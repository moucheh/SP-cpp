#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cstring>

struct WorldCity {
	std::string name;
	double latitude;
	double longitude;
	std::string country;
	std::string status;
	size_t population;
	size_t id;
};

struct WorldCities : public std::vector<WorldCity> {
	void input(std::istream& is);
};

struct Country : public std::vector<WorldCity> {
	std::string name;
	const WorldCity* capital;
	const WorldCity* largest_city;
	size_t population{};
	size_t number_of_cities{};
};

std::ostream& operator<<(std::ostream& os, const Country& country);
std::ostream& operator<<(std::ostream& os, const WorldCity& city);
std::ostream& operator<<(std::ostream& os, const WorldCities& cities);
std::istream& operator>>(std::istream& is, WorldCities& cities);

void help();
int utf8_length(const std::string& s);
