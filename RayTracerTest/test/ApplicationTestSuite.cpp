#include "ApplicationTestSuite.h"

#include "Canvas.h"
#include "Direction.h"
#include "Intersections.h"
#include "Light.h"
#include "Pi.h"
#include "Point.h"
#include "Sphere.h"
#include "Transformations.h"
#include "cute.h"

#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <variant>

std::string const outputDirectory{"TestResults/"};

struct Projectile {
	Point location;
	Direction velocity;
};

struct World {
	Direction const gravity;
	Direction const wind;
};

Projectile tick(World const & world, Projectile const & projectile) {
	return {
		projectile.location + projectile.velocity,
		projectile.velocity + world.gravity + world.wind
	};
}

void testProjectileTrajectory() {
	Projectile projectile{{0.0, 1.0, 0.0}, normalize({1.0, 1.0, 0.0})};
	constexpr World world{{0.0, -0.1, 0.0}, {-0.01, 0.0, 0.0}};

	std::vector<Point> const expected{
		{0.0, 1.0, 0.0},
		{0.707107, 1.707107, 0},
		{1.404214, 2.314214, 0},
		{2.091320, 2.821320, 0},
		{2.768427, 3.228427, 0},
		{3.435534, 3.535534, 0},
		{4.092641, 3.742641, 0},
		{4.739747, 3.849747, 0},
		{5.376854, 3.856854, 0},
		{6.003961, 3.763961, 0},
		{6.621068, 3.571068, 0},
		{7.228175, 3.278175, 0},
		{7.825281, 2.885281, 0},
		{8.412388, 2.392388, 0},
		{8.989495, 1.799495, 0},
		{9.556602, 1.106602, 0},
		{10.113708, 0.313708, 0}
	};
	std::vector<Point> trajectory{};

	do {
		trajectory.push_back(projectile.location);
		projectile = tick(world, projectile);
	} while (projectile.location.y > 0.0);

	ASSERT_EQUAL(expected, trajectory);
}

void testProjectileTraceOnCanvas() {
	constexpr Color projectileColor{0.25, 1.0, 0};
	constexpr Point startingPoint{0.0, 1.0, 0.0};
	constexpr Direction projectileVelocity = normalize({1, 1.8, 0}) * 11.25;
	Projectile projectile{startingPoint, projectileVelocity};
	constexpr Direction gravity{0.0, -0.1, 0.0};
	constexpr Direction wind{-0.01, 0, 0};
	constexpr World world{gravity, wind};
	Canvas traceCanvas{900_column, 550_row};
	do {
		traceCanvas[projectile.location] = projectileColor;
		projectile = tick(world, projectile);
	} while(projectile.location.y > 0.0);

	std::ofstream outputFile{outputDirectory + "projectile.ppm"};
	printPPM(outputFile, traceCanvas);
	ASSERT(outputFile);
}

void testClockWithRotation() {
	constexpr Color clockDotColor{1.0, 1.0, 1.0};
	constexpr Point startingPoint{0.0, 1.0, 0.0};
	Canvas clockCanvas{300_column, 300_row};
	for (auto angle = 0.0; angle < 2 * pi<double>; angle += 2 * pi<double> / 12) {
		auto const scaledPoint = scaling(0.0, 100.0, 0.0) * startingPoint;
		auto const rotatedPoint = rotation_z(angle) * scaledPoint;
		auto const translatedPoint = translation(150.0, 150.0, 0.0) * rotatedPoint;
		clockCanvas[translatedPoint] = clockDotColor;
	}
	std::ofstream outputFile{outputDirectory + "clock.ppm"};
	printPPM(outputFile, clockCanvas);
	ASSERT(outputFile);
}

void testRayHitsSphereCanvas() {
	constexpr Color lightColor{1.0, 1.0, 0.5};
	constexpr Shapes::Sphere sphere{{2.0, 1.5, -1.0}, scaling(10.0, 15.0, 10.0)};
	constexpr Point startingPoint{50.0, 50.0, -50.0};
	constexpr Point canvasTopLeft{0.0, 0.0, 0.0};
	Canvas lightCanvas{100_column, 100_row};
	for (auto row = 0_row; row < lightCanvas.rows(); row++) {
		for (auto col = 0_column; col < lightCanvas.columns(); col++) {
			double const columnOffset = col.value;
			double const rowOffset = row.value;
			Point const canvasPoint = canvasTopLeft + Direction{columnOffset, rowOffset, 0.0};
			Ray const ray{startingPoint, normalize(canvasPoint - startingPoint)};
			auto const result = intersect(sphere, ray);
			if (!result.count) {
				lightCanvas[col, row] = lightColor;
			}
		}
	}
	std::ofstream outputFile{outputDirectory + "sphere.ppm"};
	printPPM(outputFile, lightCanvas);
	ASSERT(outputFile);
}


void testRayHitsSphereCanvasWithLighting() {
	constexpr auto canvasHeight = 1000_row;
	constexpr auto canvasWidth = 1000_column;
	constexpr Point canvasTopLeft = {-3.0, -3.0, 0.0};
	constexpr Point canvasBottomRight = {3.0, 3.0, 0.0};
	constexpr Direction canvasPixelWidth = {(canvasBottomRight.x - canvasTopLeft.x) / canvasWidth.value, 0.0, 0.0};
	constexpr Direction canvasPixelHeight = {0.0, (canvasBottomRight.y - canvasTopLeft.y) / canvasHeight.value, 0.0};
	constexpr Light lightSource{{-10.0, -10.0, -10.0}, Colors::white};
	constexpr Material sphereMaterial = [newMaterial = defaultMaterial]()mutable{newMaterial.color = {1.0, 0.2, 1.0}; return newMaterial;}();
	constexpr Shapes::Sphere sphere{Point{0.0, 0.0, 0.0}, scaling(1.0, 1.0, 1.0), sphereMaterial};
	constexpr Point startingPoint{0.0, 0.0, -5.0};
	Canvas lightCanvas{canvasWidth, canvasHeight};
	for (auto row = 0_row; row < lightCanvas.rows(); row++) {
		for (auto col = 0_column; col < lightCanvas.columns(); col++) {
			double const columnOffset = col.value;
			double const rowOffset = row.value;
			Point const canvasPoint = canvasTopLeft + columnOffset * canvasPixelWidth + rowOffset * canvasPixelHeight;
			Ray const ray{startingPoint, normalize(canvasPoint - startingPoint)};
			auto const result = intersect(sphere, ray);
			auto const firstHit = hit(result.times, result.count);
			if (firstHit) {
				auto const hitPosition = ray.position(firstHit->time);
				auto const hitSphere = std::get<Shapes::Sphere>(firstHit->object);
				auto const normal = normalAt(hitSphere, hitPosition);
				auto const eye = -ray.direction;
				auto const reflectionColor = lighting(hitSphere.material, lightSource, hitPosition, eye, normal);
				lightCanvas[col, row] = reflectionColor;
			}
		}
	}
	std::ofstream outputFile{outputDirectory + "sphereWithReflection.ppm"};
	printPPM(outputFile, lightCanvas);
	ASSERT(outputFile);
}

cute::suite make_suite_ApplicationTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testProjectileTrajectory));
	s.push_back(CUTE(testProjectileTraceOnCanvas));
	s.push_back(CUTE(testClockWithRotation));
	s.push_back(CUTE(testRayHitsSphereCanvas));
	s.push_back(CUTE(testRayHitsSphereCanvasWithLighting));
	return s;
}
