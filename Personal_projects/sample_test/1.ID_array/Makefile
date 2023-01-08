
CC = gcc

CFLAGS = -Wall -pedantic


main : main.o IDs_managment.o

main.o : main.c IDs_managment.c IDs_managment.h

IDs_managment.o : IDs_managment.c IDs_managment.h

run : main
	./main
	
clean :
	$(RM) main *.o
