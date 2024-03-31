#include "WorldCities.hpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout << "Error, no arguments provided, run ./wcp -h to get help\n";
		return 0;
	}
	if (strcmp(argv[1], "--version") == 0 ||
			strcmp(argv[1], "-v") == 0) {
		std::cout << "WorldCitiesParser version: 1.0\n";
		return 0;
	}
	if (strcmp(argv[1], "--help") == 0 ||
			strcmp(argv[1], "-h") == 0) {
		help();
		return 0;
	}
	int input_index = -1;
	for (auto i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0 ||
				strcmp(argv[i], "--input") == 0) {
			input_index = i + 1;
			break;
		}
	}
	if (input_index == -1 || input_index >= argc) {
		std::cout << "Error, input file not specified, run ./wcp -h to get help\n";
		return 1;
	}
	std::ifstream input(argv[input_index]);
	if (!input) {
		std::cout << "Error 404. File not found!\n";
		return 1;
	}
	int option_index = -1;
	for (auto i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0 ||
				strcmp(argv[i], "--option") == 0) {
			option_index = i + 1;
			break;
		}
	}
	if (option_index == -1 || option_index >= argc) {
		std::cout << "Error, option not specified, run ./wcp -h to get help\n";
		input.close();
		return 1;
	}
	int output_index = -1;
	if (strcmp(argv[option_index], "5") != 0) {
		for (auto i = 1; i < argc; i++)
			if (strcmp(argv[i], "-o") == 0 ||
					strcmp(argv[i], "--output") == 0) {
				output_index = i + 1;
				break;
			}
	} else {
		output_index = -2;
	}
	std::ofstream output;
	std::string output_file;
	if (output_index == -2)
		output.close();
	else if (output_index == -1 || output_index >= argc) {
		output.open("output.txt");
		output_file = "output.txt";
	} else {
		output.open(argv[output_index]);
		output_file = argv[output_index];
	}
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
	std::istringstream option_ss{argv[option_index]};
	int choice;
	option_ss >> choice;
	if (choice == 1) {
		std::cout << "Enter country name: ";
		std::string requested_country;
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
		std::cout << "Result outputed to " << output_file << '\n';
	} else if (choice == 2) {
		std::cout << "Enter country name: ";
		std::string requested_country;
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
		std::cout << "Result outputed to " << output_file << '\n';
	} else if (choice == 3) {
		std::sort(
			countries.begin(),
			countries.end(),
		[](auto a, auto b) {
			return a.population > b.population;
		});
		for (const auto& country : countries)
			output << country << "\n\n";
		std::cout << "Result outputed to " << output_file << '\n';
	} else if (choice == 4) {
		for (const auto& country : countries)
			output << country << "\n\n";
		std::cout << "Result outputed to " << output_file << '\n';
	} else if (choice == 5) {
		std::cout << "Enter city name: ";
		std::string requested_city;
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
		std::cout << "Result outputed to " << output_file << '\n';
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
		std::cout << "Result outputed to " << output_file << '\n';
	} else {
		std::cout << "Ivalid option, run ./wcp -h to get help\n";
	}
	output.close();
	input.close();
	return 0;
}