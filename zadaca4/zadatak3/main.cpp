#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
	std::map<std::string, std::vector<int>> m;

	std::string input;

	auto i = 0;

	while (std::cin >> input) {
		m[input].push_back(i);
		i += input.length() + 1;
	}

	for (const auto& [key, value] : m) {
		std::cout << "Rijec je '" << key << "' i nalazi se na sljedecim pozicijama: " << '\n';
		for (const auto& el : value) {
			std::cout << el << ", ";
		}
		std::cout << '\n';
	}

	return 0;
}