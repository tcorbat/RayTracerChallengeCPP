#ifndef INCLUDE_COLOR_H_
#define INCLUDE_COLOR_H_

#include "DoubleComparison.h"
#include <boost/operators.hpp>

struct Color: boost::equality_comparable<Color>,
				boost::addable<Color>,
				boost::subtractable<Color>,
				boost::multipliable<Color, double>,
				boost::multipliable<Color> {
	double red{};
	double green{};
	double blue{};

	constexpr Color() = default;
	constexpr Color(double const red, double const green, double const blue) :
			red { red }, green { green }, blue { blue } {
	}

	constexpr bool operator==(Color const & other) const noexcept {
		return isEqual(red, other.red) && isEqual(green, other.green) && isEqual(blue, other.blue);
	}
};

constexpr inline Color operator-(Color const & color) noexcept {
	return {-color.red, -color.green, -color.blue};
}

constexpr inline Color & operator+=(Color & lhs, Color const & rhs) noexcept {
	lhs.red += rhs.red;
	lhs.green += rhs.green;
	lhs.blue += rhs.blue;
	return lhs;
}

constexpr inline Color & operator-=(Color & lhs, Color const & rhs) noexcept {
	return lhs += -rhs;
}

constexpr inline Color & operator*=(Color & lhs, double const factor) noexcept {
	lhs.red *= factor;
	lhs.green *= factor;
	lhs.blue *= factor;
	return lhs;
}

constexpr inline Color & operator*=(Color & lhs, Color const & rhs) noexcept {
	lhs.red *= rhs.red;
	lhs.green *= rhs.green;
	lhs.blue *= rhs.blue;
	return lhs;
}

inline std::ostream & operator<<(std::ostream & out, Color const & color) {
	return out << "Color(" << color.red << ", " << color.green << ", " << color.blue << ")";
}

#endif /* INCLUDE_COLOR_H_ */
