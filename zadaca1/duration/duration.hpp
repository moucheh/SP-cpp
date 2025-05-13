#pragma once
#include <stdexcept>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class Duration {
public:
	Duration() : _t{0}, _s{0}, _m{0}, _h{0} {}
	Duration(int h, int m, int s);
	Duration(int t);
	Duration(std::string str);

	int get_s() const { return _s; }
	int get_m() const { return _m; }
	int get_h() const { return _h; }

	Duration& set_s(int s);
	Duration& set_m(int m);
	Duration& set_h(int h);

	explicit operator bool() const {
		return _s || _m || _h;
	}

	bool operator!() const {
		return !_s && !_m && !_h;
	}

	bool operator==(const Duration& o) const {
		return _h == o._h &&
			   _m == o._m &&
			   _s == o._s;
	}

	bool operator!=(const Duration& o) const {
		return !(_h == o._h &&
				 _m == o._m &&
				 _s == o._s);
	}

	bool operator<(const Duration& o) const {
		return _t < o._t;
	}

	bool operator>(const Duration& o) const {
		return _t > o._t;
	}

	bool operator>=(const Duration& o) const {
		return _t >= o._t;
	}

	bool operator<=(const Duration& o) const {
		return _t <= o._t;
	}

	Duration operator+(const Duration& o) const;
	Duration operator-(const Duration& o) const;
	Duration operator*(int skalar) const;
	Duration operator/(int skalar) const;

	Duration& operator+=(const Duration& o);
	Duration& operator-=(const Duration& o);
	Duration& operator*=(int skalar);
	Duration& operator/=(int skalar);

private:
	/*
		_t - ukupno vrijeme u sekundama
		_s - sekunde
		_m - minute
		_h - sati
	*/
	int _t, _s, _m, _h;
};

std::ostream& operator<<(std::ostream& out, const Duration& dd);
std::istream& operator>>(std::istream& in, Duration& dd);
