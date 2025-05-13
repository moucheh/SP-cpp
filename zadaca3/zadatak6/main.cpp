#include <iostream>
#include "PostfixCalc.hpp"

int main() {
	while (true) {
		std::cout << "Enter expression: ";
		std::string input;
		std::getline(std::cin, input);

		try {
			PostfixCalc pfc(std::move(input));

			std::cout << "Result: " << pfc << std::endl;
		} catch (const std::runtime_error& err) {
			std::cout << err.what() << std::endl;
		}

	}
	return 0;
}