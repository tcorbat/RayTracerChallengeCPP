#include "MaterialTestSuite.h"
#include "cute.h"
#include "Color.h"
#include "Material.h"

#include <tuple>

void testDefaultMaterialValues() {

	ASSERT_EQUAL(std::make_tuple(Colors::white, 0.1, 0.9, 0.9, 200.0),
			     std::tie(defaultMaterial.color, defaultMaterial.ambient, defaultMaterial.diffuse, defaultMaterial.specular, defaultMaterial.shininess));
}

cute::suite make_suite_MaterialTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testDefaultMaterialValues));
	return s;
}
