# !/bin/bash
theme="iceberg"

rofi -dmenu \
    -lines 0 \
    -location 7 \
    -width 20 \
    -p " " \
    -theme $HOME/.config/rofi/themes/$theme/side-applet.rasi

# rofi -dmenu -lines 17 -location 1 -width 20 -p " " -theme $HOME/.config/rofi/themes/$theme/side-applet.rasi
