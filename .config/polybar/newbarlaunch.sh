#!/usr/bin/env sh

## Add this to your wm startup file.

# Terminate already running bar instances
killall -q polybar

# Wait until the processes have been shut down
while pgrep -u $UID -x polybar >/dev/null; do sleep 1; done

# launch fullbar
PRIMARY=$(xrandr --query | grep " connected" | grep "primary" | cut -d" " -f1)
OTHERS=$(xrandr --query | grep " connected" | grep -v "primary" | cut -d" " -f1)

# Launch on primary monitor
MONITOR=$PRIMARY polybar --reload rofimenu &
MONITOR=$PRIMARY polybar --reload workspace &
MONITOR=$PRIMARY polybar --reload song &
MONITOR=$PRIMARY polybar --reload "date" &
MONITOR=$PRIMARY polybar --reload "powermenu" &
MONITOR=$PRIMARY polybar --reload "networkconnection" &
MONITOR=$PRIMARY polybar --reload "volume" &

sleep 1

# Launch on all other monitors
for m in $OTHERS; do
    MONITOR=$m polybar --reload rofimenu &
    MONITOR=$m polybar --reload workspace &
    MONITOR=$m polybar --reload song &
    MONITOR=$m polybar --reload "date" &
    MONITOR=$m polybar --reload "powermenu" &
    MONITOR=$m polybar --reload "networkconnection" &
    MONITOR=$m polybar --reload "volume" &
done

# # Launch bar1 and bar2
# polybar -c ~/.config/polybar/config bar1 &
# polybar -c ~/.config/polybar/config bar2 &
# polybar -c ~/.config/polybar/config bar3 &
