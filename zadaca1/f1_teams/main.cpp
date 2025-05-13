#include "f1_teams.hpp"

int main() {
	std::ifstream input_file("f1_teams.csv");
	if (!input_file) {
		std::cout << "Error 404. File not found!\n";
		return 1;
	}
	std::string titles;
	std::getline(input_file, titles);
	f1_teams raw_f1_teams;
	input_file >> raw_f1_teams;
	f1_teams filtered_f1_teams = raw_f1_teams.filter();
	filtered_f1_teams.sort();
	std::ofstream output_file("f1_teams_sorted.csv");
	output_file << titles << '\n';
	output_file << filtered_f1_teams;
	output_file.close();
	input_file.close();
	return 0;
}