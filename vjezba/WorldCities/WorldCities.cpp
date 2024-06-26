#include "WorldCities.hpp"

void WorldCities::input(std::istream& is) {
	std::string entry;
	WorldCity city;
	while (std::getline(is, entry)) {
		std::istringstream iss(entry);
		iss.ignore();
		std::getline(iss, city.name, '"');
		iss.ignore(2);
		iss >> city.latitude;
		iss.ignore(3);
		iss >> city.longitude;
		iss.ignore(3);
		std::getline(iss, city.country, '"');
		iss.ignore(2);
		std::getline(iss, city.status, '"');
		iss.ignore(2);
		iss >> city.population;
		iss.ignore(3);
		iss >> city.id;
	}
	push_back(city);
}

std::ostream& operator<<(std::ostream& os, const Country& country) {
	const std::string separator(50, '-');
	os << separator << '\n'
	   << " Name             | " << country.name << '\n'
	   << separator << '\n'
	   << " Capital          | " << country.capital->name << '\n'
	   << separator << '\n'
	   << " Largest city     | " << country.largest_city->name << '\n'
	   << separator << '\n'
	   << " Population       | " << country.population << '\n'
	   << separator << '\n'
	   << " Number of cities | " << country.number_of_cities << '\n'
	   << separator << '\n';
	return os;
}


std::ostream& operator<<(std::ostream& os, const WorldCity& city) {
	const std::string separator(50, '-');
	os << separator << '\n'
	   << " Name       | " << city.name << '\n'
	   << separator << '\n'
	   << " Latitude   | " << city.latitude << '\n'
	   << separator << '\n'
	   << " Longitude  | " << city.longitude << '\n'
	   << separator << '\n'
	   << " Country    | " << city.country << '\n'
	   << separator << '\n'
	   << " Status     | " << city.status << '\n'
	   << separator << '\n'
	   << " Population | " << city.population << '\n'
	   << separator << '\n'
	   << " ID         | " << city.id << '\n'
	   << separator << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, WorldCities& cities) {
	cities.input(is);
	return is;
}

void help() {
	std::cout << "--WorldCitiesParser--\n"
			  << "Usage:\n"
			  << "./wcp [options...]\n"
			  << " -i, --input <path_to_file>   Specify path to input file\n"
			  << " -o, --output <path_to_file>  Specify path to output file\n"
			  << " -p, --option <number>        Specify option by number\n"
			  << " -v, --version                Print version\n"
			  << " -h, --help                   Print help\n"
			  << "  1, Print all cities from a country sorted by population\n"
			  << "  2, Print all cities from a country sorted A-Z\n"
			  << "  3, Print all countries sorted by population\n"
			  << "  4, Print all countries sorted A-Z\n"
			  << "  5, Print a city by name to stdout\n"
			  << "  6, Print all capital cities\n"
			  << "  7, Print all largest cities\n";
}

int utf8_length(const std::string& s) {
	int len = 0;
	for (const auto& c : s)
		len += (c & 0xc0) != 0x80;
	return len;
}