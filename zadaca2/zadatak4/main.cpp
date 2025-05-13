#include <iostream>
#include "Book.hpp"
#include "Library.hpp"

int main() {
	const std::string separator_eq(50, '=');
	const std::string separator_us(50, '_');
	const std::string separator_dots(50, '.');

	std::cout << separator_eq << '\n'
			  << "University of Tuzla\n"
			  << "Faculty of Electrical Engineering\n\n"
			  << "Library Application\n"
			  << "Version: April 2024.\n\n"
			  << separator_eq << '\n';
	Library library;
	std::string input;
	library.menu();
	while (true) {
		std::cout << separator_dots << '\n'
				  << "Enter command: ";

		std::getline(std::cin, input);
		std::istringstream iss(input);

		std::string option;
		iss >> option;

		if (option == "CreateUser") {
			User user;
			std::cout << separator_dots << '\n';
			std::cin >> user;

			int id = user.id;
			if (library.add_user(std::move(user))) {
				std::cout << "User created successfully.\n";
			} else {
				std::cout << "User with id {" << id << "} already exists!\n";
			}
		} else if (option == "BookAdd") {
			Book book;
			std::cout << separator_dots << '\n';
			std::cin >> book;

			std::string title = book.title;
			if (library.add_book(std::move(book))) {
				std::cout << "Book added successfully.\n";
			} else {
				std::cout << "Book with title {" << title << "} already exists!\n";
			}
		} else if (option == "BookBorrow") {
			std::cout << separator_dots << '\n'
					  << "User ID: ";
			int id = input_int(std::cin);

			//check if user exists
			MojVektor<User>::Iterator user = library.find_user(
			[&id](const User & user) {
				return user.id == id;
			});
			if (user == library.users_end()) {
				std::cout << "Invalid user.\n";
				continue;
			}

			std::cout << "Book title: ";
			std::string title;
			std::getline(std::cin, title);

			//check if book exists
			MojVektor<Book>::Iterator book = library.find_book(
			[&title](const Book & book) {
				return book.title == title;
			});

			if (book == library.books_end()) {
				std::cout << "Book not found.\n";
				continue;
			}

			//check if user already has the book
			auto it = user->borrowed_books.find(book.data());

			if (it == user->borrowed_books.end()) {
				if (book->quantity != 0) {
					--book->quantity;
					user->borrowed_books.push_back(book.data());
					std::cout << "Book successfully borrowed.\n";
				} else {
					std::cout << "Book not available.\n";
				}
			} else {
				std::cout << "User already has the book.\n";
			}
		} else if (option == "BookReturn") {
			std::cout << separator_dots << '\n'
					  << "User ID: ";
			int id = input_int(std::cin);

			//check if user exists
			MojVektor<User>::Iterator user = library.find_user(
			[&id](const User & user) {
				return user.id == id;
			});
			if (user == library.users_end()) {
				std::cout << "Invalid user.\n";
				continue;
			}

			std::cout << "Book title: ";
			std::string title;
			std::getline(std::cin, title);

			//check if book exists
			MojVektor<Book>::Iterator book = library.find_book(
			[&title](const Book & book) {
				return book.title == title;
			});

			if (book == library.books_end()) {
				std::cout << "Book not found.\n";
				continue;
			}

			auto it = user->borrowed_books.find(book.data());
			if (it == user->borrowed_books.end()) {
				std::cout << "User didn't borrow the book.\n";
				continue;
			}

			user->borrowed_books.erase(it);
			++book->quantity;
			std::cout << "Book successfully Returned.\n";
		} else if (option == "BookSearchByTitle") {
			std::cout << separator_dots << '\n'
					  << "Title: ";
			std::string title;
			std::getline(std::cin, title);
			MojVektor<Book>::Iterator book = library.find_book(
			[&title](const Book & book) {
				return book.title == title;
			});

			if (book == library.books_end()) {
				std::cout << "Book not found.\n";
			} else {
				std::cout << "Found book:\n"
						  << separator_us << '\n'
						  << *book << std::endl;
			}
		} else if (option == "BookSearchByAuthor") {
			std::cout << "Author: ";
			std::string author;
			std::getline(std::cin, author);

			std::cout << "Found books:\n"
					  << separator_us << '\n';
			library.print_books_by_author(author);
		} else if (option == "BookSearchByPublisher") {
			std::cout << "Publisher: ";
			std::string publisher;
			std::getline(std::cin, publisher);

			std::cout << "Found books:\n"
					  << separator_us << '\n';
			library.print_books_by_publisher(publisher);
		} else if (option == "BookSearchByPublicationYear") {
			std::cout << "Publication year: ";
			int publication_year = input_int(std::cin);

			std::cout << "Found books:\n"
					  << separator_us << '\n';
			library.print_books_by_publication_year(publication_year);
		} else if (option == "Help") {
			library.menu();
		} else if (option == "Exit") {
			break;
		} else {
			std::cout << "Invalid command. Please try again.\n";
		}
	}
	return 0;
}