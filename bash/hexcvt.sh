#!/bin/bash
# hexconvert.sh: Convert a decimal number to hexadecimal.

E_NOARGS=85 # Command-line arg missing.
BASE=16     # Hexadecimal.

if [ -z "$1" ]
then        # Need a command line argument.
  echo "Usage: $0 number"
  exit $E_NOARGS
fi          # Exercise: add argument validity checking.


hexcvt ()
{
if [ -z "$1" ]
then
  echo 0
  return    # "Return" 0 if no arg passed to function.
fi

echo ""$1" "$BASE" o p" | dc
#                  o    sets radix (numerical base) of output.
#                    p  prints the top of stack.
# For other options: 'man dc' ...
return
}

hexcvt "$1"

exit

# 
# more methods to convert 
# ==============================
# 1) with bash 
#    hex_to_dec () { let x=0x$1 ; echo $x ;} 
# 
# 2) with dc - precision calc
#	  from dec to hex e.g.
#	  echo ""12" "16" o p" | dc  
#	  
#	  from hex to dec
#	  echo ""A" "10" o p" | dc
