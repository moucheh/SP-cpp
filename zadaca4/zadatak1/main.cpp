#include <iostream>
#include "Heap.hpp"
#include <vector>

int main() {
	srand(time(NULL));
	Heap<int> h(20);
	std::vector<int> v;
	v.reserve(20);

	for (auto i = 0; i < 20; ++i) {
		auto t = rand() % 99 + 1;
		v.push_back(t);
		h.insert(t);
	}

	std::cout << "heap: " << h << std::endl;

	Heap<int> copyh(20);
	copyh = h;

	Heap<int> moveh(std::move(h));

	std::cout << "copy heap: " << copyh << std::endl;
	std::cout << "move heap: " << moveh << std::endl;

	std::cout << "max: " << moveh.max() << std::endl;
	std::cout << "capacity: " << moveh.capacity() << std::endl;
	std::cout << "size: " << moveh.size() << std::endl;

	auto i = 19;
	while (!moveh.empty())
		v[i--] = moveh.removeMax();

	std::cout << "vector after heap sort: ";

	for (const auto& el : v)
		std::cout << el << ' ';

	std::cout << std::endl << "size: " << moveh.size() << std::endl;
	return 0;
}