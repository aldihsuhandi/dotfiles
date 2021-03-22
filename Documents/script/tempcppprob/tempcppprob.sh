# !/bin/bash
echo "$1" > $HOME/Documents/script/tempcppprob/inp
$HOME/Documents/script/tempcppprob/./script < $HOME/Documents/script/tempcppprob/inp
touch in
touch out
clear
exa -F -s=name --long -S -h --group-directories-first -G
