object=main.o readBin.o queue.o unionFind.o readMaze.o mazeGen.o mazeSoluGen.o mazeSolu.o
hw4: $(object)
	gcc -o hw4 -g $(object)
main.o: main.c
	gcc -g -c -Wall main.c
readBin.o: readBin.c read.h
	gcc -g -c -Wall readBin.c
readMaze.o: read.h readMaze.c
	gcc -g -c -Wall readMaze.c
queue.o: queue.h queue.c
	gcc -g -c -Wall queue.c
unionFind.o: unionFind.h unionFind.c
	gcc -g -c -Wall unionFind.c
mazeGen.o: maze.h mazeGen.c
	gcc -g -c -Wall mazeGen.c mazeSoluGen.c
mazeSoluGen.o: mazeSoluGen.c maze.h
	gcc -g -c -Wall mazeSoluGen.c
mazeSolu.o: mazeSolu.c maze.h
	gcc -g -c -Wall mazeSolu.c
clean:
	rm -f $(object) hw4
