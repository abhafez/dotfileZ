#!/bin/bash

# Get the list of sinks
sinks=$(pactl list short sinks | awk '{print $1 " " $2}')

# Use dmenu to select a sink
selected_sink=$(echo "$sinks" | dmenu -i -p "Select PulseAudio Sink:" | awk '{print $1}')

# Set the selected sink as the default
if [ -n "$selected_sink" ]; then
	pactl set-default-sink "$selected_sink"
	notify-send "Default sink set to $selected_sink"
else
	notify-send "No sink selected"
fi
