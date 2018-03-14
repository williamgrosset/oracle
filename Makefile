.PHONY setup:
all:
	gcc -Wall -D PART1 parts.c -o diskinfo.o
	gcc -Wall -D PART2 parts.c -o disklist.o
	gcc -Wall -D PART3 parts.c -o diskget.o
	gcc -Wall -D PART4 parts.c -o diskput.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
