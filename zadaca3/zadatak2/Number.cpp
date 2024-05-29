#include "Number.hpp"
#include <cmath>

Number::Number() = default;

Number::Number(const Number& other) :
	negative_{other.negative_}, digits_{other.digits_} {}

Number::Number(Number&& other) :
	negative_{other.negative_}, digits_{std::move(other.digits_)} {}

Number& Number::operator=(const Number& other) {
	if (this != &other) {
		digits_.clear();
		digits_ = other.digits_;
		negative_ = other.negative_;
	}

	return *this;
}

Number& Number::operator=(Number&& other) {
	if (this != &other) {
		digits_.clear();
		digits_ = std::move(other.digits_);
		negative_ = other.negative_;
	}

	return *this;
}

Number::Number(int n) {
	if (n < 0) {
		n *= -1;
		negative_ = true;
	} else
		negative_ = false;

	while (n != 0) {
		digits_.push_front(n % 10);
		n /= 10;
	}
}

int Number::to_int() const {
	if (digits_.empty())
		return 0;

	int result = 0;

	int multiplicator = 1;
	for (auto it = digits_.rbegin(); it != digits_.rend(); --it) {
		result += *it * multiplicator;
		multiplicator *= 10;
	}


	return (negative_) ? result * -1 : result;
}

std::ostream& operator<<(std::ostream& o, const Number& num) {
	if (num.negative_)
		o << '-';

	for (const auto& digit : num.digits_) {
		o << digit;
	}

	return o;
}

Number Number::operator+(const Number& other) const {
	return Number(to_int() + other.to_int());
}

Number Number::operator-(const Number& other) const {
	return Number(to_int() - other.to_int());
}

Number& Number::operator+=(const Number& other) {
	return *this = Number(to_int() + other.to_int());
}

Number& Number::operator-=(const Number& other) {
	return *this = Number(to_int() - other.to_int());
}

Number& Number::operator=(const int& n) {
	return *this = Number(n);
}

Number& Number::operator=(int&& n) {
	return *this = Number(n);
}

Number Number::operator+(const int& n) const {
	return Number(to_int() + n);
}

Number Number::operator-(const int& n) const {
	return Number(to_int() - n);
}

Number& Number::operator+=(const int& n) {
	return *this = Number(to_int() + n);
}

Number& Number::operator-=(const int& n) {
	return *this = Number(to_int() - n);
}

bool Number::operator==(const Number& other) const {
	return to_int() == other.to_int();
}

bool Number::operator!=(const Number& other) const {
	return to_int() != other.to_int();
}

bool Number::operator>(const Number& other) const {
	return to_int() > other.to_int();
}

bool Number::operator<(const Number& other) const {
	return to_int() < other.to_int();

}

bool Number::operator>=(const Number& other) const {
	return to_int() >= other.to_int();

}

bool Number::operator<=(const Number& other) const {
	return to_int() <= other.to_int();

}

bool Number::operator==(const int& n) const {
	return to_int() == n;
}

bool Number::operator!=(const int& n) const {
	return to_int() != n;
}

bool Number::operator>(const int& n) const {
	return to_int() > n;
}

bool Number::operator<(const int& n) const {
	return to_int() < n;
}

bool Number::operator>=(const int& n) const {
	return to_int() >= n;
}

bool Number::operator<=(const int& n) const {
	return to_int() <= n;
}

Number Number::operator^(short exponent) const {
	return Number(pow(to_int(), exponent));
}

Number::operator bool() const {
	return to_int() != 0;
}

Number& Number::operator++() {
	return *this = to_int() + 1;
}

Number Number::operator++(int) {
	auto temp = *this;
	*this = to_int() + 1;
	return temp;
}

Number& Number::operator--() {
	return *this = to_int() - 1;
}

Number Number::operator--(int) {
	auto temp = *this;
	*this = to_int() - 1;
	return temp;
}
