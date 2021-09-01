# !/bin/bash
themes="$(cat ~/.config/rofi/colorscheme)"
rofi -show drun \
    -no-fixed-num-lines \
    -display-drun "Search " \
    -theme $HOME/.config/rofi/themes/$themes/search.rasi \
    -icon-theme "Tela Black Dark"
