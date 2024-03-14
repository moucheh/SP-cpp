#include <iostream>
#include "duration.hpp"

int main() {
	Duration d1{10, 35, 15};
	Duration d2{10, 40, 15};
	std::cout << d1.get_h() << ':' << d1.get_m() << ':' << d1.get_s() << std::endl;
	std::cout << (d1 == d1) << std::endl;
	std::cout << (d1 != d1) << std::endl;
	std::cout << (d1 + Duration{3, 2, 1}) << std::endl;
	std::cout << ((d1 == d1) ? "true" : "false") << std::endl;
	std::cout << ((d1 != d1) ? "true" : "false") << std::endl;
	std::cout << ((d1 > d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 < d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 >= d2) ? "true" : "false") << std::endl;
	std::cout << ((d1 <= d2) ? "true" : "false") << std::endl;
	Duration d3{10, 45, 50};
	Duration d4{4, 25, 30};
	try {
		d4 - d3;
	} catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << Duration("10:30:20") << std::endl;
	return 0;
}
