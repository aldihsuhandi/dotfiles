# !/bin/bash
themes="iceberg"
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
    ) light-locker-command -l;;
    ) if [ $wm == 'bspwm' ]; then
            bspc quit
       else
            opebox --exit
       fi;;
    ) reboot;;
    ) shutdown now;;
esac
