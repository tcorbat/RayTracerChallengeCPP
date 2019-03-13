#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "Point.h"

struct Light {
	Point position;
	Color intensity;
};

constexpr Light pointLight(Point const & point, Color const & intensity) {
	return {point, intensity};
}

#endif /* LIGHT_H_ */
