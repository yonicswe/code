#!/bin/bash
# utilitymenu.sh - A sample shell script to display menus on screen
# Store menu options selected by the user
INPUT=/tmp/menu.sh.$$
 
# Storage file for displaying cal and date command output
OUTPUT=/tmp/output.sh.$$
 
# get text editor or fall back to vi_editor
vi_editor=${EDITOR-vi}
 
# trap and delete temp files
trap "rm $OUTPUT; rm $INPUT; exit" SIGHUP SIGINT SIGTERM
 
#
# Purpose - display output using msgbox 
#  $1 -> set msgbox height
#  $2 -> set msgbox width
#  $3 -> set msgbox title
#
function display_output(){
    local h=${1-10}         # box height default 10
    local w=${2-41}         # box width default 41
    local t=${3-Output}     # box title 
    dialog --backtitle "Linux Shell Script Tutorial" --title "${t}" --clear --msgbox "$(<$OUTPUT)" ${h} ${w}
}
#
# Purpose - display current system date & time
#
function show_date(){
    echo "Today is $(date) @ $(hostname -f)." >$OUTPUT
    display_output 6 60 "Date and Time"
}
#
# Purpose - display a calendar
#
function show_calendar(){
    cal >$OUTPUT
    display_output 13 25 "Calendar"
}

function config_browsing () 
{
    echo "running browing resgression"; 
}

function config_protocols () 
{
    echo "running Protocols resgression"; 
}

function config_ipdr () 
{
    echo "running Ipdr resgression"; 
}
 

Main () 
{ 
     
#         dialog --clear  --help-button --backtitle "IPS Regression" \
#                --title "[ M A I N - M E N U ]" \
#                --menu "Choose type of regression" 18 50 4 \
#                Date/time "Displays date and time" \
#                Calendar "Displays a calendar" \
#                Editor "Start a text editor" \
#                Exit "Exit to the shell" 2>"${INPUT}"
                
        dialog --clear  --help-button --backtitle "IPS Regression" \
               --title "[ M A I N - M E N U ]" \
               --checklist "Choose type of regression" 18 50 4 \
               browsing " " on \
               protocols " " off \
               ipdr " " off  2> ${INPUT}

#                menuitem=$(<"${INPUT}")
                
                

        awk 'BEGIN{RS=" "} {print $0}' ${INPUT} | while read x ; do  
                echo "choice : ${x}" 
                case $x in
                    1) 
                        config_browsing;
                        ;;
                    2) 
                        config_protocols;
                        ;;
                    3) 
                        config_ipdr
                        ;;
                esac

            done                    

    
    # if temp files found, delete em
    [ -f $OUTPUT ] && rm $OUTPUT
    [ -f $INPUT ] && rm $INPUT
}



Main 
