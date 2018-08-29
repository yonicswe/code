#!/bin/bash
echo $(echo -n DE:AD:BE:EF ; for i in `seq 1 2` ; do echo -n `echo ":$RANDOM$RANDOM" | cut -n -c -3` ;done)
