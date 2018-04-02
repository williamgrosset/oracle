.PHONY all:
all:
	gcc -Wall diskstructs.c diskinfo.c -o diskinfo.o
	gcc -Wall diskstructs.c disklist.c -o disklist.o
	gcc -Wall diskstructs.c diskget.c -o diskget.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
