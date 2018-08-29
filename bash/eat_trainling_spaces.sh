#!/bin/bash

file_to_eat=$1

if ! [ -e $file_to_eat ] ; then 
	echo "$file_to_eat not found!!"
	exit
fi

sed  's/[[:space:]]*$//g' $file_to_eat > $file_to_eat.eaten
mv $file_to_eat.eaten $file_to_eat
