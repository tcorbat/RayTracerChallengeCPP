#ifndef POINT_H_
#define POINT_H_

#include "Coordinate.h"
#include "Direction.h"
#include "Operators.h"

#include <ostream>

struct Point : Coordinate<Point>, operators::addable<Point, Direction>, operators::subtractable<Point, Direction> {
	using Coordinate<Point>::Coordinate;
};

inline std::ostream & operator<<(std::ostream & out, Point const & point) {
	return out << "Point" << static_cast<Coordinate<Point> const>(point);
}

constexpr inline Point & operator+=(Point & point, Direction const & direction) noexcept {
	point.x += direction.x;
	point.y += direction.y;
	point.z += direction.z;
	return point;
}

constexpr inline Direction operator-(Point const & end, Point const & start) noexcept {
	return {end.x - start.x, end.y - start.y, end.z - start.z};
}

constexpr inline Point & operator-=(Point & start, Direction const & direction) noexcept {
	return start += -direction;
}


#endif /* POINT_H_ */
