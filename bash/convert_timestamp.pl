!#/bin/bash
#EPOCH=1000000000
EPOCH=$(date +"%s")
DATE=$(perl -e "require 'ctime.pl'; print &ctime($EPOCH);")
echo $DATE
DATE=$(perl -e "print scalar(localtime($EPOCH))")
echo $DATE
DATE=$(echo $EPOCH|awk '{print strftime("%c",$1)}')
echo $DATE

[update: Thanks to S. Maynard for reminding me of the proper use of quotes and how to avoid using the pipe...]
DATE=$(awk "BEGIN { print strftime(\"%c\",$EPOCH) }")


awk -v t=$numsec 'BEGIN{print strftime("%Hh%Mm%Ss",t)}'
