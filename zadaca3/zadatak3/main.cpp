#include <iostream>
#include "TripPlanner.hpp"

int main() {
	TripPlanner tp;

	int option;
	std::cout << "Trip Planner" << std::endl;
	while (true) {
		menu();
		std::cin >> option;
		if (option == 1) {
			Location l;

			std::cout << "Enter location name: ";
			std::cin.ignore();
			std::getline(std::cin, l.name);

			std::cout << "Enter location latitude: ";
			std::cin >> l.latitude;

			std::cout << "Enter location logitude: ";
			std::cin >> l.longitude;
			tp.addLocation(std::move(l));
		} else if (option == 2) {
			std::string stop;

			std::cout << "Enter stop name: ";
			std::cin.ignore();
			std::getline(std::cin, stop);

			if (tp.addStop(std::move(stop))) {
				std::cout << "Stop added successfully!\n" << std::endl;
			} else {
				std::cout << "Failed to add stop, invalid location!\n" << std::endl;
			}
		} else if (option == 3) {
			std::string stop;
			std::string before;

			std::cout << "Enter stop name: ";
			std::cin.ignore();
			std::getline(std::cin, stop);

			std::cout << "Insert before: ";
			std::getline(std::cin, before);

			if (tp.insertStop(std::move(stop), std::move(before))) {
				std::cout << "Stop inserted successfully!\n" << std::endl;
			} else {
				std::cout << "Failed to insert stop, either the location is invalid or already exists!\n" << std::endl;
			}

		} else if (option == 4) {
			std::string remove;

			std::cout << "Enter stop name to remove: ";
			std::cin.ignore();
			std::getline(std::cin, remove);

			if (tp.removeStop(std::move(remove))) {
				std::cout << "Stop removed successfully!\n" << std::endl;
			} else {
				std::cout << "Failed to remove stop, location not found!\n" << std::endl;
			}
		} else if (option == 5) {
			tp.print(1, std::cout);
		} else if (option == 6) {
			std::cout << "Trip distance: " << tp.calculateDistance() << "km" << std::endl;
		} else if (option == 7) {
			tp.renderTrip();
		} else if (option == 8) {
			tp.print(0, std::cout);
		} else if (option == 0) {
			break;
		} else {
			break;
		}
	}
	return 0;
}