# !/bin/bash

sxhkd &
lxqt-session &
lxqt-powermanagement &
/usr/lib/xfce4/notifyd/xfce4-notifyd &
lxqt-policykit-agent &
picom --experimental-backend &
blueman-applet &
kmix &
kdeconnect-indicator &
parcellite &
nitrogen --restore &
numlockx &
./.config/polybar/i3.sh &
xsetroot -cursor_name arrow &
