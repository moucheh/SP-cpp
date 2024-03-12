#include "duration.hpp"

Duration& Duration::set_s(int s) {
	if (s < 0)
		throw std::out_of_range{
		"Broj sekundi ne smije biti manji od 0!"
	};
	if (s >= 60)
		throw std::out_of_range{
		"Broj sekundi ne smije biti veci od 60!"
	};
	_s = s;
	return *this;
}

Duration& Duration::set_m(int m) {
	if (m < 0)
		throw std::out_of_range{
		"Broj minuta ne smije biti manji od 0!"
	};
	if (m >= 60)
		throw std::out_of_range{
		"Broj minuta ne smije biti veci od 60!"
	};
	_m = m;
	return *this;
}

Duration& Duration::set_h(int h) {
	if (h < 0)
		throw std::out_of_range{
		"Broj sati ne smije biti manji od 0!"
	};
	_h = h;
	return *this;
}

Duration::Duration(int h, int m, int s) : _t(h * 3600 + m * 60 + s) {
	set_s(s);
	set_m(m);
	set_h(h);
}

Duration::Duration(int t) : _t{t} {
	_h = t / 3600;
	_m = (t - _h * 3600) / 60;
	_s = t - _h * 3600 - _m * 60;
}

Duration::Duration(std::string str) {
	set_h(std::stoi(str.substr(0, str.find(':'))));
	str = str.substr(str.find(':') + 1, str.length());
	set_m(std::stoi(str.substr(0, str.find(':'))));
	str = str.substr(str.find(':') + 1, str.length());
	set_s(std::stoi(str));
	_t = 3600 * _h + 60 * _m + _s;
}

Duration Duration::operator+(const Duration& o) const {
	return Duration(_t + o._t);
}

Duration Duration::operator-(const Duration& o) const {
	if (_t < o._t)
		throw std::out_of_range{
		"Vrijeme ne moze biti negativno!\nPrvi operand je veci od drugog."
	};
	return Duration(_t - o._t);
}

Duration Duration::operator*(int skalar) const {
	return Duration(_t * skalar);
}

Duration Duration::operator/(int skalar) const {
	if (skalar == 0)
		throw std::out_of_range{
		"Dijeljenje s nulom nema smisla!"
	};
	return Duration(_t / skalar);
}


Duration& Duration::operator+=(const Duration& o) {
	*this = Duration(_t + o._t);
	return *this;
}

Duration& Duration::operator-=(const Duration& o) {
	if (_t < o._t)
		throw std::out_of_range{
		"Vrijeme ne moze biti negativno!\nPrvi operand je veci od drugog."
	};
	*this = Duration(_t - o._t);
	return *this;
}

Duration& Duration::operator*=(int skalar) {
	*this = Duration(_t * skalar);
	return *this;
}

Duration& Duration::operator/=(int skalar) {
	if (skalar == 0)
		throw std::out_of_range{
		"Dijeljenje s nulom nema smisla!"
	};
	*this = Duration(_t / skalar);
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Duration& dd) {
	out << std::setfill('0') << std::setw(2) << dd.get_h() << ':'
		<< std::setfill('0') << std::setw(2) << dd.get_m() << ':'
		<< std::setfill('0') << std::setw(2) << dd.get_s();
	return out;
}

std::istream& operator>>(std::istream& in, Duration& dd) {
	std::string input;
	in >> input;
	dd = Duration(input);
	return in;
}