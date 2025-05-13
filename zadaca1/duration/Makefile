all: main.o duration.o
	clang++ main.o duration.o -o main
	
main.o: main.cpp
	clang++ -c main.cpp

duration.o: duration.cpp
	clang++ -c duration.cpp

clean:
	rm -rf *.o