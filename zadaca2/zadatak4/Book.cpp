#include "Book.hpp"
#include <limits>
#include <cctype>

std::istream& operator>>(std::istream& in, Book& book) {
	std::cout << "Title: ";
	std::getline(in, book.title);
	std::cout << "Author: ";
	std::getline(in, book.author);
	std::cout << "Publisher: ";
	std::getline(in, book.publisher);
	std::cout << "Publication year: ";
	book.publication_year = input_int(in);
	std::cout << "Number of copies: ";
	book.quantity = input_int(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Book& book) {
	out << "Title: " << book.title << '\n'
		<< "Author: " << book.author << '\n'
		<< "Publisher: " << book.publisher << '\n'
		<< "Publication year: " << book.publication_year << '\n'
		<< "Number of copies: " << book.quantity;
	return out;
}

void fix_istream(std::istream& is) {
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int input_int(std::istream& is) {
	int number;
	while (!(is >> number) || number <= 0) {
		std::cout << "\nInvalid input, please enter a positive integer: ";
		fix_istream(is);
	}
	fix_istream(is);
	return number;
}