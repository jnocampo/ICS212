all: project2

project2: project2main.o llist.o
	g++ project2main.o llist.o -o project2

project2main.o: project2main.cpp	
	g++ -ansi -pedantic-errors -Wall -c project2main.cpp

llist: llist.cpp	
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

clean:
	rm -f *.o
