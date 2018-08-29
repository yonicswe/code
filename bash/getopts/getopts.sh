#!/bin/bash

usage () 
{
	echo "getopts.sh -r <pcap file> [-c <max packets to process>]"
	exit -1;
} 

get_user_options ()
{

# there is no need to reset OPTIND to 1 
# since this shell script is invoked once 
# and OPTIND is automatically restart on each shell 
# OPTIND=1
	while getopts "c:r:l" opt ; do 
		case $opt in 
		c)
			max_packets="-c $OPTARG"
            echo "c = $OPTARG";
			;;
		r) 
			pcap_file=$OPTARG
            echo "pcap_file = $OPTARG"
			;; 
		l) 
 			log_file=parse_sri_log.txt		
            echo "log_file = $log_file"
 			;; 
		esac
	done

# sanity
	if [ -z $pcap_file ] ; then 
		usage;
	fi


    profile=${!OPTIND};        

    echo "last param : ${profile}";


# to get another parameter other than the ones parsed by getopts
# use the OPTIND variable.
# when getopts finishes parsing parameters its value is the positional number 
# of the last parameter entered.
# with a 2nd level of indirection you can access this value 
# for example if you run this script with         
# ./getopts.sh   -r filename -c 20 yoni         
# OPTIND will be 5 at the end of the parsing         
# then with ${!OPTIND} 
# you access parameter $5 
# which is "yoni" 
# but notice that this works only when its the last parameter     
#        
}



get_user_options $*
