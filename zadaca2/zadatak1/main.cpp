#include <iostream>
#include "MojVektor.hpp"
#include <string>

int main() {
	MojVektor<std::string> helo;
	for (auto i = 0; i < 15; i++) {
		helo.push_back("Muhamed");
	}
	helo.insert(helo.begin() + 5, "Amar");
	helo.insert(helo.begin() + 11, "Mahir");
	helo.insert(helo.begin() + 10, "Edin");
	std::cout << helo << std::endl;
	return 0;
}
