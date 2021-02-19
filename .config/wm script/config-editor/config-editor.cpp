#include<iostream>
#include<cstdlib>
#include<string>
#include<set>
#include<map>

std::set<std::string> config_name;
std::map<std::string, std::string> config_path;

std::string file_dir()
{
    FILE *file = popen("echo $HOME", "r");
    char out[1000];
    fscanf(file, "%[^\n]\n", out);
    fclose(file);
    return (std::string)out;
}

std::string get_colorscheme()
{
    std::string file_path = file_dir() + "/.config/wm script/config-editor/colorscheme";
    FILE *file = fopen(file_path.c_str(), "r");
    char colorscheme[1000];
    fscanf(file, "%s", colorscheme);
    fclose(file);
    return (std::string)colorscheme;
}

void read_config()
{
    std::string file_path = file_dir() + "/.config/wm script/config-editor/config";
    // printf("%s\n", file_path.c_str());
    FILE *file = fopen(file_path.c_str(), "r");
    char pth[1000], config[1000];
    while(!feof(file)){
        fscanf(file, "%s %[^\n]\n", config, pth);
        config_name.insert((std::string)config);
        config_path[(std::string)config] = (std::string)pth;
    }
    fclose(file);
}

int main()
{
    read_config();
    std::string rofi_config = "", cmd;
    bool flag = false;
    for(std::string it: config_name){
        if(flag)
            rofi_config += "|";
        rofi_config += it;
        flag = true;
    }
    
    // cmd = "bash -c 'rofi -dmenu -window-title \"config:  \" -sep \"|\" <<< \"" + rofi_config + "\" -columns 1 -hide-scrollbar -theme $HOME/.config/rofi/themes/" + get_colorscheme() +"/default.rasi -no-fixed-num-lines -yoffset -150'";
    cmd = "bash -c 'rofi -dmenu -lines 17 -location 1 -width 20 -window-title \"config:\" -sep \"|\" <<< \"" + rofi_config + "\" -columns 1 -hide-scrollbar -theme $HOME/.config/rofi/themes/" + get_colorscheme() +"/side-applet.rasi'";
    FILE *rofi_output = popen(cmd.c_str(), "r");
    char output[1000];
    fscanf(rofi_output, "%s\n", output);
    fclose(rofi_output);
    if(config_path.find((std::string)output) != config_path.end())
    {
        std::string output_path = config_path[(std::string)output];
        cmd = "kitty -e nvim " + output_path;
        system(cmd.c_str());
        // printf("%s\n", output_path.c_str());
    }
    return 0;
}
