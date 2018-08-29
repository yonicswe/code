#!/bin/bash


on_die()
{
	# print message
	#
	# echo "Dying..."

	# Need to exit the script explicitly when done.
	# Otherwise the script would live on, until system
	# realy goes down, and KILL signals are send.
	#
	# echo "kill ${propel_pid}"
	kill ${propel_pid}
	exit 0
}


# Execute function on_die() receiving TERM signal
#
trap 'on_die' TERM SIGINT SIGTERM


# while true ; do 
	./propel.sh &
	propel_pid=$!

	# sleep 2

	echo -n "du -sh /   "
   output=$(du -sh / 2>/dev/null)
   output=$(du -sh / 2>/dev/null)
   output=$(du -sh / 2>/dev/null)
   output=$(du -sh / 2>/dev/null)
	kill ${propel_pid}
   sleep 1
   echo -e "\n${output}"
# done

