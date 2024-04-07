#pragma once
#include "MojVektor.hpp"
#include <cmath>

class Polynomial : public MojVektor<double> {
	friend std::ostream& operator<<(std::ostream&, const Polynomial&);
public:
	Polynomial derivative();
	double operator()(double input) const;
	Polynomial operator+(const Polynomial& other) const;
	Polynomial operator-(const Polynomial& other) const;
	Polynomial operator*(const Polynomial& other) const;
};

std::ostream& operator<<(std::ostream&, const Polynomial&);
