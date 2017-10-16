all: GroupX

GroupX : structures.o affectation.o main.o
	gcc -o GroupX  structures.o affectation.o main.o -g -v -pg

structures.o: structures.c
	gcc -o structures.o -c structures.c -W -Wall -ansi -pedantic
	
	
affectation.o: affectation.c
	gcc -o affectation.o -c affectation.c -W -Wall -ansi -pedantic
	

main.o: main.c affectation.h 
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic -g


clean:
	rm -rf *.o

mrproper: clean
	rm -rf GroupX
