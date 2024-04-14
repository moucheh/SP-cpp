#pragma once
#include "MojVektor.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <map>

using mark_t = unsigned short;

struct Student {
	double average_grade() const;
	std::string first_name;
	std::string last_name;
	std::string id;
	MojVektor<mark_t> marks{};
	mark_t year_of_study;
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