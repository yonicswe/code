#!/bin/bash 

#j=0
#
#i=2
#
#while (( $i== 3 && $j< 3 )) ; do 
#	sleep 2 
#	echo "j=$j" 
#	let j+=1
#done


myarr=(  )

myarr_size=${#myarr[*]}

echo $myarr_size


if (( $myarr_size == 0 )) ; then echo yes ; fi
