#!/bin/sed -nf
s/^.*$/\
&\
/
tx
:x
s/\(\n.\)\(.*\)\(.\n\)/\3\2\1/
tx
s/\n//g 
1! G
$p
h
