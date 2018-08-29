#!/bin/bash

while getopts "d:m:l:i:s:k:a:" opt; do
	case ${opt} in

		l)
			echo Setting logger to ${OPTARG} 
			rep_mset voltaire/modules/logger/ debug-level  ${OPTARG}
			;;

   		i)
			echo Setting itarget to ${OPTARG} 
			rep_mset voltaire/modules/itarget/ debug-level ${OPTARG}
			if (( ${OPTARG} > 3  )) ; then 
				echo + all > /proc/voltaire/itarget/trace
			else
				echo - all > /proc/voltaire/itarget/trace
			fi
			;;
   		d)
			echo Setting iser data to ${OPTARG} 
			echo data ${OPTARG} > /proc/voltaire/iser/trace
			;;
		m)
			echo Setting scsimap to ${OPTARG} 
			rep_mset voltaire/modules/scsimap/ debug-level ${OPTARG}
			;;
   		s)
			echo Setting iser_dm to ${OPTARG} 
			rep_mset voltaire/modules/iser_dm/ debug-level ${OPTARG}
			if (( ${OPTARG} > 3  )) ; then 
				echo + all > /proc/voltaire/iser/trace
			else
				echo - all > /proc/voltaire/iser/trace
			fi
			;;
   		k)
			echo Setting kdapl to ${OPTARG} 
			if (( ${OPTARG} > 3  )) ; then 
				echo + all > /proc/voltaire/kdapl/debug
			else
				echo - all > /proc/voltaire/kdapl/debug
			fi
			rep_mset voltaire/modules/kdapl/ debug-level ${OPTARG}
			;;
		a)
			if (( ${OPTARG} == 0 )) ; then 
				echo - all > /proc/voltaire/itarget/trace
				echo - all > /proc/voltaire/iser/trace 
				echo - all > /proc/voltaire/kdapl/debug 
			else
				echo "Setting all levels to ${OPTARG}" 
				rep_mset voltaire/modules/logger/ debug-level ${OPTARG}
				rep_mset voltaire/modules/itarget/ debug-level ${OPTARG}
				rep_mset voltaire/modules/scsimap/ debug-level ${OPTARG}
				rep_mset voltaire/modules/iser_dm/ debug-level ${OPTARG}
				rep_mset voltaire/modules/kdapl/ debug-level ${OPTARG}
				if (( ${OPTARG} > 3  )) ; then 
					echo + all > /proc/voltaire/itarget/trace
					echo + all > /proc/voltaire/iser/trace 
					echo + all > /proc/voltaire/kdapl/debug 
				else 
					echo - all > /proc/voltaire/itarget/trace
					echo - all > /proc/voltaire/iser/trace 
					echo - all > /proc/voltaire/kdapl/debug 
				fi
			fi
			;;
		*)
			echo "Usage: -l : logger level"
			echo "Usage: -i : itarget log level"
			echo "Usage: -m : scsimap log level"
			echo "Usage: -s : iser log level"
			echo "Usage: -d : iser pdu data size to print"
			echo "Usage: -k : kdapl log level"
			echo "Usage: -a : all log levels"
			;;
			
	esac
done

