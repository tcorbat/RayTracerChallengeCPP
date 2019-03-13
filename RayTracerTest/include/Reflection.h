#ifndef REFLECTION_H_
#define REFLECTION_H_

#include "Direction.h"

constexpr Direction reflect(Direction const & in, Direction const & normal) {
	return in - normal * 2 * dot(in, normal);
}



#endif /* REFLECTION_H_ */
