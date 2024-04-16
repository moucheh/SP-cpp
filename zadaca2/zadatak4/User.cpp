#include "User.hpp"

std::istream& operator>>(std::istream& in, User& user) {
	std::cout << "First name: ";
	in >> user.first_name;
	std::cout << "Last name: ";
	in >> user.last_name;
	std::cout << "User id: ";
	user.id = input_int(std::cin);
	return in;
}