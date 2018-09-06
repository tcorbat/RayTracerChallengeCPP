#include "DirectionTestSuite.h"
#include "Direction.h"
#include "cute.h"

void testSimpleDirectionXComponent() {
	constexpr Direction d{4.3, -4.2, 3.1};
	ASSERT_EQUAL(4.3, d.x);
}

void testSimpleDirectionYComponent(){
	constexpr Direction d{4.3, -4.2, 3.1};
	ASSERT_EQUAL(-4.2, d.y);
}

void testSimpleDirectionZComponent(){
	constexpr Direction d{4.3, -4.2, 3.1};
	ASSERT_EQUAL(3.1, d.z);
}



cute::suite make_suite_DirectionTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testSimpleDirectionXComponent));
	s.push_back(CUTE(testSimpleDirectionYComponent));
	s.push_back(CUTE(testSimpleDirectionZComponent));
	return s;
}
