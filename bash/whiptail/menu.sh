#!/bin/bash

whiptail --menu "Preferred Linux Distro" 10 40 4 \
debian "Venerable Debian" \
ubuntu "Popular Ubuntu" \
fedora "Hackish Fedora" \
centos "Stable Centos" \
mint "Rising Star Mint" 2> menu_choice.txt
# the choice is waiting in the following file.
# cat menu_choice.txt



choice=$(whiptail --menu "Preferred Linux Distro" 10 40 4 \
yoni "" \
dvori "" \
maya "" \
daniel "" 3>&1 1>&2 2>&3)
echo $choice
