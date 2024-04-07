#include "Polynomial.hpp"

#include <iostream>

int main() {
	Polynomial p1, p2;
	std::cout << "Unesite prvi polinom (prekid sa nevalidnim unosom): ";
	double x;
	while (std::cin >> x)
		p1.push_back(x);
	std::cin.clear();
	std::cin.ignore(
		std::numeric_limits<std::streamsize>::max(),
		'\n'
	);
	std::cout << "Unesite drugi polinom (prekid sa nevalidnim unosom): ";
	while (std::cin >> x)
		p2.push_back(x);
	std::cout << "P1 (x) = " << p1 << std::endl;
	std::cout << "P1'(x) = " << p1.derivative() << std::endl;
	std::cout << "P2 (x) = " << p2 << std::endl;
	std::cout << "P2'(x) = " << p2.derivative() << std::endl;
	std::cout << "P1 (x) + P2(x) = " << (p1 + p2) << std::endl;
	std::cout << "P1 (x) - P2(x) = " << (p1 - p2) << std::endl;
	std::cout << "P1 (x) * P2(x) = " << (p1 * p2) << std::endl << std::endl;

	std::cout << "\nVrijednosti polinoma P1(x) u tackama [-10, 10]:" << std::endl;
	for (auto x = -10; x <= 10; ++x) {
		std::cout << "P(" << std::setw(2) << x << ") = " << p1(x) << '\n';
	}
	auto p3 = p1.derivative();
	std::cout << "\nVrijednosti izvod polinoma P1(x) u tackama [-10, 10]:" << std::endl;
	for (auto x = -10; x <= 10; ++x) {
		std::cout << "P'(" << std::setw(2) << x << ") = " << p3(x) << '\n';
	}
	return 0;
}