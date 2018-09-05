#include "ColorTestSuite.h"
#include "cute.h"
#include "Color.h"

void testDefaultColorRedComponent() {
	ASSERT_EQUAL(0.0, Color{}.red);
}

void testDefaultColorGreenComponent() {
	ASSERT_EQUAL(0.0, Color{}.green);
}

void testDefaultColorBlueComponent() {
	ASSERT_EQUAL(0.0, Color{}.blue);
}

void testSimpleColorRedComponent() {
	Color const c{-0.5, 0.4, 1.7};
	ASSERT_EQUAL(-0.5, c.red);
}

void testSimpleColorGreenComponent() {
	Color const c{-0.5, 0.4, 1.7};
	ASSERT_EQUAL(0.4, c.green);
}

void testSimpleColorBlueComponent() {
	Color const c{-0.5, 0.4, 1.7};
	ASSERT_EQUAL(1.7, c.blue);
}

void testColorIsEqualToItself() {
	Color const c{0.9, 0.6, 0.75};
	ASSERT_EQUAL(c, c);
}

void testColorIsNotEqualToDifferentColor() {
	Color const c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	ASSERT_NOT_EQUAL_TO(c1, c2);
}

void testAddColorToColor() {
	Color c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	Color const expected{1.6, 0.7, 1.0};
	c1 += c2;
	ASSERT_EQUAL(expected, c1);
}

void testAddColors() {
	Color const c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	Color const expected{1.6, 0.7, 1.0};
	ASSERT_EQUAL(expected, c1 + c2);
}

void testNegateColor() {
	Color const c{0.9, 0.6, -0.75};
	Color const expected{-0.9, -0.6, 0.75};
	ASSERT_EQUAL(expected, -c);
}

void testSubtractColorFromColor() {
	Color c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	Color const expected{0.2, 0.5, 0.5};
	c1 -= c2;
	ASSERT_EQUAL(expected, c1);
}

void testSubtractTwoColors() {
	Color c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	Color const expected{0.2, 0.5, 0.5};
	ASSERT_EQUAL(expected, c1 - c2);
}

void testMutiplyColorByScalar() {
	Color const color{0.9, 0.6, 0.75};
	Color const expected{0.45, 0.3, 0.375};
	ASSERT_EQUAL(expected, color * 0.5);
}

void testMutiplyScalarByColor() {
	Color const color{0.9, 0.6, 0.75};
	Color const expected{0.45, 0.3, 0.375};
	ASSERT_EQUAL(expected, 0.5 * color);
}

void testHadamardProductWithColor() {
	Color c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	c1 *= c2;
	Color const expected{0.63, 0.06, 0.1875};
	ASSERT_EQUAL(expected, c1);
}

void testHadamardProductOfColors() {
	Color const c1{0.9, 0.6, 0.75};
	Color const c2{0.7, 0.1, 0.25};
	Color const expected{0.63, 0.06, 0.1875};
	ASSERT_EQUAL(expected, c1 * c2);
}

cute::suite make_suite_ColorTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultColorRedComponent));
	s.push_back(CUTE(testDefaultColorGreenComponent));
	s.push_back(CUTE(testDefaultColorBlueComponent));
	s.push_back(CUTE(testSimpleColorRedComponent));
	s.push_back(CUTE(testSimpleColorGreenComponent));
	s.push_back(CUTE(testSimpleColorBlueComponent));
	s.push_back(CUTE(testColorIsEqualToItself));
	s.push_back(CUTE(testColorIsNotEqualToDifferentColor));
	s.push_back(CUTE(testAddColorToColor));
	s.push_back(CUTE(testAddColors));
	s.push_back(CUTE(testNegateColor));
	s.push_back(CUTE(testSubtractColorFromColor));
	s.push_back(CUTE(testSubtractTwoColors));
	s.push_back(CUTE(testMutiplyColorByScalar));
	s.push_back(CUTE(testMutiplyScalarByColor));
	s.push_back(CUTE(testHadamardProductWithColor));
	s.push_back(CUTE(testHadamardProductOfColors));
	return s;
}
