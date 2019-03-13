#include "LightTestSuite.h"
#include "Color.h"
#include "cute.h"
#include "Light.h"
#include "Point.h"

#include <tuple>

void testLightHasPointAndIntensity() {
	constexpr Point position{0.0, 0.0, 0.0};
	constexpr Color intensity{1.0, 1.0, 1.0};
	constexpr auto light = pointLight(position, intensity);
	ASSERT_EQUAL(std::tie(position, intensity), std::tie(light.position, light.intensity));
}

cute::suite make_suite_LightTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testLightHasPointAndIntensity));
	return s;
}
