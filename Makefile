.PHONY all:
all:
	gcc -Wall diskinfo.c -o diskinfo.o
	gcc -Wall disklist.c -o disklist.o
	gcc -Wall diskget.c -o diskget.o
	gcc -Wall diskput.c -o diskput.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
