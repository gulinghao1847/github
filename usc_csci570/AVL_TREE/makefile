object=main.o print_tree.o bst.o avl_tree.o
hw3: $(object)
	gcc -o hw3 -g $(object)
main.o: main.c
	gcc -g -c -Wall main.c
print_tree.o: print_tree.h print_tree.c
	gcc -g -c -Wall print_tree.c
bst.o: bst.c bst.h
	gcc -g -c -Wall bst.c
avl_tree.o: avl_tree.c avl_tree.h
	gcc -g -c -Wall avl_tree.c
clean:
	rm -f $(object) hw3