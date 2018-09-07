#ifndef RAY_H_
#define RAY_H_

#include "Direction.h"
#include "Operators.h"
#include "Point.h"
#include "Sphere.h"

#include <array>
#include <cmath>
#include <cstddef>
#include <stdexcept>



struct Ray {
	Point const origin;
	Direction const direction;
};


constexpr Point position(Ray const ray, double const time) {
	return ray.origin + ray.direction * time;
}


struct Intersection : operators::equality_comparable<Intersection> {
	std::array<double, 2> const times{};
	std::size_t const count{};
	
	constexpr Intersection() = default;
	constexpr Intersection(double const first, double const second) :
			times { first, second }, count { 2 } {
	}
	
	constexpr double operator[](std::size_t const index) const {
		if (index >= count) {
			throw std::invalid_argument{"Invalid intersection index"};
		}
		return times[index];
	}

	constexpr bool operator==(Intersection const & other) const {
		return count == other.count && times == other.times;
	}
};

constexpr double discriminant(Shapes::Sphere const & sphere, Ray const & ray) {
	auto const sphereToRay = ray.origin - sphere.position;
	auto const a = dot(ray.direction, ray.direction);
	auto const b = 2 * dot(ray.direction, sphereToRay);
	auto const c = dot(sphereToRay, sphereToRay) - 1;
	return b * b - 4 * a * c;
}

template <typename Shape>
constexpr Intersection intersect(Shape const & shape, Ray const & ray) {
	auto const shapeToRay = ray.origin - shape.position;
	auto const a = dot(ray.direction, ray.direction);
	auto const b = 2 * dot(ray.direction, shapeToRay);
	auto const c = dot(shapeToRay, shapeToRay) - 1;
	auto const discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0) {
		return {};
	}
	auto  t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	auto const t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	if (t1 > t2) {
		return {t2, t1};
	} else {
		return {t1, t2};
	}
}



#endif /* RAY_H_ */
