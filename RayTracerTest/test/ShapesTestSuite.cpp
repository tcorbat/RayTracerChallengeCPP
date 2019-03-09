#include "ShapesTestSuite.h"
#include "cute.h"

#include "Sphere.h"

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

cute::suite make_suite_ShapesTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultInitializedSphere));
	s.push_back(CUTE(testSphereWithCustomTransform));
	return s;
}
