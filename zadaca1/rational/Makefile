all: main.o Rational.o
	clang++ main.o Rational.o -o main
	
main.o: main.cpp
	clang++ -c main.cpp

Rational.o: Rational.cpp
	clang++ -c Rational.cpp

clean:
	rm -rf *.o