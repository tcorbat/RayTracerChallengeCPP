#include "TransformationsTestSuite.h"
#include "Transformations.h"
#include "cute.h"



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
	auto const transformation = translation(5.0, -3.0, 2.0);
	Point const point{-3.0, 4.0, 5.0};
	Point const expected{2.0, 1.0, 7.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testMultiplyInverseOfTranslation() {
	auto const transformation = translation(5.0, -3.0, 2.0);
	Point const point{-3.0, 4.0, 5.0};
	Point const expected{-8.0, 7.0, 3.0};
	ASSERT_EQUAL(expected, inverse(transformation) * point);
}

void testMultiplyTranslationWithDirectionDoesNotChangeDirection() {
	auto const transformation = translation(5.0, -3.0, 2.0);
	Direction const direction{-3.0, 4.0, 5.0};
	ASSERT_EQUAL(direction, transformation * direction);
}

void testScalingMatrix() {
	auto const transformation = scaling(2.0, 3.0, 4.0);
	Matrix<4, 4> const expected {
		2.0, 0.0, 0.0, 0.0,
		0.0, 3.0, 0.0, 0.0,
		0.0, 0.0, 4.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	ASSERT_EQUAL(expected, transformation);
}

void testScalingAppliedToPoint() {
	auto const transformation = scaling(2.0, 3.0, 4.0);
	Point const point{-4.0, 6.0, 8.0};
	Point const expected{-8, 18.0, 32.0};
	ASSERT_EQUAL(expected, transformation * point);
}

void testMultiplyInverseOfScaling() {
	auto const transformation = scaling(2.0, 3.0, 4.0);
	Point const point{-4.0, 6.0, 8.0};
	Point const expected{-2.0, 2.0, 2.0};
	ASSERT_EQUAL(expected, inverse(transformation) * point);
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
	return s;
}
