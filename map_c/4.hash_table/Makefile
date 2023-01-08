
CC = gcc

CFLAGS = -c
 

main : main.o HASH.o

main.o : main.c hash_table.h

HASH.o : HASH.c hash_table.h

run : main
	./main

clean :
	$(RM)  *.o main