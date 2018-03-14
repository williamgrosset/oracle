.phony setup:
setup: file_system 

file_system: file_system.c
	gcc -pthread file_system.c -o file_system.o

run: file_system.o
	./file_system.o

.PHONY clean:
clean:
	rm -rf *.o *.exe
