# !/bin/bash
themes="$(cat ~/.config/rofi/colorscheme)"
rofi -show drun \
    -display-drun "Search " \
    -theme $HOME/.config/rofi/themes/$themes/search.rasi \
    -icon-theme "Tela Black Dark"
    
