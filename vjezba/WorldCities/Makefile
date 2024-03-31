all: main.o WorldCities.o
	g++ main.o WorldCities.o -o wcp

main.o: main.cpp
	g++ -c main.cpp

WorldCities.o: WorldCities.cpp
	g++ -c WorldCities.cpp
	
clean:
	rm -rf *.o