#ifndef DIRECTION_H_
#define DIRECTION_H_

#include "Coordinate.h"

#include <boost/operators.hpp>
#include <ostream>
#include <stdexcept>

struct Direction : Coordinate<Direction>, boost::addable<Direction>, boost::subtractable<Direction>, boost::multipliable<Direction, double>, boost::dividable<Direction, double> {
	using Coordinate<Direction>::Coordinate;
};

constexpr inline Direction & operator+=(Direction & lhs, Direction const & rhs) noexcept {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

constexpr inline Direction operator-(Direction const & direction) noexcept {
	return {-direction.x, -direction.y, -direction.z};
}

constexpr inline Direction & operator-=(Direction & lhs, Direction const & rhs) noexcept {
	return lhs += -rhs;
}

constexpr inline Direction & operator*=(Direction & lhs, double const factor) noexcept {
	lhs.x *= factor;
	lhs.y *= factor;
	lhs.z *= factor;
	return lhs;
}

constexpr inline Direction & operator/=(Direction & lhs, double const factor) noexcept {
	return lhs *= (1 / factor);
}


constexpr inline double magnitude(Direction const & direction) noexcept {
	return std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
}

constexpr inline Direction normalize(Direction const & direction) {
	auto const mag = magnitude(direction);
	if (isEqual(mag, 0.0)) {
		throw std::invalid_argument{"Cannot normalize direction with magnitude 0.0."};
	}
	return {direction.x / mag, direction.y / mag, direction.z / mag};
}

constexpr inline double dot(Direction const & lhs, Direction const & rhs) noexcept {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

constexpr inline Direction cross(Direction const & lhs, Direction const & rhs) noexcept {
	return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
}

inline std::ostream & operator<<(std::ostream & out, Direction const & direction) {
	return out << "Direction" << static_cast<Coordinate<Direction> const>(direction);
}


#endif /* DIRECTION_H_ */
