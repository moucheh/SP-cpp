#include "TripPlanner.hpp"

const double PI = 3.141592;
const double IMAGEWIDTH = 1063.;
const double IMAGEHEIGHT = 1014.;
const double NORTHEDGE = 45.4;
const double SOUTHEDGE = 42.4;
const double WESTEDGE = 15.5;
const double EASTEDGE = 19.9;

void menu() {
	std::cout << "Choose your option number:\n"
			  << "1. Add Location\n"
			  << "2. Add Stop\n"
			  << "3. Insert Stop\n"
			  << "4. Remove Stop\n"
			  << "5. Print Trip\n"
			  << "6. Show Trip Distance\n"
			  << "7. Render Trip\n"
			  << "8. Print Locations\n"
			  << "0. Exit\n"
			  << "Option: ";
}

void TripPlanner::print(int op, std::ostream& out) {
	DoubleLinkedList<Location>* locations_to_print;
	if (op == 0)
		locations_to_print = &locations;
	else if (op == 1)
		locations_to_print = &trip;

	if (locations_to_print->empty()) {
		std::cout << "The list is empty." << std::endl;
		return;
	}

	static const std::string separator(50, '=');
	out << std::endl;
	for (const auto& location : *locations_to_print) {
		out << "Name: " << location.name << '\n'
			<< "Latitude: " << location.latitude << '\n'
			<< "Longitude: " << location.longitude << '\n'
			<< separator << '\n';
	}
}

TripPlanner::TripPlanner() {
	std::ifstream input("locations.txt");

	if (!input) {
		std::cout << "404 File not found." << std::endl;
		exit(1);
	}

	std::string entry;

	while (std::getline(input, entry)) {
		std::istringstream iss{entry};
		Location l;
		std::getline(iss, l.name, ':');
		char c;
		iss >> l.latitude >> c >> l.longitude;
		addLocation(std::move(l));
	}

	input.close();
}

bool TripPlanner::addStop(std::string&& stop) {
	auto it = locations.find_if([&stop](const Location & loc) { return loc.name == stop; });
	if (it != locations.end()) {
		trip.push_back(*it);
		return true;
	}
	return false;
}

bool TripPlanner::insertStop(std::string&& stop, std::string&& before) {
	std::cout << stop << ' ' << before << std::endl;

	auto it = locations.find_if([&stop](const Location & loc) { return loc.name == stop; });
	auto jt = trip.find_if([&before](const Location & loc) { return loc.name == before; });

	if (it == locations.end()) return false;
	if (jt == trip.end()) return false;

	trip.insert(jt, *it);

	return true;
}

bool TripPlanner::removeStop(std::string&& remove) {
	auto it = trip.find_if([&remove](const Location & loc) { return loc.name == remove; });
	if (it == trip.end()) return false;

	trip.erase(it);

	return true;
}

double TripPlanner::calculateDistance() {
	if (trip.empty() || trip.size() == 1) {
		return 0.0;
	}

	double d = 0.;

	auto it = trip.begin();
	auto jt = std::next(it);

	while (jt != trip.end()) {
		double lat1 = it->latitude * PI / 180;
		double long1 = it->longitude * PI / 180;
		double lat2 = jt->latitude * PI / 180;
		double long2 = jt->longitude * PI / 180;

		d += 6378.8 * acos((sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 - long1));
		++it;
		++jt;
	}

	return d;
}

void TripPlanner::renderTrip() {
	if (trip.empty() || trip.size() == 1) {
		std::cout << "Insufficient amount of stops to render!" << std::endl;
		return;
	}

	std::ifstream input("outputTemplateP1.html");

	if (!input) {
		std::cout << "Error opening outputTemplateP1.html!" << std::endl;
		return;
	}

	std::string line;

	std::ofstream output("output.html");

	while (std::getline(input, line)) {
		output << line << '\n';
	}


	double x1, x2, y1, y2;

	auto it = trip.begin();
	auto jt = std::next(it);

	while (jt != trip.end()) {

		x1 = (it->longitude - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
		y1 = (it->latitude - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;

		x2 = (jt->longitude - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
		y2 = (jt->latitude - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;

		output << "\t\t\t<line x1=\""
			   << x1 << "\" y1=\"" << y1 << "\" x2=\""
			   << x2 << "\" y2=\"" << y2
			   << "\" stroke=\"orange\" stroke-width=\"4\"></line>\n";
		++it;
		++jt;
	}

	double x, y;

	int i = 1;

	for (const auto& stop : trip) {
		x = (stop.longitude - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
		y = (stop.latitude - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;
		output << "\t\t\t<text x=\""
			   << x << "\" y=\""
			   << y << "\""
			   << " dx=\"-20\" dy=\"-20\">"
			   << stop.name << "</text>\n"
			   << "\t\t\t<circle fill=\"red\""
			   << "cx=\"" << x
			   << "\" cy=\"" << y
			   << "\" r=\"8\">"
			   << "</circle>\n"
			   << "\t\t\t<text x=\"" << x << "\" "
			   << "y=\"" << y << "\""
			   << " fill=\"white\" dx=\"-5\" dy=\"5\">"
			   << i << "</text>\n"
			   ;
		++i;
	}

	output << "</svg>";

	output.close();
	input.close();
}
