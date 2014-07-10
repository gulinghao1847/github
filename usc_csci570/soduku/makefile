object=main.o ReadFile.o SolveSu.o my570list.o
hw5: $(object)
	gcc -o hw5 -g $(object)
main.o: main.c
	gcc -g -c -Wall main.c
ReadFile.o: ReadFile.c ReadFile.h
	gcc -g -c -Wall ReadFile.c
SolveSu.o: SolveSu.h SolveSu.c
	gcc -g -c -Wall SolveSu.c
my570list.o: my570list.h my570list.c
	gcc -g -c -Wall my570list.c
clean:
	rm -f $(object) hw5
