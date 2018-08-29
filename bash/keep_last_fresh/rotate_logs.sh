#!/bin/bash
# keep maximum MAX_FILES 
# and delete the oldest one
# to test created file_<time> with touch 
# e.g. touch -d 16:00 file_1600 

MAX_FILES=3;

declare -a files=($(ls -tr file_*));

if (( ${#files[*]} > ${MAX_FILES} )) ; then 
    echo "delete ${files[$1]}";
fi    

