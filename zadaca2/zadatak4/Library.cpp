#include "Library.hpp"

void Library::menu() {
	static const std::string separator_eq(50, '=');
	static const std::string separator_us(50, '_');
	static const std::string separator_dots(50, '.');
	std::cout << '\n' << separator_us << '\n'
			  << "List of commands:\n"
			  << separator_eq << '\n'
			  << "CreateUser\n"
			  << "BookAdd\n"
			  << "BookBorrow\n"
			  << "BookReturn\n"
			  << "BookSearchByTitle\n"
			  << "BookSearchByAuthor\n"
			  << "BookSearchByPublisher\n"
			  << "BookSearchByPublicationYear\n"
			  << "Help\n"
			  << "Exit\n"
			  << separator_us << '\n';
}

bool Library::add_user(User&& user) {
	auto it = users.find([&user](auto a) {
		return a.id == user.id;
	});

	if (it == users.end()) {
		users.push_back(user);
		return true;
	}
	return false;
}

bool Library::add_book(Book&& book) {
	auto it = books.find(
	[&book](auto a) {
		return a.title == book.title;
	});

	if (it == books.end()) {
		books.push_back(book);
		return true;
	}
	return false;
}

MojVektor<User>::Iterator Library::find_user(
	std::function<bool(const User&)> lambda) const {
	return users.find(lambda);
}

MojVektor<Book>::Iterator Library::find_book(
	std::function<bool(const Book&)> lambda) const {
	return books.find(lambda);
}

void Library::print_books_by_author(const std::string& author) {
	static const std::string separator_us(50, '_');
	bool found = false;
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->author == author) {
			found = true;
			std::cout << *it << '\n'
					  << separator_us << '\n';
		}
	}
	if (!found) {
		std::cout << "No books by " << author << " found.\n";
	}
}

void Library::print_books_by_publisher(const std::string& publisher) {
	static const std::string separator_us(50, '_');
	bool found = false;
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->publisher == publisher) {
			found = true;
			std::cout << *it << '\n'
					  << separator_us << '\n';
		}
	}
	if (!found) {
		std::cout << "No books from " << publisher << " found.\n";
	}
}

void Library::print_books_by_publication_year(int publication_year) {
	static const std::string separator_us(50, '_');
	bool found = false;
	for (auto it = books.begin(); it != books.end(); ++it) {
		if (it->publication_year == publication_year) {
			found = true;
			std::cout << *it << '\n'
					  << separator_us << '\n';
		}
	}
	if (!found) {
		std::cout << "No books published in " << publication_year << " found.\n";
	}
}
