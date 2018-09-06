#include "CanvasTestSuite.h"
#include "Canvas.h"
#include "cute.h"

#include <sstream>
#include <string>

void testCanvasIsInitiallyBlack() {
	Canvas const canvas{20_column, 10_row};
	constexpr Color black{};

	forEachIndex(canvas, [&](CanvasIndex const & index) {
			Color const cellColor = canvas[index];
			ASSERT_EQUAL(black, cellColor);
	});
}

void testSetPixelColorToRed() {
	Canvas canvas{20_column, 10_row};
	constexpr Color red{1.0, 0.0, 0.0};

	canvas[3_column, 2_row] = red;
	Color const targetCellColor = canvas[3_column, 2_row];
	ASSERT_EQUAL(red, targetCellColor);
}

void testOutOfRangeRowAccessThrows() {
	Canvas const canvas{20_column, 10_row};
	ASSERT_THROWS((canvas[10_column, 10_row]), std::invalid_argument);
}

void testOutOfRangeColumnAccessThrows() {
	Canvas const canvas{20_column, 10_row};
	ASSERT_THROWS((canvas[20_column, 9_row]), std::invalid_argument);
}

void testOutOfRangeRowAndColumnAccessThrows() {
	Canvas const canvas{20_column, 10_row};
	ASSERT_THROWS((canvas[20_column, 10_row]), std::invalid_argument);
}

void testPrintPPMHeader() {
	std::string const expected{
		"P3\n"
		"5 3\n"
		"255\n"
	};
	Canvas const canvas{5_column, 3_row};
	std::ostringstream output{};
	printPPMHeader(output, canvas);
	ASSERT_EQUAL(expected, output.str());
}

void testPrintPixels() {
	std::string const expected{
		"255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
		"0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
		"0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"
	};
	Canvas canvas{5_column, 3_row};
	canvas[0_column, 0_row] = {1.5, 0, 0};
	canvas[2_column, 1_row] = {0, 0.5, 0};
	canvas[4_column, 2_row] = {-0.5, 0, 1};
	std::ostringstream output{};
	printPPMPixels(output, canvas);
	ASSERT_EQUAL(expected, output.str());
}

//Test is deliberately different from book. Linebreak after whole color to have components of the same color together
void testPrintPixelsWithMaxSeventyWidth() {
	std::string const expected{
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
		"255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
	};
	constexpr Color navajoWhite{1.0, 0.8, 0.6};
	Canvas canvas{10_column, 2_row};
	forEachIndex(canvas, [&] (CanvasIndex const & index) {
		canvas[index] = navajoWhite;
	});
	std::ostringstream output{};
	printPPMPixels(output, canvas);
	ASSERT_EQUAL(expected, output.str());
}


cute::suite make_suite_CanvasTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testCanvasIsInitiallyBlack));
	s.push_back(CUTE(testSetPixelColorToRed));
	s.push_back(CUTE(testOutOfRangeRowAccessThrows));
	s.push_back(CUTE(testOutOfRangeColumnAccessThrows));
	s.push_back(CUTE(testOutOfRangeRowAndColumnAccessThrows));
	s.push_back(CUTE(testPrintPPMHeader));
	s.push_back(CUTE(testPrintPixels));
	s.push_back(CUTE(testPrintPixelsWithMaxSeventyWidth));
	return s;
}
