.PHONY all:
all:
	gcc -D PART1 parts.c -o diskinfo.o
	gcc -D PART2 parts.c -o disklist.o
	gcc -D PART3 parts.c -o diskget.o
	gcc -D PART4 parts.c -o diskput.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
