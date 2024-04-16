#pragma once
#include <string>
#include <iostream>
#include "Book.hpp"


struct User {
	std::string first_name;
	std::string last_name;
	int id;
	MojVektor<Book*> borrowed_books;
};

std::istream& operator>>(std::istream&, User&);
