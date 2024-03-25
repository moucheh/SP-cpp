#include "Point.hpp"
#include <cmath>

double Point::distance(const Point& point) const {
	return sqrt(
			   (x_ - point.x_) * (x_ - point.x_) +
			   (y_ - point.y_) * (y_ - point.y_)
		   );
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os << "Point(x=" << point.x() << ", y=" << point.y() << ")\n";
	return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
	double x, y;
	is >> x >> y;
	point.setX(x);
	point.setY(y);
	return is;
}
