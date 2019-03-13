#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "PointTestSuite.h"
#include "ApplicationTestSuite.h"
#include "DirectionTestSuite.h"
#include "OperationsTestSuite.h"
#include "ColorTestSuite.h"
#include "CanvasTestSuite.h"
#include "LightTestSuite.h"
#include "MatrixTestSuite.h"
#include "RayTestSuite.h"
#include "ReflectionTestSuite.h"
#include "ShapesTestSuite.h"
#include "TransformationsTestSuite.h"



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	char const * testResultsFilePath = "TestResults/TestResults";
	cute::xml_file_opener xmlfile(1, &testResultsFilePath);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);

	auto const runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	auto pointTestSuite = make_suite_PointTestSuite();
	success &= runner(pointTestSuite, "Point Test Suite");

	auto directionTestSuite = make_suite_DirectionTestSuite();
	success &= runner(directionTestSuite, "Direction Test Suite");

	auto operationsTestSuite = make_suite_OperationsTestSuite();
	success &= runner(operationsTestSuite, "Operations Test Suite");

	auto colorTestSuite = make_suite_ColorTestSuite();
	success &= runner(colorTestSuite, "Color Test Suite");

	auto canvasTestSuite = make_suite_CanvasTestSuite();
	success &= runner(canvasTestSuite, "Canvas Test Suite");

	auto lightTestSuite = make_suite_LightTestSuite();
	success &= runner(lightTestSuite, "Light Test Suite");

	auto matrixTestSuite = make_suite_MatrixTestSuite();
	success &= runner(matrixTestSuite, "Matrix Test Suite");

	auto transformationsTestSuite = make_suite_TransformationsTestSuite();
	success &= runner(transformationsTestSuite, "Transformations Test Suite");

	auto rayTestSuite = make_suite_RayTestSuite();
	success &= runner(rayTestSuite, "Ray Test Suite");

	auto reflectionTestSuite = make_suite_ReflectionTestSuite();
	success &= runner(reflectionTestSuite, "Reflection Test Suite");

	auto shapesTestSuite = make_suite_ShapesTestSuite();
	success &= runner(shapesTestSuite, "Shapes Test Suite");

	auto applicationTestSuite = make_suite_ApplicationTestSuite();
	success &= runner(applicationTestSuite, "Application Test Suite");

	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
