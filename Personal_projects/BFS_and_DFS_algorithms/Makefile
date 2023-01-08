
CC = gcc

CFLAGS = -Wall -pedantic
 

main : main.o graph.o linked_list.o stack.o queue.o

main.o : main.c graph.c graph.h

linked_list.o : linked_list.c linked_list.h

graph.o : graph.c graph.h stack.h queue.h

queue.o : queue.c queue.h

stack.o : stack.c stack.h


run : main
	./main

clean :
	$(RM)  *.o main
