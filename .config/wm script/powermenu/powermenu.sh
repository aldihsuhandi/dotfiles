# !/bin/bash
themes="dracula"
wm=$GDMSESSION
# echo $wm
menu=$(rofi -dmenu \
    -sep " " \
    <<< "    " \
    -lines 1 \
    -columns 4 \
    -tokenize \
    -no-custom \
    -window-title "Search " \
    -hide-scrollbar \
    -theme $HOME/.config/rofi/themes/$themes/powermenu.rasi)

case "$menu" in
    ) lxqt-leave --locksreen;;
    ) if [ $wm == 'bspwm' ]; then
            bspc quit
       else
            opebox --exit
       fi;;
    ) lxqt-leave --reboot;;
    ) lxqt-leave --shutdown;;
esac
