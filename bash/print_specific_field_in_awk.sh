#!/bin/bash

x=3

# print field number 3
echo yoni dvori maya dany | awk '{print $a" "$f}' a=1, f=$x

# another way to do this 
echo yoni dvori maya dany | awk -v f=$x '{for (i=0; i<=NF; i++) {if (i==f) print $i} }'

# another way to do this 
echo yoni dvori maya dany | awk -v f=$x '{print $f",("f")"}'
