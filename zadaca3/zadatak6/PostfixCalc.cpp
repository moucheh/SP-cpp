#include "PostfixCalc.hpp"

std::ostream& operator<<(std::ostream& out, const PostfixCalc& pc) {
	int result;

	if (pc.op == '+') {
		result = 0;

		for (const auto& element : pc)
			result += element;
	} else if (pc.op == '-') {
		result = pc.front();

		for (const auto& element : pc) {
			if (&element != &pc.front())
				result -= element;
		}
	} else if (pc.op == '*') {
		result = 1;

		for (const auto& element : pc)
			result *= element;
	} else if (pc.op == '/') {
		result = pc.front();

		for (const auto& element : pc) {
			if (&element != &pc.front()) {
				if (element == 0)
					throw std::runtime_error{
					"Division by zero is undefined!"
				};
				result /= element;
			}
		}
	}

	return out << result;
}

PostfixCalc::PostfixCalc(std::string&& input) {
	if (input.empty()) {
		std::cout << "Program exited normally." << std::endl;
		exit(0);
	}

	const char* ptr = input.c_str() + input.size() - 1;

	while (ptr != input.c_str()) {
		if (isdigit(*ptr))
			throw std::runtime_error{"Invalid input."};
		if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
			op = *ptr;
			break;
		}
		--ptr;
	}

	std::stringstream iss(input);
	int n;

	while (iss >> n) {
		push_back(n);
	}
}

