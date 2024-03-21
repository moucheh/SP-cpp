#include <iostream>
#include "List.hpp"
using std::cout, std::endl;

int main() {
	List<double> a{1.4, 2.23, 3.41231, 4.34};
	a.push_back(2);
	List<double> b{a};
	List<double> c;
	c = a;
	List<double> d;
	d = List<double> {1.41, 2.32, 3.5};
	b.push_front(4.3);
	b.push_front(4.1);
	b.back() = 44.76;
	b.front() = 125.19;
	b.push_front(4);
	d = b;
	d.push_back(99.1);
	d.push_front(99.2);
	c.push_back(99.3);
	c.push_front(99.4);
	a.pop_front();
	a.pop_back();
	cout << "\na.size() = " << a.size() << endl;
	cout << a;
	cout << "\nb.size() = " << b.size() << endl;
	cout << b;
	cout << endl;
	cout << "c.size() = " << c.size() << endl;
	cout << c;
	cout << "\nd.size() = " << d.size() << endl;
	cout << d;
	cout << endl;
	List<double> la{1.44, 2.3, 3.2, 4.34, 5.12};
	try {
		la.insert(69.32, 99);
	} catch (const std::out_of_range& e) {
		cout << e.what() << endl;
		return 0;
	}
	cout << "la.size() = " << la.size() << endl;
	cout << la;
	cout << endl;
	return 0;
}