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
# MONITOR=$PRIMARY polybar --reload fullbar &
MONITOR=$PRIMARY polybar --reload bar1 &
MONITOR=$PRIMARY polybar bar2 &
MONITOR=$PRIMARY polybar bar3 &
sleep 1

# Launch on all other monitors
for m in $OTHERS; do
    # MONITOR=$m polybar --reload fullbar &
    MONITOR=$m polybar --reload bar1 &
    MONITOR=$m polybar bar2 &
    MONITOR=$m polybar bar3 &
    sleep 1
done

# # Launch bar1 and bar2
# polybar -c ~/.config/polybar/config bar1 &
# polybar -c ~/.config/polybar/config bar2 &
# polybar -c ~/.config/polybar/config bar3 &
