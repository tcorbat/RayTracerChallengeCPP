#ifndef SPHERE_H_
#define SPHERE_H_

#include "Matrix.h"
#include "Material.h"
#include "Operators.h"
#include "Point.h"
#include "Transformations.h"


namespace Shapes {

struct Sphere : operators::equality_comparable<Sphere> {

	constexpr explicit Sphere(Point const position = {}, Matrix<4, 4, double> const transform = identity<4>, Material const material = defaultMaterial) :
			position{position}, transform{transform}, material{material}{}

	Point const position;
	Matrix<4, 4, double> const transform;
	Material material;

	constexpr bool operator==(Sphere const & other) const {
		return position == other.position;
	}
};

constexpr Direction normalAt(Sphere const & sphere, Point const point) {
	auto const inverseTransform = inverse(sphere.transform);
	auto const objectPoint =  inverseTransform * point;
	auto const objectNormal = objectPoint - Point{0, 0, 0};
	auto const worldNormal = transpose(inverseTransform) * objectNormal;
	return normalize(worldNormal);
}

}



#endif /* SPHERE_H_ */
