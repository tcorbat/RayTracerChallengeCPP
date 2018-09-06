#include "OperationsTestSuite.h"

#include "Direction.h"
#include "Point.h"
#include "cute.h"

#include <tuple>

void testPointIsEqualToItself() {
	constexpr Point point{1.5, -2.2, 10.9};
	ASSERT_EQUAL(point, point);
}

void testDifferentPointsAreNotEqual() {
	constexpr Point first{1.5, -2.2, 10.9};
	constexpr Point other{1.4, -2.2, 10.9};
	ASSERT_NOT_EQUAL_TO(first, other);
}

void testDefaultPointIsZeroZeroZero() {
	constexpr Point zero{0.0, 0.0, 0.0};
	constexpr Point point{};
	ASSERT_EQUAL(zero, point);
}

void testDirectionIsEqualToItself() {
	constexpr Direction direction{1.5, -2.2, 10.9};
	ASSERT_EQUAL(direction, direction);
}

void testDifferentDirectionsAreNotEqual() {
	constexpr Direction first{1.5, -2.2, 10.9};
	constexpr Direction other{1.4, -2.2, 10.9};
	ASSERT_NOT_EQUAL_TO(first, other);
}


void testDefaultDirectionIsZeroZeroZero() {
	constexpr Direction zero{0.0, 0.0, 0.0};
	constexpr Direction direction{};
	ASSERT_EQUAL(zero, direction);
}

void testAddingTwoDirections() {
	constexpr Direction first{1.5, -7.3, -0.9};
	constexpr Direction second{47.8, 15.1, -1.2};
	constexpr Direction expected{49.3, 7.8, -2.1};
	ASSERT_EQUAL(expected, first + second);
}

void testAddingPointAndDirection() {
	constexpr Point point{5.0, 98.3, -7.8};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	constexpr Point expected{-82.1, 114.8, -14.7};
	ASSERT_EQUAL(expected, point + direction);
}

void testAddingDirectionAndPoint() {
	constexpr Point point{5.0, 98.3, -7.8};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	constexpr Point expected{-82.1, 114.8, -14.7};
	ASSERT_EQUAL(expected, direction + point);
}

void testAddingDirectionToPoint() {
	Point point{5.0, 98.3, -7.8};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	constexpr Point expected{-82.1, 114.8, -14.7};
	point += direction;
	ASSERT_EQUAL(expected, point);
}

void testSubtractTwoPoints() {
	constexpr Point start{5.0, 98.3, -7.8};
	constexpr Point end{-82.1, 114.8, -14.7};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	ASSERT_EQUAL(direction, end - start);
}

void testSubtractPointAndDirection() {
	constexpr Point start{5.0, 98.3, -7.8};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	constexpr Point expected{92.1, 81.8, -0.9};
	ASSERT_EQUAL(expected, start - direction);
}

void testSubtractDirectionFromPoint() {
	Point start{5.0, 98.3, -7.8};
	constexpr Direction direction{-87.1, 16.5, -6.9};
	start -= direction;
	constexpr Point expected{92.1, 81.8, -0.9};
	ASSERT_EQUAL(expected, start);
}

void testNegateDirection() {
	constexpr Direction direction{-87.1, 16.5, -6.9};
	constexpr Direction expected{87.1, -16.5, 6.9};
	ASSERT_EQUAL(expected, -direction);
}

void testSubtractTwoDirections() {
	constexpr Direction first{5.0, 98.3, -7.8};
	constexpr Direction second{-82.1, 114.8, -14.7};
	constexpr Direction expected{87.1, -16.5, 6.9};
	ASSERT_EQUAL(expected, first - second);
}

void testSubtractDirectionFromDirection() {
	Direction first{5.0, 98.3, -7.8};
	constexpr Direction second{-82.1, 114.8, -14.7};
	first -= second;
	constexpr Direction expected{87.1, -16.5, 6.9};
	ASSERT_EQUAL(expected, first);
}

void testStretchDirection() {
	Direction direction{9.1, -17.3, 5.7};
	constexpr double factor{3.5};
	constexpr Direction expected{31.85, -60.55, 19.95};
	direction *= factor;
	ASSERT_EQUAL(expected, direction);
}

void testMultiplyDirectionAndScalar() {
	constexpr Direction direction{9.1, -17.3, 5.7};
	constexpr double factor{3.5};
	constexpr Direction expected{31.85, -60.55, 19.95};
	ASSERT_EQUAL(expected, direction * factor);
}

void testMultiplyScalarAndDirection() {
	constexpr Direction direction{9.1, -17.3, 5.7};
	constexpr double factor{3.5};
	constexpr Direction expected{31.85, -60.55, 19.95};
	ASSERT_EQUAL(expected, factor * direction);
}

void testShrinkDirection() {
	Direction direction{9.1, -17.3, 5.7};
	constexpr double factor{3.5};
	constexpr Direction expected{2.6, -4.942857, 1.628571};
	direction /= factor;
	ASSERT_EQUAL(expected, direction);
}

void testDivideDirectionByScalar() {
	constexpr Direction direction{9.1, -17.3, 5.7};
	constexpr double divisor{3.5};
	constexpr Direction expected{2.6, -4.942857, 1.628571};
	ASSERT_EQUAL(expected, direction / divisor);
}

void testMagnitudeOfDefaultDirection() {
	constexpr auto mag = magnitude(Direction{});
	ASSERT_EQUAL(0.0, mag);
}

void testMagnitudesOfUnitDirection() {
	constexpr Direction d1{1, 0, 0};
	constexpr Direction d2{0, 1, 0};
	constexpr Direction d3{0, 0, 1};

	constexpr auto const expected = std::make_tuple(1, 1, 1);
	constexpr auto const result = std::make_tuple(magnitude(d1), magnitude(d2), magnitude(d3));
	ASSERT_EQUAL(expected, result);
}

void testMagnitudeOfLongDirection() {
	constexpr Direction direction{9.1, -17.3, 5.7};
	constexpr double expected{20.361483};
	ASSERT_EQUAL_DELTA(expected, magnitude(direction), epsilon<double>);
}

void testNormalizeDefaultDirectionThrows() {
	constexpr Direction direction{};
	ASSERT_THROWS(normalize(direction), std::invalid_argument);
}

void testNormalizeSingleComponentDirection() {
	constexpr Direction d1{4, 0, 0};
	constexpr Direction d2{0, 5, 0};
	constexpr Direction d3{0, 0, -5};

	constexpr Direction e1{1, 0, 0};
	constexpr Direction e2{0, 1, 0};
	constexpr Direction e3{0, 0, -1};

	constexpr auto const expected = std::make_tuple(e1, e2, e3);
	constexpr auto const result = std::make_tuple(normalize(d1), normalize(d2), normalize(d3));
	ASSERT_EQUAL(expected, result);
}

void testNormalizeDirection() {
	constexpr Direction direction{1, -2, 3};
	constexpr Direction normalized = normalize(direction);
	constexpr Direction expected{0.267261, -0.534522, 0.801784};
	ASSERT_EQUAL(expected, normalized);
}

void testDotProductOfDirections() {
	constexpr Direction d1{1.0, 2.0, 3.0};
	constexpr Direction d2{2.0, 3.0, 4.0};
	ASSERT_EQUAL(20.0, dot(d1, d2));
}

void testCrossProductOfDirections() {
	constexpr Direction d1{1.0, 2.0, 3.0};
	constexpr Direction d2{2.0, 3.0, 4.0};
	constexpr Direction expected{-1, 2, -1};
	ASSERT_EQUAL(expected, cross(d1, d2));
}

cute::suite make_suite_OperationsTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testPointIsEqualToItself));
	s.push_back(CUTE(testDifferentPointsAreNotEqual));
	s.push_back(CUTE(testDefaultPointIsZeroZeroZero));
	s.push_back(CUTE(testDirectionIsEqualToItself));
	s.push_back(CUTE(testDifferentDirectionsAreNotEqual));
	s.push_back(CUTE(testDefaultDirectionIsZeroZeroZero));
	s.push_back(CUTE(testAddingTwoDirections));
	s.push_back(CUTE(testAddingPointAndDirection));
	s.push_back(CUTE(testAddingDirectionAndPoint));
	s.push_back(CUTE(testAddingDirectionToPoint));
	s.push_back(CUTE(testSubtractTwoPoints));
	s.push_back(CUTE(testSubtractPointAndDirection));
	s.push_back(CUTE(testSubtractDirectionFromPoint));
	s.push_back(CUTE(testNegateDirection));
	s.push_back(CUTE(testSubtractTwoDirections));
	s.push_back(CUTE(testSubtractDirectionFromDirection));
	s.push_back(CUTE(testStretchDirection));
	s.push_back(CUTE(testMultiplyDirectionAndScalar));
	s.push_back(CUTE(testMultiplyScalarAndDirection));
	s.push_back(CUTE(testShrinkDirection));
	s.push_back(CUTE(testDivideDirectionByScalar));
	s.push_back(CUTE(testMagnitudeOfDefaultDirection));
	s.push_back(CUTE(testMagnitudesOfUnitDirection));
	s.push_back(CUTE(testMagnitudeOfLongDirection));
	s.push_back(CUTE(testNormalizeDefaultDirectionThrows));
	s.push_back(CUTE(testNormalizeSingleComponentDirection));
	s.push_back(CUTE(testNormalizeDirection));
	s.push_back(CUTE(testDotProductOfDirections));
	s.push_back(CUTE(testCrossProductOfDirections));
	return s;
}
