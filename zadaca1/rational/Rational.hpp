#pragma once
#include <iostream>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>


/*! \class Rational
 *
 *  Klasa Rational simulira rad sa racionalnim brojevima.
 *  Stanje ove klase cine dva cijela broja: brojnik i nazivnik.
 *  Sve operacije moraju bit optimialne, sto znaci da ako je moguce i brojnik i
 * nazivnik treba skratiti na najmanju mogucu vrijednost, na primjer: 10/12 je
 * neophodno prikazati kao 5/6 nakon kracenja sa 2.
 * Ne dozvoliti da nazivnik bude 0!
 */

class Rational {
public:
	Rational() : numerator_{0}, denominator_{1} {};
	Rational(int numerator, int denominator);

	Rational(const char* rational);
	Rational(const std::string&);

	// copy constructor
	Rational(const Rational& rational)
		: numerator_{rational.numerator_},
		  denominator_{rational.denominator_} {};
	// Move constructor
	Rational(Rational&& rational)
		: numerator_{rational.numerator_},
		  denominator_{rational.denominator_} {
		rational.numerator_ = 0;
		rational.denominator_ = 1;
	};
	// Copy op=
	Rational& operator=(const Rational& rational) {
		numerator_ = rational.numerator_;
		denominator_ = rational.denominator_;
		return *this;
	}

	Rational& operator=(Rational&& rational) {
		numerator_ = rational.numerator_;
		denominator_ = rational.denominator_;
		rational.numerator_ = 0;
		rational.denominator_ = 1;
		return *this;
	}

	Rational operator+(const Rational& rational) const;
	Rational operator+(int numerator) const;
	Rational operator-(const Rational& rational) const;
	Rational operator-(int numerator) const;

	Rational operator*(const Rational& rational) const;
	Rational operator*(int numerator) const;

	Rational operator/(const Rational& rational) const;
	Rational operator/(int numerator) const;

	Rational operator^(int) const;
	Rational& operator++();
	Rational operator++(int);
	Rational& operator--();
	Rational operator--(int);

	bool operator==(const Rational& rational) const;
	bool operator==(const char* rational) const;
	bool operator!=(const Rational& rational) const;
	bool operator!=(const char* rational) const;

	const int numerator() const { return numerator_; }
	const int denominator() const { return denominator_; }

	~Rational() {}

private:
	int numerator_;
	int denominator_;
};

std::ostream& operator<<(std::ostream& os, const Rational& rational);
int gcd(const int numerator, const int denominator);
