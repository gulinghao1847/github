for i in node01 node02 node03 node04 192.168.100.5 192.168.100.6 192.168.100.7; do
	ssh $i rm -rf /home/localadmin/503Project
	scp -r /home/localadmin/503Project localadmin@$i:/home/localadmin/
done
