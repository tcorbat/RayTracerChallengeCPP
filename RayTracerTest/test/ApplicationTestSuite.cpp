#include "ApplicationTestSuite.h"

#include "Point.h"
#include "Direction.h"
#include "Canvas.h"
#include "cute.h"

#include <vector>
#include <fstream>

struct Projectile {
	Point location;
	Direction velocity;
};

struct World {
	Direction const gravity;
	Direction const wind;
};

Projectile tick(World const & world, Projectile projectile) {
	projectile.location += projectile.velocity;
	projectile.velocity += world.gravity + world.wind;
	return projectile;
}

void testProjectileTrajectory() {
	Projectile projectile{{0.0, 1.0, 0.0}, normalize({1.0, 1.0, 0.0})};
	World const world{{0.0, -0.1, 0.0}, {-0.01, 0.0, 0.0}};

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
	Color const projectileColor{0.25, 1.0, 0};
	Point const startingPoint{0.0, 1.0, 0.0};
	Direction const projectileVelocity = normalize({1, 1.8, 0}) * 11.25;
	Projectile projectile{startingPoint, projectileVelocity};
	Direction const gravity{0.0, -0.1, 0.0};
	Direction const wind{-0.01, 0, 0};
	World const world{gravity, wind};
	Canvas traceCanvas{900_column, 550_row};
	do {
		traceCanvas[projectile.location] = projectileColor;
		projectile = tick(world, projectile);
	} while(projectile.location.y > 0.0);

	std::ofstream outputFile{"projectile.ppm"};
	printPPM(outputFile, traceCanvas);
	ASSERT(outputFile);
}

cute::suite make_suite_ApplicationTestSuite() {
	cute::suite s { };
	s.push_back(CUTE(testProjectileTrajectory));
	s.push_back(CUTE(testProjectileTraceOnCanvas));
	return s;
}
