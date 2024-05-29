#pragma once

extern const double PI;
extern const double IMAGEWIDTH;
extern const double IMAGEHEIGHT;
extern const double NORTHEDGE;
extern const double SOUTHEDGE;
extern const double WESTEDGE;
extern const double EASTEDGE;

#include "../zadatak1/DoubleLinkedList.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

#include <cmath>

#include <string>

void menu();

struct Location {
	std::string name;
	double longitude{};
	double latitude{};
};

class TripPlanner {
public:
	TripPlanner();

	template<typename F>
	void addLocation(F&&);

	bool addStop(std::string&&);

	bool removeStop(std::string&&);

	void print(int, std::ostream&);

	double calculateDistance();

	bool insertStop(std::string&&, std::string&&);

	void renderTrip();
private:
	DoubleLinkedList<Location> locations;
	DoubleLinkedList<Location> trip;
};

template<typename F>
void TripPlanner::addLocation(F&& loc) {
	locations.push_back(std::forward<F>(loc));
}