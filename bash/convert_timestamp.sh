#!/bin/bash
start_epoch=$(date +"%s")
while true ; do 

	now_epoch=$(date +"%s")

	((elapsed = now_epoch - start_epoch ))
	echo $elapsed

	echo $(	awk -v t=$elapsed 'BEGIN{print strftime("%Hh%Mm%Ss",t)}' )


	sleep 1
done
