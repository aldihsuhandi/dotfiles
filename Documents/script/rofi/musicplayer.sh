# !/bin/sh
musicstat=$(playerctl status)
# echo $musicstat

symbol=
case "$musicstat" in
    Paused) symbol="||";;
    Playing) symbol="||";;
esac

var=$(rofi -dmenu -sep "|" <<< $symbol \
    -no-custom \
    -lines 1 \
    -columns 3 \
    -hide-scrollbar\
    -font "JetBrainsMonoExtraBold 12"\
    -tokenize \
    -theme $HOME/.config/rofi/themes/applet/musicplayer.rasi \
    -width 10
)
echo $var
