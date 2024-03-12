#include "Rational.hpp"

int gcd(int numerator, int denominator) {
	if (numerator < 0) numerator *= -1;
	if (denominator < 0) denominator *= -1;
	const int num = numerator;
	const int denom = denominator;
	int shift;
	for (shift = 0; ((numerator | denominator) & 1) == 0; ++shift) {
		numerator >>= 1;
		denominator >>= 1;
	}
	while ((numerator & 1) == 0) {
		numerator >>= 1;
	}
	while (denominator != 0) {
		while ((denominator & 1) == 0) {
			denominator >>= 1;
		}
		if (numerator > denominator) {
			std::swap(numerator, denominator);
		}
		denominator -= numerator;
	}
	return numerator << shift;
}

Rational::Rational(int numerator, int denominator) {
	if (denominator == 0)
		throw std::invalid_argument{
		"The denominator mustn't be zero!"
	};
	numerator_ = numerator;
	denominator_ = denominator;
}

Rational::Rational(const char* rational) {
	std::string str = rational;
	*this = Rational(str);
}

Rational::Rational(const std::string& str) {
	int i;
	if ( (i = str.find('/')) == std::string::npos)
		throw std::invalid_argument{
		"Invalid format, input has to contain (/)!"
	};
	if (std::stoi(str.substr(i + 1, str.length())) == 0)
		throw std::invalid_argument{
		"Denominator mustn't be zero!"
	};
	for (auto j = 0; j < str.length(); j++) {
		if (j == i) continue;
		if (!isdigit(str[j]))
			throw std::invalid_argument{
			"Invalid argument, only numbers allowed!"
		};
	}
	numerator_ = std::stoi(str.substr(0, str.find('/')));
	denominator_ = std::stoi(str.substr(str.find('/') + 1, str.length()));
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
	if (rational.numerator() == 0) {
		os << 0;
		return os;
	}
	int _gcd = gcd(rational.numerator(), rational.denominator());
	os << rational.numerator() / _gcd;
	if (rational.denominator() / _gcd != 1)
		os << '/' << rational.denominator() / _gcd;
	return os;
}

Rational Rational::operator+(const Rational& rational) const {
	if (numerator() == 0) return rational;
	if (rational.numerator() == 0) return *this;
	Rational result(
		numerator() * rational.denominator() + rational.numerator() * denominator(),
		denominator() * rational.denominator()
	);
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator+(int numerator) const {
	return *this + Rational(numerator, 1);
}

Rational Rational::operator-(const Rational& rational) const {
	if (numerator() == 0) return rational;
	if (rational.numerator() == 0) return *this;
	if (*this == rational) return Rational(0, 1);
	Rational result(
		numerator() * rational.denominator() - rational.numerator() * denominator(),
		denominator() * rational.denominator()
	);
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator-(int numerator) const {
	return *this - Rational(numerator, 1);
}

Rational& Rational::operator++() {
	*this = *this + 1;
	return *this;
}

Rational Rational::operator++(int) {
	auto temp = *this;
	*this = *this + 1;
	return temp;
}

Rational& Rational::operator--() {
	*this = *this - 1;
	return *this;
}


Rational Rational::operator--(int) {
	auto temp = *this;
	*this = *this - 1;
	return temp;
}

Rational Rational::operator*(const Rational& rational) const {
	Rational result(
		numerator() * rational.numerator(),
		denominator() * rational.denominator()
	);
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator*(int numerator) const {
	Rational result(this->numerator() * numerator, denominator());
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator/(const Rational& rational) const {
	Rational result(
		numerator() * rational.denominator(),
		denominator() * rational.numerator()
	);
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator/(int numerator) const {
	Rational result(this->numerator(), denominator() * numerator);
	int _gcd = gcd(result.numerator(), result.denominator());
	return Rational(
			   result.numerator() / _gcd,
			   result.denominator() / _gcd
		   );
}

Rational Rational::operator^(int exponent) const {
	return Rational(
			   pow(numerator(), exponent),
			   pow(denominator(), exponent)
		   );
}

bool Rational::operator==(const Rational& rational) const {
	int _gcd1 = gcd(numerator(), denominator());
	int _gcd2 = gcd(rational.numerator(), rational.denominator());
	return numerator() / _gcd1 == rational.numerator() / _gcd2 &&
		   denominator() / _gcd1 == rational.denominator() / _gcd2;
}

bool Rational::operator==(const char* rational) const {
	Rational temp(rational);
	return *this == temp;
}

bool Rational::operator!=(const Rational& rational) const {
	int _gcd1 = gcd(numerator(), denominator());
	int _gcd2 = gcd(rational.numerator(), rational.denominator());
	return !(numerator() / _gcd1 == rational.numerator() / _gcd2) ||
		   !(denominator() / _gcd1 == rational.denominator() / _gcd2);
}

bool Rational::operator!=(const char* rational) const {
	Rational temp(rational);
	return *this != temp;
}
