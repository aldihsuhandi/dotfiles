# !/bin/sh

term="Alacritty"

while :
do
    window=$(xdotool getactivewindow getwindowname)
    name=$(echo $window | awk -F "-" '{print $NF}')
    if [ "$name" = "$window" ]; then
        name=$term
    fi
    echo "$name | $window"
    sleep 1
done
