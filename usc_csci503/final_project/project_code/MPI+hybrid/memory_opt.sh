for i in 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 
do
./quicksort_MemoryOpt 1048576 $i >> memory.txt;
done
