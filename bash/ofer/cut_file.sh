#!/bin/bash


start=0
skip_next_line=0

cat input.txt | while read x ; do
   
   s=$(echo $x | awk '{print $1}') ;  
   
   # set -x
   if [ "$s" == "###" ] ; then 
      eval $(echo $x | awk '{print $2}') ; 
      if (( $start == 0 )) ; then 
         start=1
         skip_next_line=1
      # else
      #   start=0
      fi 
   fi

   # now $file holds the filename to save to 
   if (( $start == 1 && $skip_next_line==1 )) ; then 
      skip_next_line=0
      continue
   fi

   if (( $start == 1 )) ; then 
      echo $x >> ${file}
   fi

   # set +x
done
