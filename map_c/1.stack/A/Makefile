CC = gcc

CFALGS = -c

main : main.o stack.o

main.o : main.c stack.c stack.h

stack.o : stack.c stack.h

run : main
	./main

clean : 
	$(RM) *.o ./main