#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

struct Material {
	Color color;
	double ambient;
	double diffuse;
	double specular;
	double shininess;
};

constexpr Material defaultMaterial{Colors::white, 0.1, 0.9, 0.9, 200.0};


#endif /* MATERIAL_H_ */
