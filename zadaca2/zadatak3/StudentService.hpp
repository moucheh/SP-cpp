#pragma once
#include "MojVektor.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <map>

struct Student {
	double average_grade() const;
	std::string first_name;
	std::string last_name;
	std::string id;
	MojVektor<int> marks{};
	int year_of_study;
};

class StudentService : public MojVektor<Student> {
public:
	static void menu();
	static void edit_menu();
	Iterator find(const std::string& str) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->id == str) {
				return it;
			}
		}
		return end();
	}

};

std::ostream& operator<<(std::ostream&, const Student&);
std::istream& operator>>(std::istream&, Student&);

void clrscr();
void fix_istream(std::istream&);
int input_int(std::istream&);
double input_double(std::istream&);