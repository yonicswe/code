#!/bin/bash

#the following is the same as rmmod --all
# which removes unused modules. 

for i in $(lsmod |awk '{if ( $3 == 0)  print $1}') ; do 
	echo ${i} 
done
