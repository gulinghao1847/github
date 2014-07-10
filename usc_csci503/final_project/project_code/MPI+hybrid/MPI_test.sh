for j in 2 3 4 5 6 7 8; do

	for i in 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288; do
		echo "host number:  $j size: $i" 
		mpirun --hostfile hosts -np $j ./quicksort_MPI $i $j >> data_MPI.txt;
	done
done
