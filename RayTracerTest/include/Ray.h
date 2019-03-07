#ifndef RAY_H_
#define RAY_H_

#include "Direction.h"
#include "Operators.h"
#include "Point.h"
#include "Sphere.h"

#include <array>
#include <cmath>
#include <cstddef>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <variant>


struct Ray : private operators::equality_comparable<Ray> {
	Point const origin;
	Direction const direction;

	explicit constexpr Ray(Point const origin = {}, Direction const direction = {}) :
			origin{origin}, direction{direction}{}

	constexpr bool operator==(Ray const & other) const {
		return origin == other.origin && direction == other.direction;
	}
};

inline std::ostream & operator<<(std::ostream & out, Ray const & ray) {
	return out << "Ray{" << ray.origin << "} {" << ray.direction << '}';
}

constexpr Point position(Ray const ray, double const time) {
	return ray.origin + ray.direction * time;
}


struct Intersection : operators::equality_comparable<Intersection> {
	double const time{};
	std::variant<Shapes::Sphere> const object{};

	constexpr Intersection() = default;
	template <typename Shape>
	constexpr Intersection(double const time, Shape const & shape) :
			time{time}, object{shape}{}

	constexpr bool operator==(Intersection const & other) const {
		return time == other.time && object == other.object;
	}
};

struct IntersectionResult : operators::equality_comparable<IntersectionResult> {
	std::array<Intersection, 2> const times{};
	std::size_t const count{};
	
	constexpr IntersectionResult() = default;
	template <typename Shape>
	constexpr IntersectionResult(Shape const & shape, double const first, double const second) :
			times { Intersection{first, shape}, Intersection{second, shape} }, count { 2u } {
	}
	
	constexpr Intersection operator[](std::size_t const index) const {
		if (index >= count) {
			throw std::invalid_argument{"Invalid intersection index"};
		}
		return times[index];
	}

	constexpr bool operator==(IntersectionResult const & other) const {
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
constexpr IntersectionResult intersect(Shape const & shape, Ray const & ray) {
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
		return {shape, t2, t1};
	} else {
		return {shape, t1, t2};
	}
}

template <typename...Inter>
using Intersections = std::array<Intersection, sizeof...(Inter)>;

template <typename...Inter>
constexpr Intersections<Inter...> intersections(Inter const &...inters) {
	return {inters...};
}

template <std::size_t N>
constexpr std::optional<Intersection> hit(std::array<Intersection, N> const & inters) {
	constexpr auto kNoHitIndex = -1;
	auto minIndex = kNoHitIndex;
	for (auto index = 0; index < static_cast<decltype(kNoHitIndex)>(inters.size()); ++index) {
		auto const & current = inters[index];
		if (current.time >= 0.0) {
			if (minIndex == kNoHitIndex || inters[minIndex].time > current.time) {
				minIndex = index;
			}
		}
	}
	if (minIndex == kNoHitIndex) {
		return {};
	} else {
		return inters[minIndex];
	}
}


#endif /* RAY_H_ */
