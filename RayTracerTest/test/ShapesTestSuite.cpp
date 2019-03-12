#include "ShapesTestSuite.h"
#include "cute.h"

#include "Pi.h"
#include "Sphere.h"
#include "Transformations.h"

using namespace Shapes;

void testDefaultInitializedSphere() {
	constexpr Sphere sphere{};
	ASSERT_EQUAL(identity<4>, sphere.transform);
}

void testSphereWithCustomTransform() {
	constexpr Matrix<4, 4> expected{2, 3, 4};
	constexpr Sphere sphere{{}, expected};
	ASSERT_EQUAL(expected, sphere.transform);
}

void testNormalOnSphereOnXAxis() {
	constexpr Direction expected{1, 0, 0};
	constexpr Sphere sphere{};
	auto const result = normalAt(sphere, {1, 0, 0});
	ASSERT_EQUAL(expected, result);
}

void testNormalOnSphereOnYAxis() {
	constexpr Direction expected{0, 1, 0};
	constexpr Sphere sphere{};
	auto const result = normalAt(sphere, {0, 1, 0});
	ASSERT_EQUAL(expected, result);
}

void testNormalOnSphereOnZAxis() {
	constexpr Direction expected{0, 0, 1};
	constexpr Sphere sphere{};
	auto const result = normalAt(sphere, {0, 0, 1});
	ASSERT_EQUAL(expected, result);
}

void testNormalOnSphereOnNonAxialPoint() {
	constexpr double val{std::sqrt(3.0) / 3.0};
	constexpr Direction expected{val, val, val};
	constexpr Sphere sphere{};
	auto const result = normalAt(sphere, {val, val, val});
	ASSERT_EQUAL(expected, result);
}

void testNormalIsNormalized() {
	constexpr double val{std::sqrt(3.0) / 3.0};
	constexpr Direction expected{val, val, val};
	constexpr Sphere sphere{};
	auto const result = normalAt(sphere, {val, val, val});
	ASSERT_EQUAL(expected, normalize(result));
}

void testNormalOnTranslatedSphere() {
	constexpr Direction expected{0.0, 0.707107, -0.707107};
	constexpr Sphere sphere{{}, translation(0.0, 1.0, 0.0)};
	constexpr auto result = normalAt(sphere, {0.0, 1.707107, -0.707107});
	ASSERT_EQUAL(expected, result);
}

void testNormalOnTransformedSphere() {
	constexpr Direction expected{0.0, 0.970143, -0.242536};
	constexpr auto transform = scaling(1.0, 0.5, 1.0) * rotation_z(pi<double>);
	constexpr Sphere sphere{{}, transform};
	constexpr auto result = normalAt(sphere, {0.0, std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0});
	ASSERT_EQUAL(expected, result);
}


cute::suite make_suite_ShapesTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultInitializedSphere));
	s.push_back(CUTE(testSphereWithCustomTransform));
	s.push_back(CUTE(testNormalOnSphereOnXAxis));
	s.push_back(CUTE(testNormalOnSphereOnYAxis));
	s.push_back(CUTE(testNormalOnSphereOnZAxis));
	s.push_back(CUTE(testNormalOnSphereOnNonAxialPoint));
	s.push_back(CUTE(testNormalIsNormalized));
	s.push_back(CUTE(testNormalOnTranslatedSphere));
	s.push_back(CUTE(testNormalOnTransformedSphere));
	return s;
}
