#!/bin/bash

##########################################################
# instructios: 
#  cd to a root of a branch and invoke this script. 
#  all the files that had any work done on them in that branch 
#  wil have revision numbers bigger than the default 2.
#  these files will be printed out in a format that fits to diffing. 
#
#  so echoing its output to something like |awk '{x="tkdiff " $0; system(eval x)}'
#  will show all the differences.
##########################################################

for src_file in $(find . -type f|awk '!/CVS/{print}') ; do 

	revision_str=$(2>&1 cvs stat ${src_file} |awk '/Working revision/{print $3}')

    revision_arr=( $(echo ${revision_str} |sed 's/\./ /g') )
    
	revision_size=${#revision_arr[*]}

	if  (( ${revision_size} > 2 )) ; then  
		echo "-r ${revision_arr[0]}.${revision_arr[1]} -r ${revision_str} ${src_file}"
	fi
    
done


