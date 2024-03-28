#include "f1_teams.hpp"

void f1_teams::input(std::istream& input) {
	std::string entry;
	f1_team ff;
	while (std::getline(input, entry)) {
		std::istringstream ss(entry);
		std::getline(ss, ff.team_name, ',');
		std::getline(ss, ff.country_of_origin, ',');
		ss >> ff.year_founded;
		ss.ignore();
		ss >> ff.number_of_championships;
		ss.ignore();
		ss >> ff.team_budget_million_usd;
		push_back(ff);
	}
}

f1_teams f1_teams::filter() const {
	f1_teams result;
	for (const auto& outer : *this) {
		if (outer.number_of_championships == 0) continue;
		f1_team new_f1_team;
		for (const auto& inner : *this) {
			if (outer.team_name == inner.team_name &&
					outer.country_of_origin == inner.country_of_origin) {
				new_f1_team.team_name = outer.team_name;
				new_f1_team.country_of_origin = outer.country_of_origin;
				new_f1_team.year_founded = outer.year_founded;
				new_f1_team.number_of_championships += inner.number_of_championships;
				new_f1_team.team_budget_million_usd += inner.team_budget_million_usd;
				if (new_f1_team.year_founded > inner.year_founded)
					new_f1_team.year_founded = inner.year_founded;
			}
		}
		if (!result.find(new_f1_team))
			result.push_back(new_f1_team);
	}
	return result;
}

bool f1_teams::find(const f1_team& ff) const {
	auto result = cend();
	for (auto it = cbegin(); it != cend(); ++it) {
		if (it->team_name == ff.team_name &&
				it->country_of_origin == ff.country_of_origin) {
			result = it;
		}
	}
	if (result == cend())
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& out, const f1_team& ff) {
	out << ff.team_name << ','
		<< ff.country_of_origin << ','
		<< ff.year_founded << ','
		<< ff.number_of_championships << ','
		<< ff.team_budget_million_usd;
	return out;
}

std::ostream& operator<<(std::ostream& out, const f1_teams& fft) {
	for (const auto& f1_team : fft)
		out  << f1_team << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, f1_teams& fft) {
	fft.input(in);
	return in;
}
