 
lun_size=41943040 
(( last_block= lun_size -1 ))
(( part_size=($lun_size/4) ))

echo part_size=$part_size, lun_size=$lun_size, last_block=$last_block

for ((i=0,part_start=0, part_end=part_start+part_size ; 
	i<4  ; 
	i+=1,part_start+=part_size+1, part_end=part_start+part_size )); do

	if (( part_end < last_block)); then
		echo "i=$i; part_start=$part_start; part_end=$part_end"
	else
		echo "ii=$i;  part_start=$part_start; part_end=$last_block"
	fi
done
