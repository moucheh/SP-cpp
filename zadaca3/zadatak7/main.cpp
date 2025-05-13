#include <iostream>
#include <string>
#include <sstream>
#include "../zadatak5/Stack.hpp"

bool checkBraces(std::string&& input) {
	if (input.empty())
		throw std::runtime_error{"Input is empty."};

	std::istringstream iss(input);

	Stack<char> braces;

	char ch;

	while (iss >> ch) {
		if (ch == '<' && ((braces.top() == '{' || braces.top() == '[' || braces.top() == '(' || braces.top() == '<') || braces.empty()))
			braces.push(ch);

		if (ch == '(' && ((braces.top() == '{' || braces.top() == '[' || braces.top() == '(') || braces.empty()))
			braces.push(ch);

		if (ch == '[' && ((braces.top() == '{' || braces.top() == '[') || braces.empty()))
			braces.push(ch);

		if (ch == '{' && (braces.top() == '{' || braces.empty()))
			braces.push(ch);

		if (ch == '[' && (braces.top() == '<' || braces.top() == '('))
			return false;

		if (ch == '{' && (braces.top() == '<' || braces.top() == '(' || braces.top() == '['))
			return false;

		if ((ch == '(' || ch == '[' || ch == '{') && braces.top() == '<' )
			return false;

		if ((ch == '[' || ch == '{') && braces.top() == '(' )
			return false;

		if (ch == '{' && braces.top() == '[')
			return false;

		if (ch == '>' && braces.top() != '<')
			return false;

		if (ch == ')' && braces.top() != '(')
			return false;

		if (ch == ']' && braces.top() != '[')
			return false;

		if (ch == '}' && braces.top() != '{')
			return false;

		if (ch == '(' && braces.top() == '<')
			return false;

		if (ch == '>' && braces.top() == '<' && !braces.empty())
			braces.pop();

		if (ch == ')' && braces.top() == '(' && !braces.empty())
			braces.pop();

		if (ch == ']' && braces.top() == '[' && !braces.empty())
			braces.pop();

		if (ch == '}' && braces.top() == '{' && !braces.empty())
			braces.pop();
	}

	if (!braces.empty())
		return false;

	return true;
}

int main() {
	std::string input;

	while (std::getline(std::cin, input)) {
		try {
			if (checkBraces(std::move(input)))
				std::cout << "All of the braces are closed properly!" << std::endl;
			else
				std::cout << "Syntax error, braces aren't closed properly!" << std::endl;
		} catch (const std::runtime_error& err) {
			std::cout << err.what() << std::endl;
		}
	}

	return 0;
}