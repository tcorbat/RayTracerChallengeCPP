#include "RayTestSuite.h"
#include "Ray.h"
#include "Direction.h"
#include "Intersections.h"
#include "Point.h"
#include "Sphere.h"
#include "Transformations.h"
#include "cute.h"

#include <tuple>


using Shapes::Sphere;

void testPropertiesOfRay() {
	constexpr Point origin{1.0, 2.0, 3.0};
	constexpr Direction direction{4.0, 5.0, 6.0};
	constexpr Ray ray{origin, direction};
	ASSERT_EQUAL(std::tie(origin, direction), std::tie(ray.origin, ray.direction));
}

void testRayEquality() {
	constexpr Point origin{1.0, 2.0, 3.0};
	constexpr Direction direction{4.0, 5.0, 6.0};
	constexpr Ray ray{origin, direction};
	constexpr Ray expected{origin, direction};
	ASSERT_EQUAL(expected, ray);
}

void testRayInequality() {
	constexpr Ray first{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
	constexpr Ray second{{2.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
	ASSERT_NOT_EQUAL_TO(first, second);
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
	constexpr Ray ray{{ 2.0, 3.0, 4.0 }, { 1.0, 0.0, 0.0 }};
	for (auto const & testEntry : rayPositions) {
		ASSERT_EQUAL_DDT(testEntry.expected, ray.position(testEntry.time), testEntry.failure);
	}
}

void testRayIntersectionWithSphere() {
	constexpr Ray ray{{0.0, 0.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr IntersectionResult expected{sphere, 4.0, 6.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayTouchesSphere() {
	constexpr Ray ray{{0.0, 1.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr IntersectionResult expected{sphere, 5.0, 5.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayMissesSphere() {
	constexpr Ray ray{{0.0, 2.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr IntersectionResult expected{};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayOriginsInSphere() {
	constexpr Ray ray{{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr IntersectionResult expected{sphere, -1.0, 1.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testRayOriginsBeyonSphere() {
	constexpr Ray ray{{0.0, 0.0, 5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr IntersectionResult expected{sphere, -6.0, -4.0};
	constexpr auto intersections = intersect(sphere, ray);
	ASSERT_EQUAL(expected, intersections);
}

void testIntersectionsStructure() {
	constexpr Sphere sphere{};
	constexpr Intersection i1{1.0, sphere};
	constexpr Intersection i2{2.0, sphere};
	constexpr auto intersects = intersections(i1, i2);
	constexpr Intersections<Sphere, Sphere> expected{i1, i2};
	ASSERT_EQUAL(expected, intersects);
}

void testIntersectObjectContent() {
	constexpr Ray ray{{0.0, 0.0, -5.0}, {0.0, 0.0, 1.0}};
	constexpr Sphere sphere{};
	constexpr auto inters = intersect(sphere, ray);
	ASSERT_EQUAL(std::tie(sphere, sphere), std::tie(std::get<Sphere>(inters[0].object), std::get<Sphere>(inters[1].object)));
}

void testHitWithPositiveTime() {
	constexpr Sphere sphere{};
	constexpr Intersection i1{1.0, sphere};
	constexpr Intersection i2{2.0, sphere};
	constexpr auto inters = intersections(i1, i2);
	constexpr auto result = hit(inters);
	ASSERT_EQUAL(i1, result.value());
}

void testHitWithMixedTime() {
	constexpr Sphere sphere{};
	constexpr Intersection i1{-1.0, sphere};
	constexpr Intersection i2{1.0, sphere};
	constexpr auto inters = intersections(i1, i2);
	constexpr auto result = hit(inters);
	ASSERT_EQUAL(i2, result.value());
}

void testHitWithNegativeTime() {
	constexpr Sphere sphere{};
	constexpr Intersection i1{-2.0, sphere};
	constexpr Intersection i2{-1.0, sphere};
	constexpr auto inters = intersections(i1, i2);
	constexpr auto result = hit(inters);
	ASSERT(!result);
}

void testHitReturnsLowestNonNegativeTime() {
	constexpr Sphere sphere{};
	constexpr Intersection i1{5.0, sphere};
	constexpr Intersection i2{7.0, sphere};
	constexpr Intersection i3{-3.0, sphere};
	constexpr Intersection i4{2.0, sphere};
	constexpr auto inters = intersections(i1, i2, i3, i4);
	constexpr auto result = hit(inters);
	ASSERT_EQUAL(i4, result.value());
}

void testIntersetingAScaledSphereWithARay() {
	constexpr Ray ray{{0, 0, -5}, {0, 0, 1}};
	constexpr Sphere sphere{{}, scaling(2.0, 2.0, 2.0)};
	constexpr auto intersectResult = intersect(sphere, ray);
	ASSERT_EQUAL(std::make_tuple(2, 3.0, 7.0), std::tie(intersectResult.count, intersectResult[0].time, intersectResult[1].time));
}

void testIntersetingATranslatedSphereWithARay() {
	constexpr Ray ray{{0, 0, -5}, {0, 0, 1}};
	constexpr Sphere sphere{{}, translation(5.0, 0.0, 0.0)};
	constexpr auto intersectResult = intersect(sphere, ray);
	ASSERT_EQUAL(intersectResult.count, 0);
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
	s.push_back(CUTE(testIntersectionsStructure));
	s.push_back(CUTE(testIntersectObjectContent));
	s.push_back(CUTE(testHitWithPositiveTime));
	s.push_back(CUTE(testHitWithMixedTime));
	s.push_back(CUTE(testHitWithNegativeTime));
	s.push_back(CUTE(testHitReturnsLowestNonNegativeTime));
	s.push_back(CUTE(testRayEquality));
	s.push_back(CUTE(testRayInequality));
	s.push_back(CUTE(testIntersetingAScaledSphereWithARay));
	s.push_back(CUTE(testIntersetingATranslatedSphereWithARay));
	return s;
}
