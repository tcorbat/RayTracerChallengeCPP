#ifndef SPHERE_H_
#define SPHERE_H_

#include "Point.h"
#include "Operators.h"

namespace Shapes {

struct Sphere : operators::equality_comparable<Sphere> {

	Point const position;

	constexpr bool operator==(Sphere const & other) const {
		return position == other.position;
	}
};

}



#endif /* SPHERE_H_ */
