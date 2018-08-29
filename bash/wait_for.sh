#!/bin/bash



function f1 () 
{
	echo $1
	sleep 10
	echo finished
}


for i in 1 2 3 4 ; do 
	( f1 $i ) & 
	pid=$!
	wait_4_arr="${wait_4_arr} $pid"
done

echo waiting for ${wait_4_arr}
wait ${wait_4_arr}
echo done
