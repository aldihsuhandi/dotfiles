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

vector<WifiData> wifi_data;
map<string, string> bssid_password;
EncodeDecode encode_decode;

void show_loading_rofi();
void kill_loading_rofi();
string get_str_from_buffer();
void set_global_theme();
void set_config_file();
string execute_rofi_cmd(string cmd);
void write_password_file();
void read_password_file();
void show_notif(string notification);

void scan_wifi_networks()
{
    string cmd = "nmcli -t -f SSID,IN-USE,SIGNAL,BSSID device wifi list";
    FILE *wifi_connection = popen(cmd.c_str(), "r");
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
    return wifi_data[rofi_res_index];
}

string view_rofi_password()
{
    string rofi_cmd = (string) "bash -c 'rofi -dmenu -location 7 -width 20 -window-title \"Enter Password\" -theme $HOME/.config/rofi/themes/" + theme + "/side-applet.rasi " + "-columns 1 -hide-scrollbar " + "'";
    return execute_rofi_cmd(rofi_cmd);
}

bool connect_to_network(WifiData network)
{
    show_notif("connecting to " + network.get_name());
    sprintf(buffer_c, "nmcli device wifi connect \"%s\" password \"%s\"", network.get_wifi_uuid().c_str(), network.get_password().c_str());
    string cmd = get_str_from_buffer();
    FILE *connect = popen(cmd.c_str(), "r");
    fscanf(connect, "%[^\n]\n", buffer_c);
    fclose(connect);
    string connect_result = get_str_from_buffer();
    show_notif(connect_result);

    string success_string = "successfully";
    return search(connect_result.begin(), connect_result.end(), success_string.begin(), success_string.end()) != connect_result.end();
}

int main()
{
    set_global_theme();
    set_config_file();
    show_loading_rofi();
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
    FILE *file = popen("echo $HOME", "r");
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
    FILE *file = popen("echo $HOME", "r");
    fscanf(file, "%[^\n]\n", buffer_c);
    fclose(file);

    string file_dir = get_str_from_buffer();
    password_file_loc = file_dir + "/.config/wm script/network-select/password.secret";
}

string execute_rofi_cmd(string cmd)
{
    kill_loading_rofi();
    FILE *command_res = popen(cmd.c_str(), "r");
    fscanf(command_res, "%[^\n]\n", buffer_c);
    fclose(command_res);

    return get_str_from_buffer();
}

void show_loading_rofi()
{
    loading_rofi = true;
    string rofi_cmd = (string) "bash -c 'rofi -dmenu -lines 5 -location 1 -width 20 -window-title \"Wifi Network\" -sep \"|\"" + " <<< \"loading....\" " + "-theme $HOME/.config/rofi/themes/" + theme + "/side-applet.rasi " + "-columns 1 -hide-scrollbar " + "' &";

    system(rofi_cmd.c_str());
}

void kill_loading_rofi()
{
    if (loading_rofi)
    {
        loading_rofi = false;
        system("pkill rofi >> /dev/null");
    }
}

void write_password_file()
{
    FILE *password_file = fopen(password_file_loc.c_str(), "w");
    for (auto it : bssid_password)
    {
        fprintf(password_file, "{\"bssid\": \"%s\", \"password\": \"%s\"}\n", it.first.c_str(),
                encode_decode.decode(it.second).c_str());
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
        string bssid = password_map["bssid"], password = encode_decode.decode(password_map["password"]);
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

void show_notif(string notification)
{
    string cmd = "notify-send \"" + notification + "\" &";
    system(cmd.c_str());
}
