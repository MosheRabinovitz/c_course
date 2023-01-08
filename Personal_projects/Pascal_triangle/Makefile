
CC = gcc

CFALGS = -c

main : main.o functions.o

main.o : main.c Pascal.h

functions.o : functions.c Pascal.h

run : main
	./main

clean : 
	$(RM) *.o ./main
