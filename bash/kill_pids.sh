#!/bin/bash


kill_pids () 
{

   max_pids=$#

   pid_arr=( $(echo $*) )

   for (( i=0 ; i<$max_pids ; i++))  ; do 

      p=${pid_arr[$i]}

      e=$( ps h ${p} ) 
      
      if ! [ -z "$e" ] ; then 
         echo "killing $p" 
      else
         echo "process $p not found"
      fi
   done 

}






#
# Main
#
kill_pids 34 55 567 767 12134 444
