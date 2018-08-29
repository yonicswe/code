#!/bin/bash

send_mail () 
{
    declare -a mailing_list=("${!1}");
    declare -a subject=("${!2}");
    declare -a attach_list_p=("${!3}");
    local attach_list=;       

    if (( ${#attach_list_p[*]} > 0 )) ; then         
        echo "attach_list_p = ${attach_list_p[*]}"

        m=${#attach_list_p[*]};
        for ((i=0 ;  i<m ; i++)) ; do 
            attach_list=${attach_list}" -a ${attach_list_p[$i]}"
        done

    fi
        

    echo -e " mailx -s \"${subject[*]}\" ${attach_list} ${mailing_list[*]}"
    echo | mailx -s "${subject[*]}" ${attach_list} ${mailing_list[*]}


}

mailing_list=(yonatan.cohen@nice.com yonatan.kalev@nice.com)
subject=(tester mail)
attach_list_1=(a.txt b.txt);
attach_list_2=();


send_mail mailing_list[@] subject[@] attach_list_1[@]
send_mail mailing_list[@] subject[@] attach_list_2[@]
    
