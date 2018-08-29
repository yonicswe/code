#!/bin/bash

# options
# list
# getopts-style

function getoptex()
{
	let $# || return 1
	local optlist="${1#;}"
	let OPTIND || OPTIND=1
	[ $OPTIND -lt $# ] || return 1
	shift $OPTIND
  
	if [ "$1" != "-" ] && [ "$1" != "${1#-}" ] ;  then 
		OPTIND=$[OPTIND+1]
		if [ "$1" != "--" ] ; then
		local o
		o="-${1#-$OPTOFS}"
		for opt in ${optlist#;} ; do
			OPTOPT="${opt%[;.:]}"
			unset OPTARG
			local opttype="${opt##*[^;:.]}"
			[ -z "$opttype" ] && opttype=";"
			
			if [ ${#OPTOPT} -gt 1 ] ; then # long-named option
				case $o in
					"--$OPTOPT")
						if [ "$opttype" != ":" ]; then 
							return 0 
						fi

						OPTARG="$2"
							if [ -z "$OPTARG" ]; then # error: must have an agrument
							  let OPTERR && echo "$0: error: $OPTOPT must have an argument" >&2
							  OPTARG="$OPTOPT";
							  OPTOPT="?"
							  return 1;
							fi
							
						OPTIND=$[OPTIND+1] # skip option's argument
							return 0
						;;

					"--$OPTOPT="*)
						if [ "$opttype" = ";" ]; then  # error: must not have arguments
							let OPTERR && echo "$0: error: $OPTOPT must not have arguments" >&2
							OPTARG="$OPTOPT"
							OPTOPT="?"
							return 1
						fi
						OPTARG=${o#"--$OPTOPT="}
						return 0
						;;
				esac
			else # short-named option
				case "$o" in
				  "-$OPTOPT")
					unset OPTOFS
					[ "$opttype" != ":" ] && return 0
					OPTARG="$2"
					if [ -z "$OPTARG" ]
					then
					  echo "$0: error: -$OPTOPT must have an argument" >&2
					  OPTARG="$OPTOPT"
					  OPTOPT="?"
					  return 1
					fi
					OPTIND=$[OPTIND+1] # skip option's argument
					return 0
				  ;;
				  "-$OPTOPT"*)
					if [ $opttype = ";" ]
					then # an option with no argument is in a chain of options
					  OPTOFS="$OPTOFS?" # move to the next option in the chain
					  OPTIND=$[OPTIND-1] # the chain still has other options
					  return 0
					else
					  unset OPTOFS
					  OPTARG="${o#-$OPTOPT}"
					  return 0
					fi
				  ;;
				esac
			fi
    done
    echo "$0: error: invalid option: $o"
  fi; fi
  OPTOPT="?"
  unset OPTARG
  return 1
}

function optlistex
{
  local l="$1"
  local m # mask
  local r # to store result
  while [ ${#m} -lt $[${#l}-1] ]; do m="$m?"; done # create a "???..." mask
  while [ -n "$l" ]
  do
    r="${r:+"$r "}${l%$m}" # append the first character of $l to $r
    l="${l#?}" # cut the first charecter from $l
    m="${m#?}"  # cut one "?" sign from m
    if [ -n "${l%%[^:.;]*}" ]
    then # a special character (";", ".", or ":") was found
      r="$r${l%$m}" # append it to $r
      l="${l#?}" # cut the special character from l
      m="${m#?}"  # cut one more "?" sign
    fi
  done
  echo $r
}

function getopt()
{
  local optlist=`optlistex "$1"`
  shift
  getoptex "$optlist" "$@"
  return $?
}

#**************************************
#     cut here
#**************************************
#*** (end of getopt.sh) ***


#*** file getopt1 ***

#! /bin/bash
# getopt1:
# Sample script using the function getopt
#
# Type something like "getopt1 -ab -d 10 -e20 text1 text2"
# on the command line to see how it works
#
# See getopt.sh for more information
#. getopt.sh
#echo Using getopt to parse arguments:
#while getopt "abcd:e." "$@"
#do
#  echo "Option <$OPTOPT> ${OPTARG:+has an arg <$OPTARG>}"
#done
#shift $[OPTIND-1]
#for arg in "$@"
#do
#  echo "Non option argument <$arg>"
#done
#
#**************************************
#        cut here
#**************************************
#*** (end of getopt1) ***
#
#
#*** file getopt2 ***
#
#! /bin/bash
# getopt2:
# Sample script using the function getoptex
#
# Type something like "getopt2 -ab -d 10 -e20 --opt1 --opt4=100 text1 text2"
# to see how it works
#
# See getopt.sh for more information
#. getopt.sh
echo Using getoptex to parse arguments:
#while getoptex "a; b; c; d: e. opt1 opt2 opt3 opt4: opt5." "$@"
while getoptex "moshe"
do
  echo "Option <$OPTOPT> ${OPTARG:+has an arg <$OPTARG>}"
done
shift $[OPTIND-1]
for arg in "$@"
do
  echo "Non option argument <$arg>"
done
#
#**************************************
#         cut here
#**************************************
#*** (end of getopt2) ***

