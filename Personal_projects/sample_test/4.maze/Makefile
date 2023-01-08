

CC = gcc

CFLAGS = -Wall -pedantic

main : main.o maze.o

main.o : main.c maze.c maze.h

maze.o : maze.c maze.h

run : main
	./main
	
clean :
	$(RM) main *.o
