!/bin/bash
confirm="N"
\cp .config ~ -drf
\cp .zshrc ~
\cp .bashrc ~
\cp .vimrc ~
\cp .fonts ~ -drf
\cp .themes ~ -drf
\cp .ideavimrc ~ -drf
fc-cache -fv


read -p "Do you want to use my vscode config[y/n]? " confirm
if [ $confirm == "Y" -o $confirm == "y" ]
then
    \cp .vscode-oss ~ -drf
fi
\cp Documents ~ -drf

cd "$HOME/.config/wm script/bookmark-select"
g++ -o bookmarksApplet bookmarksApplet.cpp

cd "$HOME/.config/wm script/config-editor"
g++ -o config-editor config-editor.cpp

cd "$HOME/.config/wm script/network-select"
g++ -o network-select network-select.cpp
