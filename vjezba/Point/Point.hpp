
#pragma once
#include <iostream>

class Point {
public:
	// Default constructor
	Point() : x_{0.}, y_{0.} {};
	// Constructor with initial values for x and y
	Point(double x, double y) : x_{x}, y_{y} {}
	// Copy constructor
	Point(const Point& point) : x_{point.x_}, y_{point.y_} {}
	// Move constructor
	Point(Point&& point) : x_{std::move(point.x_)}, y_{std::move(point.y_)} {
		point.x_ = 0.;
		point.y_ = 0.;
	}
	// Assignment operator
	Point& operator=(const Point& point) {
		x_ = point.x_;
		y_ = point.y_;
		return *this;
	}
	// Move assignment operator
	Point& operator=(Point&& point) {
		x_ = std::move(point.x_);
		y_ = std::move(point.y_);
		point.x_ = 0.;
		point.y_ = 0.;
		return *this;
	}
	// Addition operator
	Point operator+(const Point& point) const {
		return Point(x_ + point.x_, y_ + point.y_);
	}
	// Subtraction operator
	Point operator-(const Point& point) const {
		return Point(x_ - point.x_, y_ - point.y_);
	}
	// Multiplication operator (scalar multiplication)
	Point operator*(double scalar) const {
		return Point(x_ * scalar, y_ * scalar);
	}
	// Division operator (scalar division)
	Point operator/(double scalar) const {
		if (scalar == 0)
			throw std::invalid_argument{
			"Dijeljenje s nulom nije definisana operacija."
		};
		return Point(x_ / scalar, y_ / scalar);
	}
	// Addition assignment operator
	Point& operator+=(const Point& point) {
		*this = Point(x_ + point.x_, y_ + point.y_);
		return *this;
	}
	// Subtraction assignment operator
	Point& operator-=(const Point& point) {
		*this = Point(x_ - point.x_, y_ - point.y_);
		return *this;
	}
	// Multiplication assignment operator (scalar multiplication)
	Point& operator*=(double scalar) {
		*this = Point(x_ * scalar, y_ * scalar);
		return *this;
	}
	// Division assignment operator (scalar division)
	Point& operator/=(double scalar) {
		if (scalar == 0)
			throw std::invalid_argument{
			"Dijeljenje s nulom nije definisana operacija."
		};
		*this = Point(x_ / scalar, y_ / scalar);
		return *this;
	}
	// Equality operator
	bool operator==(const Point& point) const {
		return x_ == point.x_ && y_ == point.y_;
	}
	// Inequality operator
	bool operator!=(const Point& point) const {
		return !(x_ == point.x_ && y_ == point.y_);
	}
	// Get x-coordinate
	double x() const { return x_; }
	// Get y-coordinate
	double y() const { return y_; }
	// Set x-coordinate
	void setX(double x) {
		x_ = x;
	}
	// Set y-coordinate
	void setY(double y) {
		y_ = y;
	}
	// Get the distance between this point and anpoint point
	// sqrt((point.x_ - x_)^2 + (point.y_ - y_)^2)
	double distance(const Point& point) const;

private:
	double x_;
	double y_;
};

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Point& point);
std::istream& operator>>(std::istream& is, Point& point);
