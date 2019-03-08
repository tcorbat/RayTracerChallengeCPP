#include "ShapesTestSuite.h"
#include "cute.h"

#include "Sphere.h"

using namespace Shapes;

void testDefaultInitializedSphere() {
	Sphere const sphere{};
	ASSERT_EQUAL(identity<4>, sphere.transform);
}

cute::suite make_suite_ShapesTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultInitializedSphere));
	return s;
}
