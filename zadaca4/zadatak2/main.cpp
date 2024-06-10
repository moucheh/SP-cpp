#include <iostream>
#include "Map.hpp"
#include <cstdlib>

int main() {
	srand(time(NULL));

	Map<int, int> m;

	std::cout << "empty: " << ((m.empty()) ? "true" : "false") << std::endl;

	for (auto i = 0; i < 20; ++i) {
		auto t = rand() % 99 + 1;

		try {
			m.insert(t, t * 10);
		} catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}

	m[5] = 500;

	std::cout << m << std::endl;

	std::cout << "empty: " << ((m.empty()) ? "true" : "false") << std::endl;

	std::cout << "size: " << m.size() << std::endl;

	std::cout << "Key 10 " << ((m.find(10) != nullptr) ? "was found" : "wasn't found") << std::endl;
	std::cout << "Key 4 " << ((m.find(4) != nullptr) ? "was found" : "wasn't found") << std::endl;


	try {
		m.at(150);
	} catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << ((m.erase(5) ? "Successfully deleted key 5." : "Element whose key is 5 was not found.")) << std::endl;

	std::cout << ((m.erase(56) ? "Successfully deleted key 56." : "Element whose key is 56 was not found.")) << std::endl;

	std::cout << ((m.erase(100) ? "Successfully deleted key 100." : "Element whose key is 100 was not found.")) << std::endl;

	std::cout << m << std::endl;

	Map<int, int> m1;
	m1 = m;
	auto m2 = std::move(m);

	std::cout << m1 << std::endl;

	std::cout << m2 << std::endl;

	return 0;
}