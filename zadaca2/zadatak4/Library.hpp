#pragma once

#include "Book.hpp"
#include "User.hpp"
#include <sstream>
#include <functional>

class Library {
public:
	static void menu();
	bool add_user(User&&);
	bool add_book(Book&&);

	void print_books_by_author(const std::string&);
	void print_books_by_publisher(const std::string&);
	void print_books_by_publication_year(int);

	MojVektor<User>::Iterator find_user(
		std::function<bool(const User&)>) const;

	MojVektor<User>::Iterator users_end() const {
		return users.end();
	}

	MojVektor<Book>::Iterator find_book(
		std::function<bool(const Book&)>) const;

	MojVektor<Book>::Iterator books_end() const {
		return books.end();
	}
private:
	MojVektor<User> users;
	MojVektor<Book> books;
};