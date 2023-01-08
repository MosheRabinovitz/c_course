GCC=/usr/bin/gcc

-I = scrips/

simplefs: scrips/shell.o scrips/fs.o scrips/disk.o
	$(GCC) scrips/shell.o scrips/fs.o scrips/disk.o  -o simplefs

shell.o: scrips/shell.c
	$(GCC) -Wall scrips/shell.c -c -o scrips/shell.o -g

fs.o: scrips/fs.c scrips/fs.h
	$(GCC) -Wall scrips/fs.c -c -o scrips/fs.o -g
	
disk.o: scrips/disk.c scrips/disk.h
	$(GCC) -Wall scrips/disk.c -c -o scrips/disk.o -g


clean:
	rm simplefs scrips/disk.o scrips/fs.o scrips/shell.o
