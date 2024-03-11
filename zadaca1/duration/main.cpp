#include <iostream>
#include "duration.hpp"

int main() {
	// ovdje možete samostalno testirati neke funkcionalnosti.
	// Napomena: main.cpp se ne pregleda, sva implementacija
	// ide u duration .cpp i .hpp fileove.
	Duration d1{10, 45, 50};
	Duration d3{4, 25, 30};
	Duration d2{10, 40, 15};
	std::cout << ((d1 != d1) ? "true" : "false") << std::endl;
	std::cout << ((d1 == d1) ? "true" : "false") << std::endl;
	std::cout << ((d1 > d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 < d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 >= d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 <= d2) ? "true" : "false") << std::endl;
	try {
		d3 - d1;
	} catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << Duration("10:30:20") << std::endl;
	return 0;
}
