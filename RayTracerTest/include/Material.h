#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"
#include "DoubleComparison.h"
#include "Operators.h"

struct Material : operators::equality_comparable<Material> {
	Color color;
	double ambient;
	double diffuse;
	double specular;
	double shininess;

	constexpr bool operator==(Material const & other) const {
		return color == other.color &&
				isEqual(ambient, other.ambient) &&
				isEqual(diffuse, other.diffuse) &&
				isEqual(specular, other.specular) &&
				isEqual(shininess, other.shininess);
	}
};

constexpr Material defaultMaterial{{}, Colors::white, 0.1, 0.9, 0.9, 200.0};


#endif /* MATERIAL_H_ */
