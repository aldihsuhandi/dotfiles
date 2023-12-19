# !/bin/bash
confirm="N"
\cp .config ~ -drf
\cp .zshrc ~
\cp .bashrc ~
\cp .vimrc ~
\cp .fonts ~ -drf
\cp .themes ~ -drf
\cp .mpd ~ -drf


read -p "Do you want to use my vscode config[y/n]? " confirm
if [ $confirm == "Y" -o $confirm == "y" ]
then
    \cp .vscode-oss ~ -drf
fi
\cp Documents ~ -drf
