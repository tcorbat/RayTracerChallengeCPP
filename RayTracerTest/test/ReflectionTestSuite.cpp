#include "ReflectionTestSuite.h"
#include "cute.h"
#include "Direction.h"
#include "Reflection.h"


void testReflectionAt45DegreeAngle() {
	constexpr Direction expected{1.0, 1.0, 0.0};
	constexpr Direction reflected{1.0, -1.0, 0.0};
	constexpr Direction reflectorNormal{0.0, 1.0, 0.0};
	constexpr auto reflection = reflect(reflected, reflectorNormal);
	ASSERT_EQUAL(expected, reflection);
}

void testReflectionOffSlantedSurface() {
	constexpr Direction expected{1.0, 0.0, 0.0};
	constexpr Direction reflected{0, -1.0, 0.0};
	constexpr Direction reflectorNormal{std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0, 0};
	constexpr auto reflection = reflect(reflected, reflectorNormal);
	ASSERT_EQUAL(expected, reflection);
}

cute::suite make_suite_ReflectionTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testReflectionAt45DegreeAngle));
	s.push_back(CUTE(testReflectionOffSlantedSurface));
	return s;
}
