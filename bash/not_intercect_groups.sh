#!/bin/bash

# this code shows how delete the specified items in b from a 
# something like a  - b 
# the result is a=(2 4)
a=(1 2 3 4);
b=(1 3);

# for each item in b[] rebuild a[] without the current item.
for i in ${b[@]} ; do 
   a=( $(printf "%s\n" $(echo ${a[@]}) | grep -v $i ) )
done
echo ${a[@]}

# this is another way to do it 
# by taking advantage of the search and replace capability built into bash arrays
# where for example ${arr[@]/yo/ho} would replace occurences of "yo" with "ho"
# in arr[]
c=(1 2 3 4)
for i in ${b[@]} ; do 
    c=( $(echo ${c[@]/$i/}) )
done
echo ${c[@]}
    



    
