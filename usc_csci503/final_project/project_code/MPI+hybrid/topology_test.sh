for i in 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288; do
		echo "number: $i"
		#mpirun --hostfile hosts -np 8 ./quicksort_topology $i 8 >> data_topology_2.txt;
		mpirun --hostfile hosts -np 8 ./quicksort_MPI $i 8 >>data_topology_3.txt;
done
