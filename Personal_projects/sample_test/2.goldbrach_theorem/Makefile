
CC = gcc

CFLAGS = -Wall -pedantic


main : main.o goldbrach_theorem.o

main.o : main.c goldbrach_theorem.c goldbrach_theorem.h

goldbrach_theorem.o : goldbrach_theorem.c goldbrach_theorem.h

run : main
	./main
	
clean :
	$(RM) main *.o
