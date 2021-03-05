#!/bin/bash

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
xsetroot -cursor_name arrow
# ./.config/polybar/launch.sh &
sxhkd &
