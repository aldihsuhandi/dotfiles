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
MONITOR=$PRIMARY polybar rofimenu &
MONITOR=$PRIMARY polybar workspace &
MONITOR=$PRIMARY polybar song &
MONITOR=$PRIMARY polybar "date" &
MONITOR=$PRIMARY polybar "networkconnection" &
MONITOR=$PRIMARY polybar "volume" &

sleep 1

# Launch on all other monitors
for m in $OTHERS; do
    MONITOR=$m polybar rofimenu &
    MONITOR=$m polybar workspace &
    MONITOR=$m polybar song &
    MONITOR=$m polybar "date" &
    MONITOR=$m polybar "networkconnection" &
    MONITOR=$m polybar "volume" &
done

# # Launch bar1 and bar2
# polybar -c ~/.config/polybar/config bar1 &
# polybar -c ~/.config/polybar/config bar2 &
# polybar -c ~/.config/polybar/config bar3 &
