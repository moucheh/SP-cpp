#include "DoubleLinkedList.hpp"
#include <iostream>

int main() {
	DoubleLinkedList<int> list;
	list.push_back(1).push_back(2).push_back(3).push_back(4).push_back(5);

	list.remove_if([](auto a) { return a % 2 == 0; });

	for (const auto& element : list) {
		std::cout << element << ' ';
	}

	std::cout << std::endl;

	return 0;
}
