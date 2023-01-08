

CC = gcc

CFLAGS = -Wall -pedantic

main : main.o distance_from_string.o

main.o : main.c distance_from_string.c distance_from_string.h

distance_from_string.o : distance_from_string.c distance_from_string.h

run : main
	./main
	
clean :
	$(RM) main *.o
