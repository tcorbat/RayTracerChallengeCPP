#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "DoubleComparison.h"
#include <boost/operators.hpp>
#include <ostream>

template <typename SubType>
struct Coordinate : private boost::equality_comparable<SubType> {
	double x{};
	double y{};
	double z{};

	constexpr Coordinate() = default;

	constexpr Coordinate(double const x, double const y, double const z) noexcept :
			x { x }, y { y }, z { z } {
	}

	constexpr bool operator==(SubType const & rhs) const noexcept {
		return isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z);
	}

};

template <typename Sub>
std::ostream & operator<<(std::ostream & out, Coordinate<Sub> const & coordinate) {
	return out << "(" << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << ")";
}


#endif /* COORDINATE_H_ */
