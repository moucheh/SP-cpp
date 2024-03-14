#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <algorithm>

class f1_team {
public:
	friend std::ostream& operator<<(std::ostream& out, const f1_team& ff);
	friend class f1_teams;

	bool operator<(const f1_team& other) const {
		return number_of_championships > other.number_of_championships;
	}
private:
	std::string team_name;
	std::string country_of_origin;
	int year_founded{};
	int number_of_championships{};
	int team_budget_million_usd{};
};

class f1_teams : public std::list<f1_team> {
public:
	f1_teams filter() const;
	void input(std::istream& input);
	bool find(const f1_team& ff) const;
};

std::ostream& operator<<(std::ostream& out, const f1_team& ff);
std::ostream& operator<<(std::ostream& out, const f1_teams& fft);
std::istream& operator>>(std::istream& in, f1_teams& fft);