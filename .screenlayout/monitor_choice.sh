#!/bin/sh

# Detect connected and active monitors with their resolutions
connected_monitors=$(xrandr | grep ' connected' | awk '{ print $1 }')
active_monitor=""

for monitor in $connected_monitors; do
	resolution=$(xrandr | grep "^$monitor" -A1 | grep -Eo '[0-9]+x[0-9]+' | head -1)
	if [ "$resolution" = "2560x1440" ]; then
		active_monitor=$monitor
		break
	fi
done

if [ -z "$active_monitor" ]; then
	echo "No monitor with 2560x1440 resolution found."
	exit 1
fi

# dmenu prompt to choose monitor setup
choice=$(echo -e "CenterMonitor\nDual\nLaptop Only" | dmenu -i -p "Choose monitor setup:")

case $choice in
CenterMonitor)
	xrandr --output $active_monitor --primary --mode 2560x1440 --pos 0x0 --rotate normal \
		--output eDP1 --off
	;;
Dual)
	xrandr --output $active_monitor --primary --mode 2560x1440 --pos 0x0 --rotate normal \
		--output eDP1 --mode 1920x1080 --pos 2560x0 --rotate normal
	;;
"Laptop Only")
	xrandr --output eDP1 --primary --mode 1920x1080 --pos 0x0 --rotate normal
	;;
*)
	echo "Invalid choice."
	exit 1
	;;
esac

# Turn off all other monitors (except eDP1 if Laptop Only is chosen)
for monitor in $connected_monitors; do
	if [ "$choice" = "Laptop Only" ]; then
		if [ "$monitor" != "eDP1" ]; then
			xrandr --output $monitor --off
		fi
	else
		if [ "$monitor" != "$active_monitor" ] && [ "$monitor" != "eDP1" ]; then
			xrandr --output $monitor --off
		fi
	fi
done

# Call post_script.sh
bash ~/.screenlayout/post_script.sh
