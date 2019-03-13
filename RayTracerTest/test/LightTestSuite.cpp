#include "LightTestSuite.h"
#include "Color.h"
#include "cute.h"
#include "Light.h"
#include "Material.h"
#include "Point.h"

#include <tuple>

void testLightHasPointAndIntensity() {
	constexpr Point position{0.0, 0.0, 0.0};
	constexpr Color intensity{1.0, 1.0, 1.0};
	constexpr auto light = pointLight(position, intensity);
	ASSERT_EQUAL(std::tie(position, intensity), std::tie(light.position, light.intensity));
}

constexpr Point position{0.0, 0.0, 0.0};
constexpr Direction normal{0.0, 0.0, -1.0};

void testLightingWithEyeBetweenLightAndSurface() {
	constexpr Color expected{1.9, 1.9, 1.9};
	constexpr Direction eye{0.0, 0.0, -1.0};
	constexpr auto light = pointLight({0.0, 0.0, -10.0}, Colors::white);
	constexpr auto result = lighting(defaultMaterial, light, position, eye, normal);
	ASSERT_EQUAL(expected, result);
}

void testLightingWithEyeBetweenLightAndSurfaceEyeAt45DegreeAngle() {
	constexpr Color expected{1.0, 1.0, 1.0};
	constexpr Direction eye{0.0, std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0};
	constexpr auto light = pointLight({0.0, 0.0, -10.0}, Colors::white);
	constexpr auto result = lighting(defaultMaterial, light, position, eye, normal);
	ASSERT_EQUAL(expected, result);
}

void testLightingWithEyeOppositeSurfaceLightAt45DegreeAngle() {
	constexpr Color expected{0.736396, 0.736396, 0.736396};
	constexpr Direction eye{0.0, 0.0, -1.0};
	constexpr auto light = pointLight({0.0, 10.0, -10.0}, Colors::white);
	constexpr auto result = lighting(defaultMaterial, light, position, eye, normal);
	ASSERT_EQUAL(expected, result);
}

void testLightingWithEyeInPathOfReflectionVector() {
	constexpr Color expected{1.636396, 1.636396, 1.636396};
	constexpr Direction eye{0.0, -std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0};
	constexpr auto light = pointLight({0.0, 10.0, -10.0}, Colors::white);
	constexpr auto result = lighting(defaultMaterial, light, position, eye, normal);
	ASSERT_EQUAL(expected, result);
}

void testLightingWithLightBehindSurface() {
	constexpr Color expected{0.1, 0.1, 0.1};
	constexpr Direction eye{0.0, 0.0, -1.0};
	constexpr auto light = pointLight({0.0, 0.0, 10.0}, Colors::white);
	constexpr auto result = lighting(defaultMaterial, light, position, eye, normal);
	ASSERT_EQUAL(expected, result);
}

cute::suite make_suite_LightTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testLightHasPointAndIntensity));
	s.push_back(CUTE(testLightingWithEyeBetweenLightAndSurface));
	s.push_back(CUTE(testLightingWithEyeBetweenLightAndSurfaceEyeAt45DegreeAngle));
	s.push_back(CUTE(testLightingWithEyeOppositeSurfaceLightAt45DegreeAngle));
	s.push_back(CUTE(testLightingWithEyeInPathOfReflectionVector));
	s.push_back(CUTE(testLightingWithLightBehindSurface));
	return s;
}
