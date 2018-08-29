#!/bin/bash

# print the header
ps -eo pid,rss,vsz,pmem,wchan,sgi_p,args|  awk '{if (FNR == 1) print $0 }' ;

# print the processes sorted by mem usage
ps -eo pid,rss,vsz,pmem,wchan,sgi_p,args|  awk '{if (FNR != 1) print $0 }' | sort -n -k 2



