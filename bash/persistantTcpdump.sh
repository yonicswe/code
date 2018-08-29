#!/bin/bash
done=0
pcapFileName="locationFromApp"
tcpDumpArgs="-i eth1"

catchINTSignal ()
{
	done=1;
	echo "killall -9 tcpdump";
	killall -9 tcpdump;
}

trap catchINTSignal TERM SIGINT SIGTERM


main()
{
    local count=0;
    local ret=0;
    local execute=1;

	while (( ${done} ==  0 )) ; do

        if (( ${execute} == 1 )) ; then
            execute=0;

            # preapare pcap file name
            (( count ++ ));
            now=$(date +"%m%d%H%M%S");
            f=${pcapFileName}.${now}.${count}.pcap;

            # execute
            tcpdump ${tcpDumpArgs} -w ${f} & 
            echo "tcpdump started with pcap file ${f}";
        fi

		sleep 5;

        # check if tcpdump is still running
        pgrep tcpdump > /dev/null;
        ret=$?;
        if (( ${ret} != 0 )) ; then
            execute=1;
        fi

	done

	return;
}

main
