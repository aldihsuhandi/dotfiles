#ifndef _IOSTREAM_
#include <iostream>
#define _IOSTREAM_
#endif

#ifndef _STRING_
#include <string>
#define _STRING_
#endif

#ifndef _VECTOR_
#include <vector>
#define _VECTOR_
#endif

#ifndef _MAP_
#include <map>
#define _MAP_
#endif

#include <algorithm>
#include <cstring>

#include "encrypt.cpp"
#include "json_lib.cpp"
#include "hexadec.cpp"

#include <unistd.h>

using namespace std;

typedef struct WifiData
{
private:
    string wifi_uuid;
    string wifi_name;
    string password;
    int wifi_strength;
    bool connected;

    void clean_up_wifi_uuid()
    {
        string str = this->wifi_uuid;
        string escaped_colon = "\\:";
        string replacement = ":";

        size_t pos = 0;
        while ((pos = str.find(escaped_colon, pos)) != string::npos)
        {
            str.replace(pos, escaped_colon.length(), replacement);
            pos += replacement.length();
        }

        this->wifi_uuid = str;
    }

public:
    WifiData(string wifi_uuid, string _wifi_name, int _wifi_strength, bool connected)
    {
        this->wifi_name = _wifi_name;
        this->wifi_strength = _wifi_strength;
        this->connected = connected;
        this->wifi_uuid = wifi_uuid;

        this->clean_up_wifi_uuid();
    }

    string get_wifi_uuid()
    {
        return this->wifi_uuid;
    }

    string get_name()
    {
        return this->wifi_name;
    }

    bool get_connected()
    {
        return this->connected;
    }

    int get_strength()
    {
        return this->wifi_strength;
    }

    string get_password()
    {
        return this->password;
    }

    void set_password(string password)
    {
        this->password = password;
    }

    string to_string()
    {
        char buffer[1024];
        sprintf(buffer, "{\"WifiData\": {\"wifi_uuid\": \"%s\", \"wifi_name\": \"%s\", \"password\": \"%s\", \"wifi_strength\": \"%d\", \"connected\": \"%s\"}}", this->wifi_uuid.c_str(), this->wifi_name.c_str(), this->password.c_str(), this->wifi_strength, this->connected ? "TRUE" : "FALSE");
        return (string)buffer;
    }

    string get_strength_logo()
    {
        int strength = this->wifi_strength;
        if (strength >= 99)
        {
            return "󰣺";
        }

        if (strength >= 80)
        {
            return "󰣸";
        }

        if (strength >= 50)
        {
            return "󰣶";
        }

        if (strength >= 25)
        {
            return "󰣴";
        }

        return "󰣾";
    }

    static bool compare(const WifiData &lhs, const WifiData &rhs)
    {
        if (lhs.connected)
        {
            return true;
        }

        if (rhs.connected)
        {
            return false;
        }

        return lhs.wifi_strength > rhs.wifi_strength;
    }
} WifiData;

string password_file_loc = "$HOME/.config/wm script/network-select/password.secret";

char buffer_c[4096];
string buffer_str;

string theme;
bool loading_rofi = false;
int wifi_status = -1;

vector<WifiData> wifi_data;
map<string, string> bssid_password;
EncodeDecode encode_decode;

void run_shell(string s);
FILE *run_shell_file(string s);
void show_loading_rofi();
void kill_loading_rofi();
string get_str_from_buffer();
void set_global_theme();
void set_config_file();
string execute_rofi_cmd(string cmd);
void write_password_file();
void read_password_file();
int show_notif(string notification);
void show_notif(string notification, int notif_id);
int get_wifi_status();
void toggle_wifi();

void scan_wifi_networks()
{
    string cmd = "nmcli -t -f SSID,IN-USE,SIGNAL,BSSID device wifi list";
    FILE *wifi_connection = run_shell_file(cmd);
    while (!feof(wifi_connection))
    {
        fscanf(wifi_connection, "%[^\n]\n", buffer_c);
        char name_buffer[1024], bssid_buffer[1024], connected_buffer;
        int strength_buffer;
        sscanf(buffer_c, "%[^:]:%c:%d:%[^\n]\n", name_buffer, &connected_buffer, &strength_buffer, bssid_buffer);
        wifi_data.push_back(WifiData((string)bssid_buffer, (string)name_buffer, strength_buffer, connected_buffer == '*'));
    }
    fclose(wifi_connection);

    stable_sort(wifi_data.begin(), wifi_data.end(), WifiData::compare);

    read_password_file();
}

WifiData show_rofi_selection()
{
    string rofi_value = "";
    bool need_separator = false;

    if (get_wifi_status() == 1)
    {
        rofi_value = "Turn off wifi connection";
        need_separator = true;
    }

    for (auto it : wifi_data)
    {
        if (need_separator)
        {
            rofi_value += "|";
        }

        sprintf(buffer_c, "%s %-24s %s ", it.get_connected() ? "*" : " ",
                it.get_name().c_str(), it.get_strength_logo().c_str());
        rofi_value += get_str_from_buffer();

        need_separator = true;
    }

    string rofi_cmd = (string) "bash -c 'rofi -dmenu -lines 5 -location 1 -width 20 -window-title \"Wifi Network\" -sep \"|\"" + " <<< \"" + rofi_value + "\" " + "-theme $HOME/.config/rofi/themes/" + theme + "/side-applet.rasi " + "-columns 1 -hide-scrollbar " + "-format i " + "'";

    string res = execute_rofi_cmd(rofi_cmd);
    if (res == "")
    {
        exit(0);
    }

    int rofi_res_index = stoi(res);

    if (rofi_res_index == 0 && get_wifi_status() == 1)
    {
        toggle_wifi();
        exit(0);
    }

    WifiData result_wifi = wifi_data[rofi_res_index - get_wifi_status()];
    printf("DEBUG[result_wifi: %s]\n", result_wifi.to_string().c_str());
    return result_wifi;
}

string view_rofi_password()
{
    string rofi_cmd = (string) "bash -c 'rofi -dmenu -location 7 -width 20 -window-title \"Enter Password\" -theme $HOME/.config/rofi/themes/" + theme + "/side-applet.rasi " + "-columns 1 -hide-scrollbar " + "'";
    return execute_rofi_cmd(rofi_cmd);
}

bool connect_to_network(WifiData network)
{
    int notif_res = show_notif("connecting to " + network.get_name());
    sprintf(buffer_c, "nmcli device wifi connect \"%s\" password \"%s\"", network.get_wifi_uuid().c_str(), network.get_password().c_str());
    string cmd = get_str_from_buffer();
    FILE *connect = run_shell_file(cmd);
    fscanf(connect, "%[^\n]\n", buffer_c);
    fclose(connect);
    string connect_result = get_str_from_buffer();
    show_notif(connect_result, notif_res);

    string success_string = "successfully";
    return search(connect_result.begin(), connect_result.end(), success_string.begin(), success_string.end()) != connect_result.end();
}

int main()
{
    set_global_theme();
    set_config_file();
    show_loading_rofi();
    int status = get_wifi_status();
    if (status == 0)
    {
        toggle_wifi();
        sleep(2);
    }

    scan_wifi_networks();
    WifiData selected_network = show_rofi_selection();
    if (selected_network.get_connected())
    {
        show_notif("Network " + selected_network.get_name() + " is already connected!");
        exit(0);
    }

    if (selected_network.get_password().length() == 0)
    {
        string wifi_password = view_rofi_password();
        if (wifi_password == "")
        {
            exit(1);
        }

        selected_network.set_password(wifi_password);
        bssid_password[selected_network.get_wifi_uuid()] = wifi_password;
        write_password_file();
    }

    bool connect_res = connect_to_network(selected_network);
    if (!connect_res)
    {
        bssid_password.erase(selected_network.get_wifi_uuid());
        write_password_file();
    }
    return 0;
}

string get_str_from_buffer()
{
    string s = (string)buffer_c;
    memset(buffer_c, 0, sizeof(buffer_c));
    return s;
}

void set_global_theme()
{
    FILE *file = run_shell_file("echo $HOME");
    fscanf(file, "%[^\n]\n", buffer_c);
    fclose(file);

    string file_dir = get_str_from_buffer();
    string theme_file_path = file_dir + "/.config/rofi/colorscheme";
    FILE *colorscheme = fopen(theme_file_path.c_str(), "r");
    fscanf(colorscheme, "%s\n", buffer_c);
    fclose(colorscheme);

    theme = get_str_from_buffer();
}

void set_config_file()
{
    FILE *file = run_shell_file("echo $HOME");
    fscanf(file, "%[^\n]\n", buffer_c);
    fclose(file);

    string file_dir = get_str_from_buffer();
    password_file_loc = file_dir + "/.config/wm script/network-select/password.secret";
}

string execute_rofi_cmd(string cmd)
{
    kill_loading_rofi();
    FILE *command_res = run_shell_file(cmd);
    fscanf(command_res, "%[^\n]\n", buffer_c);
    fclose(command_res);

    return get_str_from_buffer();
}

void show_loading_rofi()
{
    loading_rofi = true;
    string rofi_cmd = (string) "bash -c 'rofi -dmenu -lines 5 -location 1 -width 20 -window-title \"Wifi Network\" -sep \"|\"" + " <<< \"loading....\" " + "-theme $HOME/.config/rofi/themes/" + theme + "/side-applet.rasi " + "-columns 1 -hide-scrollbar " + "' &";

    run_shell(rofi_cmd);
}

void kill_loading_rofi()
{
    if (loading_rofi)
    {
        loading_rofi = false;
        run_shell("pkill rofi >> /dev/null");
    }
}

void write_password_file()
{
    FILE *password_file = fopen(password_file_loc.c_str(), "w");
    for (auto it : bssid_password)
    {
        fprintf(password_file, "{\"bssid\": \"%s\", \"password\": \"%s\"}\n", it.first.c_str(),
                HexaUtil::string_to_hex(encode_decode.decode(it.second)).c_str());
    }
    fclose(password_file);
}

void read_password_file()
{
    FILE *password_file = fopen(password_file_loc.c_str(), "r");
    if (password_file == NULL)
    {
        return;
    }

    while (!feof(password_file))
    {
        fscanf(password_file, "%[^\n]\n", buffer_c);
        string json_string = get_str_from_buffer();
        map<string, string> password_map = JsonUtil::parse_json_to_map(json_string);
        string bssid = password_map["bssid"], password = encode_decode.decode(
                                                  HexaUtil::hex_to_string(password_map["password"]));
        bssid_password[bssid] = password;
    }
    fclose(password_file);

    for (WifiData &it : wifi_data)
    {
        if (bssid_password.find(it.get_wifi_uuid()) == bssid_password.end())
        {
            continue;
        }

        it.set_password(bssid_password[it.get_wifi_uuid()]);
    }
}

int show_notif(string notification)
{
    string cmd = "notify-send -p \"" + notification + "\" &";
    FILE *notif_result = run_shell_file(cmd);
    fscanf(notif_result, "%[^\n]\n", buffer_c);
    fclose(notif_result);

    string res = get_str_from_buffer();
    return stoi(res);
}

void show_notif(string notification, int notif_id)
{
    sprintf(buffer_c, "notify-send -r %d  \"%s\" &", notif_id, notification.c_str());
    string cmd = get_str_from_buffer();
    run_shell(cmd.c_str());
}

int get_wifi_status()
{
    if (wifi_status != -1)
    {
        return wifi_status;
    }

    FILE *wifi_status_res = run_shell_file("nmcli radio wifi");
    fscanf(wifi_status_res, "%[^\n]\n", buffer_c);
    fclose(wifi_status_res);
    string wifi_status_str = get_str_from_buffer();

    return wifi_status = wifi_status_str == "enabled" ? 1 : 0;
}

void toggle_wifi()
{
    int status = get_wifi_status();
    if (status == -1)
    {
        return;
    }

    string command = "nmcli radio wifi on";
    string notif_message = "turning on wifi connection";
    if (wifi_status)
    {
        command = "nmcli radio wifi off";
        notif_message = "turning off wifi connection";
    }

    run_shell(command.c_str());
    show_notif(notif_message);

    wifi_status = -1;
    get_wifi_status();
}

void run_shell(string s)
{
    printf("RUN: %s\n", s.c_str());
    system(s.c_str());
}

FILE *run_shell_file(string s)
{
    printf("RUN: %s\n", s.c_str());
    FILE *file = popen(s.c_str(), "r");
    return file;
}