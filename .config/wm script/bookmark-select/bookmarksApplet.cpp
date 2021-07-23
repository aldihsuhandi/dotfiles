#include<iostream>
#include<map>
#include<set>

std::string theme;
std::map<std::string, std::string> mp;
std::set<std::string> st;

std::string file_dir()
{
    FILE *file = popen("echo $HOME", "r");
    char out[1000];
    fscanf(file, "%[^\n]\n", out);
    fclose(file);
    return (std::string)out;
}

void getThemes()
{
    std::string file_path = file_dir() + "/.config/rofi/colorscheme";
    FILE *colorscheme = fopen(file_path.c_str(), "r");
    char t[1000];
    fscanf(colorscheme, "%s\n", t);
    theme = (std::string)t;
    fclose(colorscheme);
}

void readBookmarks()
{
    std::string file_path = file_dir() + "/.config/wm script/bookmark-select/bookmark";
    char fi[1000], se[1000];
    FILE *bookmarks = fopen(file_path.c_str(), "r");
    while(!feof(bookmarks)){
        fscanf(bookmarks, "%s - %s\n", fi, se);
        st.insert((std::string)fi);
        mp[(std::string)fi] = (std::string)se;
    }
}

std::string convertBookmark()
{
    std::string ret = "";
    bool flag = false;
    for(std::string it: st){
        if(flag)
            ret += "|";
        ret += it;
        flag = true;
    }
    return ret;
}

std::string exRofi(std::string cmd)
{
    char t[1000];
    FILE *output = popen(cmd.c_str(), "r");
    fscanf(output, "%s\n", t);
    if(mp.find((std::string)t) == mp.end())
        return "";
    return mp[(std::string)t];
}

int main()
{
    getThemes();
    readBookmarks();
    std::string dm = convertBookmark();
    std::string cmd = "bash -c 'rofi -dmenu -lines 17 -location 1 -width 20 -window-title \"Bookmark:\" -sep \"|\" <<< \"" + dm + "\" -columns 1 -hide-scrollbar -theme $HOME/.config/rofi/themes/" + theme +"/side-applet.rasi'";
    std::string out = exRofi(cmd);
    
    if(out != "")
    {
        cmd = "brave " + out;
        system(cmd.c_str());
    }

    return 0;
}
