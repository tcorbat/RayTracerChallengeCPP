#include "TransformationsTestSuite.h"
#include "Transformations.h"
#include "cute.h"

#include <boost/math/constants/constants.hpp>
#include <cmath>

template <typename T>
constexpr auto pi = boost::math::constants::pi<double>();


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
	return s;
}
