for i in 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 
do
echo "start $i" 
./quicksort_MemoryOpt 524288 $i #>> memory.txt;
done
