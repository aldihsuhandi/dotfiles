#include<iostream>
#include<cstdlib>
#include<string>

int main()
{
    std::string cmd = "curl -s \"https://www.youtube.com/results?search_query=$query\" | grep -oP '\"videoRenderer\":{\"videoId\":\".{11}\".+?\"text\":\".+?[^\\\\](?=\")' | sed 's|\\\\\\\"|“|g' | awk -F\\\" '{ print $6 \" \" $NF}'";
    printf("%s\n", cmd.c_str());
}
