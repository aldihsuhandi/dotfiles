#include<iostream>
#include<stdlib.h>
#include<string>

int length(char x[])
{
    int i;
    for(i = 0;x[i];++i);
    return i;
}

int main()
{
    char c = getchar();
    int n = c - 'a' + 1;
    char command[100] = "cp $HOME/Documents/cpp/template/template.cpp a.cpp";
    int idx = length(command) - 5;
    for(int i = 0;i < n;++i){
        command[idx] = 'a' + i;
        system(command);
    }
}
