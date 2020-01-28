all: project1

project1: project1main.o project1functions.o
	gcc project1main.o project1functions.o -o project1

project1main.o: project1main.c	
	gcc -ansi -pedantic-errors -Wall -c project1main.c

project1functions: project1functions.c	
	gcc -ansi -pedantic-errors -Wall -c project1functions.c

clean:
	rm -f *.o
