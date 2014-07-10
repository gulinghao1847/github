object=main.o arrival_thread.o my402list.o token_arrival.o server_thread.o statistics.o 402_warmup2_time.o header.o
warmup2: $(object)
	gcc -lpthread -lm -o warmup2 -g $(object)
main.o: main.c
	gcc -g -c -Wall main.c
arrival_thread.o: arrival_thread.c arrival_thread.h
	gcc -g -c -Wall arrival_thread.c
header.o: header.c header.h
	gcc -g -c -Wall header.c
my402list.o: my402list.c my402list.h cs402.h
	gcc -g -c -Wall my402list.c
token_arrival.o: token_arrival.c token_arrival.h
	gcc -g -c -Wall token_arrival.c
server_thread.o: server_thread.c server_thread.h
	gcc -g -c -Wall server_thread.c
statistics.o: statistics.c statistics.h
	gcc -g -c -Wall statistics.c
402_warmup2_time.o: 402_warmup2_time.c 402_warmup2_time.h
	gcc -g -c -Wall 402_warmup2_time.c
clean:
	rm -f $(object) warmup2
