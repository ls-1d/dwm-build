#!/bin/bash

#starting some nice programs
#
#
cbatticon &
picom &
unclutter &
nm-applet &
#xfce4-power-manager &
#volumeicon &
feh --bg-fill --randomize ~/.local/share/wallpapers/*
nitrogen --restore &

# start redshift
#
if [ -f /usr/bin/redshift-gtk ]; then
    redshift-gtk&
fi

# Mute Audio and Mic
#
amixer -D pulse set Master mute
amixer set Capture nocap

# Swap caps lock with esc and disable esc key
#
#setxkbmap -option caps:swapescape

# start kdeconnectd
/usr/lib/kdeconnectd &

# start kdeconnect-indicator
/usr/bin/kdeconnect-indicator &

#polkit-gnome
#
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

#starting the dwm_bar
#
sleep 2
slstatus &
