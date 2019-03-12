#ifndef RAY_H_
#define RAY_H_

#include "Direction.h"
#include "Matrix.h"
#include "Operators.h"
#include "Point.h"

#include <ostream>
#include <variant>


struct Ray : private operators::equality_comparable<Ray> {
	Point const origin;
	Direction const direction;

	explicit constexpr Ray(Point const origin = {}, Direction const direction = {}) :
			origin{origin}, direction{direction}{}

	constexpr bool operator==(Ray const & other) const {
		return origin == other.origin && direction == other.direction;
	}

	constexpr Point position(double const time) const {
		return origin + direction * time;
	}

	template<typename ValueType = double>
	constexpr auto transform(Matrix<4, 4, ValueType> const & matrix) const {
		return Ray{matrix * origin, matrix * direction};
	}
};

inline std::ostream & operator<<(std::ostream & out, Ray const & ray) {
	return out << "Ray{" << ray.origin << "} {" << ray.direction << '}';
}







#endif /* RAY_H_ */
