#!/bin/bash


while getopt "show" -- opt; do
	case ${opt} in
	show) 
		echo "option show";
		;;
	a)
		echo -e "option a"
		;;
	b)
		echo -e "option b";
		;;
	*)
        echo -e "unknown option";
		exit 1 
		;;
	esac
done
