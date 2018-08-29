#!/bin/bash
#! /bin/bash
whiptail --title "Backups" --yesno --defaultno "Start the sample program." 8 78

exitstatus=$?
if [ $exitstatus = 0 ]; then
    status="0"
    while [ "$status" -eq 0 ]  
    do
        choice=$(whiptail --title "Testing" --menu "Make a choice" 16 78 5 \
        "Application 1" "Start backing up the first application." \
        "Application 2" "Start backing up the second application." 3>&2 2>&1 1>&3) 
        
        # Change to lower case and remove spaces.
        option=$(echo $choice | tr '[:upper:]' '[:lower:]' | sed 's/ //g')
        case "${option}" in 
            application1) 
                whiptail --title "Testing" --msgbox "In first option" 8 78
            ;;
            application2)
                whiptail --title "Testing" --msgbox "In second option" 8 78
            ;;
            *) whiptail --title "Testing" --msgbox "You cancelled or have finished." 8 78
                status=1
                exit
            ;;
        esac
        exitstatus1=$status1
    done
else
    whiptail --title "Testing" --msgbox "You chose not to start." 8 78
    exit 
fi
