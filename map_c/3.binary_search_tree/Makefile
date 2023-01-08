
CC = gcc

CFLAGS = -c
 

main : main.o binary_tree.o

main.o : main.c binary_tree.c binary_tree.h

binary_tree.o : binary_tree.c binary_tree.h

run : main
	./main

clean :
	$(RM)  *.o main
