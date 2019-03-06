#include "TransformationsTestSuite.h"
#include "Transformations.h"
#include "Pi.h"
#include "cute.h"

#include <cmath>



void testTranslationMatrix() {
	auto const transformation = translation(5.0, -3.0, 2.0);
	Matrix<4, 4> const expected {
		 1.0,  0.0,  0.0,  5.0,
		 0.0,  1.0,  0.0, -3.0,
		 0.0,  0.0,  1.0,  2.0,
		 0.0,  0.0,  0.0,  1.0
	};
	ASSERT_EQUAL(expected, transformation);
}

void testTransformationAppliedToPoint() {
	constexpr auto transformation = translation(5.0, -3.0, 2.0);
	constexpr Point point{-3.0, 4.0, 5.0};
	constexpr Point expected{2.0, 1.0, 7.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testMultiplyInverseOfTranslation() {
	constexpr auto transformation = translation(5.0, -3.0, 2.0);
	constexpr Point point{-3.0, 4.0, 5.0};
	constexpr Point expected{-8.0, 7.0, 3.0};
	ASSERT_EQUAL(expected, inverse(transformation) * point);
}

void testMultiplyTranslationWithDirectionDoesNotChangeDirection() {
	constexpr auto transformation = translation(5.0, -3.0, 2.0);
	constexpr Direction direction{-3.0, 4.0, 5.0};
	ASSERT_EQUAL(direction, transformation * direction);
}

void testScalingMatrix() {
	constexpr auto transformation = scaling(2.0, 3.0, 4.0);
	constexpr Matrix<4, 4> expected {
		2.0, 0.0, 0.0, 0.0,
		0.0, 3.0, 0.0, 0.0,
		0.0, 0.0, 4.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	ASSERT_EQUAL(expected, transformation);
}

void testScalingAppliedToPoint() {
	constexpr auto transformation = scaling(2.0, 3.0, 4.0);
	constexpr Point point{-4.0, 6.0, 8.0};
	constexpr Point expected{-8, 18.0, 32.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testMultiplyInverseOfScaling() {
	constexpr auto transformation = scaling(2.0, 3.0, 4.0);
	constexpr Point point{-4.0, 6.0, 8.0};
	constexpr Point expected{-2.0, 2.0, 2.0};
	ASSERT_EQUAL(expected, inverse(transformation) * point);
}

void testReflectionScaling() {
	constexpr auto transformation = scaling(-1.0, 1.0, 1.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{-2.0, 3.0, 4.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testRotationAroundXAxisHalfQuarter() {
	constexpr Point point{0.0, 1.0, 0.0};
	constexpr auto halfQuarter = rotation_x(pi<double> / 4.0);
	constexpr Point expected{0.0, std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testRotationAroundXAxisQuarter() {
	constexpr Point point{0.0, 1.0, 0.0};
	constexpr auto halfQuarter = rotation_x(pi<double> / 2.0);
	constexpr Point expected{0.0, 0.0, 1.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testInverseRotationAroundXAxisHalfQuarter() {
	constexpr Point point{0.0, 1.0, 0.0};
	constexpr auto halfQuarter = rotation_x(pi<double> / 4.0);
	constexpr Point expected{0.0, std::sqrt(2.0)/2.0, -std::sqrt(2.0)/2.0};
	ASSERT_EQUAL(expected, inverse(halfQuarter) * point);
}

void testRotationAroundYAxisHalfQuarter() {
	constexpr Point point{0.0, 0.0, 1.0};
	constexpr auto halfQuarter = rotation_y(pi<double> / 4.0);
	constexpr Point expected{std::sqrt(2.0)/2.0, 0.0, std::sqrt(2.0)/2.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testRotationAroundYAxisQuarter() {
	constexpr Point point{0.0, 0.0, 1.0};
	constexpr auto halfQuarter = rotation_y(pi<double> / 2.0);
	constexpr Point expected{1.0, 0.0, 0.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testRotationAroundZAxisHalfQuarter() {
	constexpr Point point{0.0, 1.0, 0.0};
	constexpr auto halfQuarter = rotation_z(pi<double> / 4.0);
	constexpr Point expected{-std::sqrt(2.0)/2.0, std::sqrt(2.0)/2.0, 0.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testRotationAroundZAxisQuarter() {
	constexpr Point point{0.0, 1.0, 0.0};
	constexpr auto halfQuarter = rotation_z(pi<double> / 2.0);
	constexpr Point expected{-1.0, 0.0, 0.0};
	ASSERT_EQUAL(expected, halfQuarter * point);
}

void testShearingXInProportionToY() {
	constexpr auto transformation = shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{5.0, 3.0, 4.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testShearingXInProportionToZ() {
	constexpr auto transformation = shearing(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{6.0, 3.0, 4.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testShearingYInProportionToX() {
	constexpr auto transformation = shearing(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{2.0, 5.0, 4.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testShearingYInProportionToZ() {
	constexpr auto transformation = shearing(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{2.0, 7.0, 4.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testShearingZInProportionToX() {
	constexpr auto transformation = shearing(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{2.0, 3.0, 6.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testShearingZInProportionToY() {
	constexpr auto transformation = shearing(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	constexpr Point point{2.0, 3.0, 4.0};
	constexpr Point expected{2.0, 3.0, 7.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testChainingTransformations() {
	constexpr auto A = rotation_x(pi<double> / 2.0);
	constexpr auto B = scaling(5.0, 5.0, 5.0);
	constexpr auto C = translation(10.0, 5.0, 7.0);
	constexpr Point initial{1.0, 0.0, 1.0};
	constexpr auto afterA = A * initial;
	constexpr auto afterB = B * afterA;
	constexpr auto afterC = C * afterB;
	ASSERT_EQUAL(afterC, C * B * A * initial);
}

void testTranslatingARay() {
	constexpr auto expected = Ray::create({4, 6, 8}, {0, 1, 0});

	constexpr auto ray = Ray::create({1, 2, 3}, {0, 1, 0});
	constexpr auto matrix = translation(3, 4, 5);

	constexpr Ray result = transform(ray, matrix);
	ASSERT_EQUAL(expected, result);
}

void testScalingARay() {
	constexpr Ray expected = Ray::create({2, 6, 12}, {0, 3, 0});

	constexpr Ray ray = Ray::create({1, 2, 3}, {0, 1, 0});
	constexpr auto matrix = scaling(2, 3, 4);

	constexpr Ray result = transform(ray, matrix);
	ASSERT_EQUAL(expected, result);
}

cute::suite make_suite_TransformationsTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testTranslationMatrix));
	s.push_back(CUTE(testTransformationAppliedToPoint));
	s.push_back(CUTE(testMultiplyInverseOfTranslation));
	s.push_back(CUTE(testMultiplyTranslationWithDirectionDoesNotChangeDirection));
	s.push_back(CUTE(testScalingMatrix));
	s.push_back(CUTE(testScalingAppliedToPoint));
	s.push_back(CUTE(testMultiplyInverseOfScaling));
	s.push_back(CUTE(testReflectionScaling));
	s.push_back(CUTE(testRotationAroundXAxisHalfQuarter));
	s.push_back(CUTE(testRotationAroundXAxisQuarter));
	s.push_back(CUTE(testInverseRotationAroundXAxisHalfQuarter));
	s.push_back(CUTE(testRotationAroundYAxisHalfQuarter));
	s.push_back(CUTE(testRotationAroundYAxisQuarter));
	s.push_back(CUTE(testRotationAroundZAxisHalfQuarter));
	s.push_back(CUTE(testRotationAroundZAxisQuarter));
	s.push_back(CUTE(testShearingXInProportionToY));
	s.push_back(CUTE(testShearingXInProportionToZ));
	s.push_back(CUTE(testShearingYInProportionToX));
	s.push_back(CUTE(testShearingYInProportionToZ));
	s.push_back(CUTE(testShearingZInProportionToX));
	s.push_back(CUTE(testShearingZInProportionToY));
	s.push_back(CUTE(testChainingTransformations));
	s.push_back(CUTE(testTranslatingARay));
	s.push_back(CUTE(testScalingARay));
	return s;
}
