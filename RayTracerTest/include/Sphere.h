#ifndef SPHERE_H_
#define SPHERE_H_

#include "Matrix.h"
#include "Operators.h"
#include "Point.h"

namespace Shapes {

struct Sphere : operators::equality_comparable<Sphere> {

	constexpr explicit Sphere(Point const position = {}, Matrix<4, 4, double> const transform = identity<4>) :
			position{position}, transform{transform}{}

	Point const position;
	Matrix<4, 4, double> const transform;

	constexpr bool operator==(Sphere const & other) const {
		return position == other.position;
	}
};

}



#endif /* SPHERE_H_ */
