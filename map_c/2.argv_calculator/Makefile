
CC = gcc

CFLAGS = -c
 

main : main.o calculator.o

main.o : main.c calculator.c calculator.h

calculator.o : calculator.c calculator.h

run : main
	./main

clean :
	$(RM)  *.o main