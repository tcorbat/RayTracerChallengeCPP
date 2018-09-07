#include "RayTestSuite.h"
#include "Ray.h"
#include "Direction.h"
#include "Point.h"
#include "Sphere.h"
#include "cute.h"

#include <tuple>


using Shapes::Sphere;

void testPropertiesOfRay() {
	constexpr Point origin{1.0, 2.0, 3.0};
	constexpr Direction direction{4.0, 5.0, 6.0};
	constexpr Ray ray{origin, direction};
	ASSERT_EQUAL(std::tie(origin, direction), std::tie(ray.origin, ray.direction));
}

struct {
	double const time;
	Point const expected;
	cute::test_failure const failure;
} const rayPositions[] {
		{  0.0, {2.0, 3.0, 4.0}, DDT()},
		{  1.0, {3.0, 3.0, 4.0}, DDT()},
		{ -2.0, {0.0, 3.0, 4.0}, DDT()},
		{  2.5, {4.5, 3.0, 4.0}, DDT()}
};

void testRayPosition() {
	constexpr Ray ray { { 2.0, 3.0, 4.0 }, { 1.0, 0.0, 0.0 } };
	for (auto const & testEntry : rayPositions) {
		ASSERT_EQUAL_DDT(testEntry.expected, position(ray, testEntry.time), testEntry.failure);
	}
}

void testRayIntersectionWithSphere() {
	constexpr Ray ray{{0.0, 0.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr Intersection expected{4.0, 6.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayTouchesSphere() {
	constexpr Ray ray{{0.0, 1.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr Intersection expected{5.0, 5.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayMissesSphere() {
	constexpr Ray ray{{0.0, 2.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr Intersection expected{};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayOriginsInSphere() {
	constexpr Ray ray{{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr Intersection expected{-1.0, 1.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayOriginsBeyonSphere() {
	constexpr Ray ray{{0.0, 0.0, 5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr Intersection expected{-6.0, -4.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

cute::suite make_suite_RayTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testPropertiesOfRay));
	s.push_back(CUTE(testRayPosition));
	s.push_back(CUTE(testRayIntersectionWithSphere));
	s.push_back(CUTE(testRayTouchesSphere));
	s.push_back(CUTE(testRayMissesSphere));
	s.push_back(CUTE(testRayOriginsInSphere));
	s.push_back(CUTE(testRayOriginsBeyonSphere));
	return s;
}
