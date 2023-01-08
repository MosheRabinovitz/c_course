
CC = gcc

CFALGS = -c


main : main.o 	sub_arrays.o


main.o : main.c sub_arrays.h

sub_arrays.o : sub_arrays.c sub_arrays.h

run : main
	./main
	
clean : 
	$(RM) *.o ./main
