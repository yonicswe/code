#! /bin/bash

whiptail --yesno "would you like to see another menu?" \
--yes-button "Yes, I do" \
--no-button "No, get me out of here"  8 80

choice=$?

if (( ${choice} == 1 )) ; then 
    exit 0
fi    
# If you cannot understand this, read Bash_Shell_Scripting#if_statements again.
if (whiptail --title "Example Dialog" --yesno "This is an example of a yes/no box." 8 78) then
    echo "User selected Yes, exit status was $?."
else
    echo "User selected No, exit status was $?."
fi
