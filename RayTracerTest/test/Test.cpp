#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../test/PointTestSuite.h"
#include "ApplicationTestSuite.h"
#include "DirectionTestSuite.h"
#include "OperationsTestSuite.h"
#include "ColorTestSuite.h"
#include "CanvasTestSuite.h"
#include "MatrixTestSuite.h"
#include "TransformationsTestSuite.h"



bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	cute::suite PointTestSuite = make_suite_PointTestSuite();
	success &= runner(PointTestSuite, "Point Test Suite");

	cute::suite DirectionTestSuite = make_suite_DirectionTestSuite();
	success &= runner(DirectionTestSuite, "Direction Test Suite");

	cute::suite OperationsTestSuite = make_suite_OperationsTestSuite();
	success &= runner(OperationsTestSuite, "Operations Test Suite");

	cute::suite Application = make_suite_ApplicationTestSuite();
	success &= runner(Application, "Application Test Suite");

	cute::suite ColorTestSuite = make_suite_ColorTestSuite();
	success &= runner(ColorTestSuite, "Color Test Suite");

	cute::suite CanvasTestSuite = make_suite_CanvasTestSuite();
	success &= runner(CanvasTestSuite, "Canvas Test Suite");

	cute::suite MatrixTestSuite = make_suite_MatrixTestSuite();
	success &= runner(MatrixTestSuite, "Matrix Test Suite");

	cute::suite TransformationsTestSuite = make_suite_TransformationsTestSuite();
	success &= runner(TransformationsTestSuite, "Transformations Test Suite");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
