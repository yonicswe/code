#!/bin/bash
num_of_machines=$(cat remoteDeskDB.sh | sed '/^$/d' |wc -l)

# hosts=()
hosts_ip=()
hosts_user=()
hosts_pass=()

declare -a hosts
# declare -a hosts_ip
# declare -a hosts_user
# declare -a hosts_pass
# declare -i i

# i=0

set -x

#   cat remoteDeskDB.sh | sed '/^$/d' | awk '{print $1" "$2" "$3" "$4}'  | while read x1 x2 x3 x4 ; do 
# cat remoteDeskDB.sh |
while read x1 x2 x3 x4 ; do
      i=$(($i+1)) ;
#     echo "$i: $x1,$x2,$x3,$x4" ; 
#     hosts=( $(echo "${hosts[*]}  $x1" ))
#       eval hosts_ip[$i]=$x1
#     hosts_user[$i]=$x3
#     hosts_pass[$i]=$x4

#     eval hosts[$i]="$x1"
     eval hosts+=("$x1")
#     eval hosts_ip+=("$x2")
#     eval hosts_user+=("$x3")
#     eval hosts_pass+=("$x4")
 done < <(cat remoteDeskDB.sh)
#     done      

set +x 

echo "hosts[] = ${hosts[@]}"
# echo "hosts_ip[] = ${hosts_ip[@]}"
# echo "hosts_user[] = ${hosts_user[@]}"
# echo "hosts_pass[] = ${hosts_pass[@]}"

# for ((i=0; i<num_of_machines; i++)) ; do 
#     ${hosts[$i]}=awk
# done
