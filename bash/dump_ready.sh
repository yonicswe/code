#!/bin/bash

# 
#  make sure that /dev/dump is infact a link to a block partition.
# 

DUMP_DEVICE=/dev/dump




# 
# Main 
# 

# make sure there is a dump device.
dump_dev_type=$(file $DUMP_DEVICE)
if ! [ -b $DUMP_DEVICE ] ; then 
	echo -e "$DUMP_DEVICE not found\nNo Crash dump"
	exit 1
fi


# 



