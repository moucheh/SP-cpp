#include "WorldCities.hpp"

int main() {
	std::ifstream input("WorldCities.csv");
	if (!input) {
		std::cout << "Error 404. File not found!";
		return 1;
	}
	std::ofstream output("output.txt");
	std::string titles;
	std::getline(input, titles);
	std::string entry;
	WorldCities cities;
	while (std::getline(input, entry)) {
		std::istringstream iss(entry);
		iss >> cities;
	}
	std::map<std::string, WorldCities> countriesSorted;
	for (const auto& city : cities)
		countriesSorted[city.country].push_back(city);
	std::vector<Country> countries;
	for (const auto& [country, cities] : countriesSorted) {
		Country newCountry;
		newCountry.name = country;
		newCountry.largest_city = &cities[0];
		for (const auto& city : cities) {
			if (city.status == "primary")
				newCountry.capital = &city;
			if (newCountry.largest_city->population < city.population)
				newCountry.largest_city = &city;
			newCountry.population += city.population;
			++newCountry.number_of_cities;
		}
		countries.push_back(newCountry);
	}
	menu();
	int choice;
	std::cin >> choice;
	const char* message = "Result outputed to output.txt\n";
	if (choice == 1) {
		std::cout << "Enter country name: ";
		std::string requested_country;
		std::cin.ignore();
		std::getline(std::cin, requested_country);
		if (countriesSorted[requested_country].empty()) {
			std::cout << "Invalid country.\n";
			input.close();
			output.close();
			return 1;
		}
		std::sort(
			countriesSorted[requested_country].begin(),
			countriesSorted[requested_country].end(),
		[](auto a, auto b) {
			return a.population > b.population;
		});
		for (const auto& city : countriesSorted[requested_country])
			output << city << "\n\n";
		std::cout << message;
	} else if (choice == 2) {
		std::cout << "Enter country name: ";
		std::string requested_country;
		std::cin.ignore();
		std::getline(std::cin, requested_country);
		if (countriesSorted[requested_country].empty()) {
			std::cout << "Invalid country.\n";
			input.close();
			output.close();
			return 1;
		}
		std::sort(
			countriesSorted[requested_country].begin(),
			countriesSorted[requested_country].end(),
		[](auto a, auto b) {
			return a.name < b.name;
		});
		for (const auto& city : countriesSorted[requested_country])
			output << city << "\n\n";
		std::cout << message;
	} else if (choice == 3) {
		std::sort(
			countries.begin(),
			countries.end(),
		[](auto a, auto b) {
			return a.population > b.population;
		});
		for (const auto& country : countries)
			output << country << "\n\n";
		std::cout << message;
	} else if (choice == 4) {
		for (const auto& country : countries)
			output << country << "\n\n";
		std::cout << message;
	} else if (choice == 5) {
		std::cout << "Enter city name: ";
		std::string requested_city;
		std::cin.ignore();
		std::getline(std::cin, requested_city);
		bool found = false;
		for (const auto& city : cities)
			if (city.name == requested_city) {
				std::cout << '\n' << city << '\n';
				found = true;
				break;
			}
		if (!found) {
			std::cout << "Invalid city.\n";
			input.close();
			output.close();
			return 1;
		}
	} else if (choice == 6) {
		const std::string separator(75, '-');
		output << separator << '\n'
			   << "Capital" << std::string(23, ' ')
			   << "| Country\n"
			   << separator << '\n';
		for (const auto& country : countries) {
			const std::string white_space(30 - utf8_length(country.capital->name), ' ');
			output << country.capital->name
				   << white_space << "| "
				   << country.name << '\n'
				   << separator << '\n';
		}
		std::cout << "Result outputed to output.txt\n";
	} else if (choice == 7) {
		const std::string separator(90, '-');
		output << separator << '\n'
			   << "Largest City" << std::string(18, ' ')
			   << "| Population" << std::string(7, ' ')
			   << "| Country\n"
			   << separator << '\n';
		for (const auto& country : countries) {
			const std::string white_space_pop(
				30 - utf8_length(country.largest_city->name), ' ');
			const std::string white_space_ctry(
				15 - std::to_string(country.largest_city->population).size(), ' ');
			output << country.largest_city->name
				   << white_space_pop << "| "
				   << country.largest_city->population
				   << white_space_ctry << "  | "
				   << country.name << '\n'
				   << separator << '\n';
		}
		std::cout << "Result outputed to output.txt\n";
	}
	input.close();
	output.close();
	return 0;
}