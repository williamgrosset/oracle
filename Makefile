.PHONY all:
all:
	gcc -Wall diskhelper.c diskinfo.c -o diskinfo.o
	gcc -Wall diskhelper.c disklist.c -o disklist.o
	gcc -Wall diskhelper.c diskget.c -o diskget.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
