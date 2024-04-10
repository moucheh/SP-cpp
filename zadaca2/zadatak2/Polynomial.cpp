#include "Polynomial.hpp"
std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
	if (p.empty())
		return out << '0';
	bool allZero = true;
	for (const auto& a : p) {
		if (a != 0) {
			allZero = false;
			break;
		}
	}
	if (allZero)
		return out << '0';
	if (p[0] != 0.)
		out << p[0];
	if (p.size() >= 2) {
		if (p[1] != 0.) {
			if (p[1] == 1. || p[1] == -1.) {
				out << ((p[1] > 0) ? '+' : '-')
					<< 'x';
			} else {
				out << ((p[1] > 0) ? '+' : '-')
					<< ((p[1] < 0) ? -p[1] : p[1])
					<< 'x';
			}
		}
	}
	for (auto i = 2; i < p.size(); ++i) {
		if (p[i] == 0.) continue;
		if (p[i] == 1. || p[i] == -1.) {
			out << ((p[i] > 0) ? '+' : '-')
				<< 'x' << '^' << i;
		} else {
			out << ((p[i] > 0) ? '+' : '-')
				<< ((p[i] < 0) ? -p[i] : p[i])
				<< 'x' << '^' << i;
		}
	}
	return out;
}

double Polynomial::operator()(double input) const {
	double result{};
	for (auto i = 0; i < size(); ++i) {
		result += (*this)[i] * pow(input, i);
	}
	return result;
}


Polynomial Polynomial::derivative() const {
	Polynomial result;
	result.resize(this->size(), 0);
	for (auto i = size() - 1; i >= 1; --i) {
		result.push_back(i * (*this)[i]);
	}
	result.rotate();
	return result;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
	Polynomial result;
	int size = (this->size() < other.size()
				? other.size()
				: this->size()
			   );
	result.resize(size, 0);
	for (auto i = 0; i < size; ++i) {
		result[i] = (*this)[i] + other[i];
	}
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
	Polynomial result;
	int size = (this->size() < other.size()
				? other.size()
				: this->size()
			   );
	result.resize(size, 0);
	for (auto i = 0; i < size; ++i) {
		result[i] = (*this)[i] - other[i];
	}
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
	Polynomial result;
	result.resize(this->size() + other.size(), 0);
	for (auto i = 0; i < size(); ++i) {
		Polynomial temp;
		for (auto j = 0; j < other.size(); ++j) {
			temp.push_back((*this)[i]*other[j]);
		}
		for (auto k = 0; k < i; ++k) {
			temp.push_front(0);
		}
		result = result + temp;
	}
	return result;
}