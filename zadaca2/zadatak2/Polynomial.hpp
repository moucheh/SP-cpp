#pragma once
#include "MojVektor.hpp"
#include <cmath>
#include <limits>
#include <iomanip>

class Polynomial : public MojVektor<double> {
public:
	Polynomial derivative() const;
	double operator()(double input) const;
	Polynomial operator+(const Polynomial& other) const;
	Polynomial operator-(const Polynomial& other) const;
	Polynomial operator*(const Polynomial& other) const;
};

std::ostream& operator<<(std::ostream&, const Polynomial&);
