for i in 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288
do
echo "start $i" 
./quicksort_pthread $i 2 >> data2.txt;
done
