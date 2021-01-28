# !/bin/bash
themes="adapta"
rofi -show drun \
    -display-drun "Search " \
    -theme $HOME/.config/rofi/themes/$themes/search.rasi \
    -lines 3 \
    -columns 5 \
    -width 60 \
    -hide-scrollbar \
    -icon-theme "Tela Black Dark"
    
