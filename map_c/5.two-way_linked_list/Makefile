
CC = gcc

CFLAGS = -c
 

main : main.o linked_list.o

main.o : main.c linked_list.c linked_list.h

linked_list.o : linked_list.c linked_list.h

run : main
	./main

clean :
	$(RM)  *.o main