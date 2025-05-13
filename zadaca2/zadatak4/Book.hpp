#pragma once
#include <string>
#include <iostream>
#include "MojVektor.hpp"

struct Book {
	std::string title;
	std::string author;
	std::string publisher;
	int publication_year;
	int quantity;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);

void fix_istream(std::istream&);
int input_int(std::istream&);
