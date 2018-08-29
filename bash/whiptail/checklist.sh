#!/bin/bash
whiptail --checklist "Preferred Linux distros" 15 40 5\
               debian "Venerable Debian" off \
               ubuntu "Popular Ubuntu"   on  \
               fedora "Hackish Fedora"   off \
               centos "Stable Centos"    off \
               mint "Rising Star Mint"   off 2>distrochoice
