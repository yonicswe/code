#!/bin/bash

SLEEP_TIME=150000

trap_hl()
{
 printf '\r'
 # printf ' '
 # printf '\n'
 exit 0
}

trap 'trap_hl' 2 9 15

count=0

while true
do
	printf '\'
	printf '\b' 
	usleep $SLEEP_TIME
	printf '|'
	printf '\b' 
	usleep $SLEEP_TIME
	printf '/'
	printf '\b' 
	printf '-'
	printf '\b' 
	usleep $SLEEP_TIME
   ((count++))
   if (( count == 5 )) ; then 
      (( count = 0 ))
      printf '*' 
   fi 

done

# while true
# do
# 	printf '\'
# 	printf '\r' 
# 	usleep $SLEEP_TIME
# 	printf '|'
# 	printf '\r' 
# 	usleep $SLEEP_TIME
# 	printf '/'
# 	printf '\r' 
# 	printf '-'
# 	printf '\r' 
# 	usleep $SLEEP_TIME
# done

