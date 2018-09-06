#include "PointTestSuite.h"

#include "Point.h"
#include "cute.h"

void testSimplePointXComponent() {
	constexpr Point p{4.3, -4.2, 3.1};
	ASSERT_EQUAL(4.3, p.x);
}

void testSimplePointYComponent(){
	constexpr Point p{4.3, -4.2, 3.1};
	ASSERT_EQUAL(-4.2, p.y);
}

void testSimplePointZComponent(){
	constexpr Point p{4.3, -4.2, 3.1};
	ASSERT_EQUAL(3.1, p.z);
}


cute::suite make_suite_PointTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testSimplePointXComponent));
	s.push_back(CUTE(testSimplePointYComponent));
	s.push_back(CUTE(testSimplePointZComponent));
	return s;
}
