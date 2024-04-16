run:
	./library

all: main.o Book.o Library.o User.o
	g++ main.o Book.o Library.o User.o -o library

main: main.o
	g++ -c main.cpp

Book: Book.o
	g++ -c Book.cpp

Library: Library.o
	g++ -c Library.cpp

User: User.o
	g++ -c User.cpp

clean:
	rm -f *.o library