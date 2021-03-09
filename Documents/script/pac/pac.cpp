#include <iostream>
#include <vector>
#include <cstdlib>

void print_usage()
{
    system("cat $HOME/Documents/script/pac/help");
}

void search_package(std::vector<std::string> args)
{
    if(args.size() == 1)
        system("echo \"Incomplete command\"");
    else if(args[1] == "installed")
    {
        if(args.size() == 2)
            system("echo \"Incomplete command\"");
        else
        {
            std::string cmd;
            cmd = "paru -Qs " + args[2];
            system(cmd.c_str());
        }
    }
    else
    {
        std::string cmd;
        cmd = "paru -Ss " + args[1];
        system(cmd.c_str());
    }
}

void install_package(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        system("echo \"Incomplete command\"");
    else
    {
        std::string cmd;
        cmd = "paru -S";
        for(int i = 1;i < (int)args.size();++i)
            cmd += " " + args[i];
        system(cmd.c_str());
    }
}

void uninstall_package(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        system("echo \"Incomplete command\"");
    else
    {
        std::string cmd;
        cmd = "paru -R";
        for(int i = 1;i < (int)args.size();++i)
            cmd += " " + args[i];
        system(cmd.c_str());
    }
}

void purge_package(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        puts("Incomplete command");
    else{
        std::string cmd;
        cmd = "paru -Rcs";
        for(int i = 1;i < (int)args.size();++i)
            cmd += " " + args[i];
        system(cmd.c_str());
    }
}

void update()
{
    system("paru");
}

void refresh()
{
    system("sudo pacman -Syyy");
}

void cl(std::vector<std::string> args)
{
    if(args.size() == 1)
        system("echo \"Incomplete command\"");
    else if(args[1] == "cache")
        system("sudo pacman -Scc");
    else if(args[1] == "orphans")
    {
        FILE *package = popen("pacman -Qdtq", "r");
        std::string cmd = "paru -R";
        int cnt = 0;
        while(!feof(package)){
            char tempPack[1000];
            fscanf(package, "%s\n", tempPack);
            cmd += " " + (std::string)tempPack;
            ++cnt;
        }
        // printf("%d\n", cnt);
        if(cnt == 1)
            system("echo \"There is no orphaned package\"");
        else
            system(cmd.c_str());
    }
}

int main(int argc, char **argv)
{
    if(argc == 1)
        print_usage();
    else
    {
        std::vector<std::string> args;
        for(int i = 1;i < argc;++i)
            args.push_back((std::string)argv[i]);
        if(args[0] == "install")
            install_package(args);
        else if(args[0] == "uninstall")
            uninstall_package(args);
        else if(args[0] == "purge")
            purge_package(args);
        else if(args[0] == "search")
            search_package(args);
        else if(args[0] == "update")
            update();
        else if(args[0] == "refresh")
            refresh();
        else if(args[0] == "clear")
            cl(args);
        else
            system("echo \"Unknown Command\"");
    }
}
