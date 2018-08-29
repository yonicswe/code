#!/bin/bash

if ! [ $# -gt 0 ] ; then 
	exit
fi

rpm -qa | 

while read x ; do  
	rpm_arr=( $(rpm -ql $x | grep -i $1 |  xargs) )
	
	#echo looking in $x with ${#rpm_arr[*]} entries

	for (( count=0 ; count<${#rpm_arr[*]} ; count++ )) ; do 
		echo "Found ${rpm_arr[$count]}" 
		echo "in RPM : $x" 
		echo
	done
done
