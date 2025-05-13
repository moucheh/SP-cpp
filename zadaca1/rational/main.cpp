#include "Rational.hpp"

int main() {
	std::string input;
	while (std::cin >> input) {
		try {
			Rational temp(input);
			std::cout << temp << '\n';
		} catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << ((Rational("4/3") == "4/3") ? "true" : "false") << std::endl;
	std::cout << ((Rational("4/3") != "4/3") ? "true" : "false") << std::endl;
	std::cout << Rational("3/5") + "8/16" << std::endl;
	std::cout << Rational("3/5") - "8/16" << std::endl;
	std::cout << Rational("3/5") * "8/16" << std::endl;
	std::cout << Rational("3/5") / "8/16" << std::endl;
	std::cout << (Rational("3/2") ^ 5) << std::endl;
	std::cout << ++Rational("4/5") << std::endl;
	std::cout << Rational("3/5") - "3/5" << std::endl;
	return 0;
}
