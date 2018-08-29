#!/bin/bash
if [ `stat -c "%h" $dir` -gt 2 ] ; then 
    echo $dir is not empty
fi   

if [ "$(ls $dir)" ] ; then 
    echo $dir is not empty
fi
