CC = gcc

CFLAGS = -c
 

main : main.o functions.o

main.o : main.c functions.c question_6.h

functions.o : functions.c question_6.h



run : main
	./main

clean :
	$(RM)  *.o main