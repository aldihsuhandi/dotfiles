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
        puts("Incomplete command");
    else
    {
        std::string cmd;
        cmd = "paru -Ss " + args[1];
        system(cmd.c_str());
    }
}

void list_package(std::vector<std::string> args)
{
    if(args.size() == 1)
        puts("Incomplete command");
    else
    {
        std::string cmd;
        cmd = "paru -Qs " + args[1];
        system(cmd.c_str());
    }
}

void install_package(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        puts("Incomplete command");
    else
    {
        std::string cmd;
        bool flag = false;
        cmd = "paru -S";
        for(int i = 1;i < (int)args.size();++i) {
            std::string t = args[i];
            if((t == "-y" || t == "-Y" || t == "--noconfirm") && !flag)
                t = "--noconfirm", flag = true;
            cmd += " " + t;
        }
        system(cmd.c_str());
    }
}

void uninstallPackage(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        puts("Incomplete command");
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
        cmd = "paru -Rcns";
        for(int i = 1;i < (int)args.size();++i)
            cmd += " " + args[i];
        system(cmd.c_str());
    }
}

void downgrade_package(std::vector<std::string> args)
{
    if((int)args.size() == 1)
        puts("Incomplete command");
    else
    {
        std::string cmd = "sudo downgrade";
        for(int i = 1;i < (int)args.size();++i)
            cmd += " " + args[i];
        system(cmd.c_str());
    }
}

void update(std::vector<std::string> args)
{
    if(
        (int)args.size() == 2 && (
            args[1] == "--noconfirm"|| 
            args[1] == "-y" ||
            args[1] == "-Y"
        )
    )
        system("paru -Syu --noconfirm");
    else
        system("paru -Syu");
}

void refresh()
{
    system("sudo pacman -Syyy");
}

void removeOrphans()
{
    FILE *package = popen("paru -Qdtq", "r");
    std::string cmd = "paru -R --noconfirm";
    int cnt = 0;

    while(!feof(package)){
        char tempPack[1000];
        fscanf(package, "%s\n", tempPack);
        cmd += " " + (std::string)tempPack;
        ++cnt;
    }

    if(cnt == 1)
    {
        puts("Finish...");
        return;
    }
    else
    {
        system(cmd.c_str());
        removeOrphans();
    }
}

void cl(std::vector<std::string> args)
{
    if(args.size() == 1)
        puts("Incomplete command");
    else if(args[1] == "cache")
        system("sudo pacman -Scc");
    else if(args[1] == "orphans")
    {
        printf("Remove all orphaned packages?(y/N) ");
        std::string op;
        std::getline(std::cin, op);
        if(op == "")
            op = "N";

        if(op == "n" || op == "N")
            return;
        else 
        {
            removeOrphans();
        }
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
            uninstallPackage(args);
        else if(args[0] == "purge")
            purge_package(args);
        else if(args[0] == "search")
            search_package(args);
        else if(args[0] == "list")
            list_package(args);
        else if(args[0] == "update")
            update(args);
        else if(args[0] == "downgrade")
            downgrade_package(args);
        else if(args[0] == "refresh")
            refresh();
        else if(args[0] == "clear")
            cl(args);
        else
            puts("Unknown command");
    }
}
