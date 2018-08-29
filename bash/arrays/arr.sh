#!/bin/bash

echo "running $BASH_COMMAND"
exit

MAP_ARRAY=( U - P S )
 
echo ${MAP_ARRAY[*]}
MAP=$(echo ${MAP_ARRAY[*]} | sed 's/ //g')
echo ${MAP}

MAP_ARRAY[0]="-"

echo ${MAP_ARRAY[*]}

MAP_ARRAY[3]="-"

echo ${MAP_ARRAY[*]}
