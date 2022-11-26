#include "pch.h"
#include "..\UAS-Pathfinding\Route.h"

TEST(RouteTests, projectConfigTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(RouteTests, t1) {
	Route route;
	Waypoint wp1;
	Waypoint wp2;
	Waypoint wp3;
	wp1.x = 0; wp1.y = 0;
	wp2.x = 1; wp2.y = 0;
	wp3.x = 1; wp3.y = 1;
	std::vector<Waypoint*> waypoints{ &wp1, &wp2, &wp3 };

	route = Route(waypoints, "route1", 40.2);
	
	EXPECT_EQ(2, route.getDistance());
	EXPECT_TRUE(true);
}

TEST(RouteTests, t2) {
	Route route;
	Waypoint wp1;
	Waypoint wp2;
	Waypoint wp3;
	wp1.x = 5; wp1.y = 5;
	wp2.x = 6; wp2.y = 6;
	wp3.x = 7; wp3.y = 7;
	std::vector<Waypoint*> waypoints{ &wp1, &wp2, &wp3 };

	route = Route(waypoints, "route1", 40.2);

	EXPECT_EQ(2, int(route.getDistance()));
	EXPECT_TRUE(true);
}

TEST(RouteTests, t3) {
	Route route;
	Waypoint wp1;
	Waypoint wp2;
	Waypoint wp3;
	wp1.x = -1; wp1.y = 0;
	wp2.x = 1; wp2.y = 0;
	wp3.x = 6; wp3.y = 0;
	std::vector<Waypoint*> waypoints{ &wp1, &wp2, &wp3 };

	route = Route(waypoints, "route1", 40.2);

	EXPECT_EQ(7, route.getDistance());
	EXPECT_TRUE(true);
}

TEST(RouteTests, t4) {
	Route route;
	Waypoint wp1;
	Waypoint wp2;
	Waypoint wp3;
	wp1.x = 10; wp1.y = 11;
	wp2.x = 10; wp2.y = 11;
	wp3.x = 10; wp3.y = 11;
	std::vector<Waypoint*> waypoints{ &wp1, &wp2, &wp3 };

	route = Route(waypoints, "route1", 40.2);

	EXPECT_EQ(0, int(route.getDistance()));
	EXPECT_TRUE(true);
}

TEST(RouteTests, t5) {
	Route route;
	Waypoint wp1;
	Waypoint wp2;
	Waypoint wp3;
	wp1.x = 0; wp1.y = 0;
	wp2.x = 0; wp2.y = 0;
	wp3.x = 0; wp3.y = 0;
	std::vector<Waypoint*> waypoints{ &wp1, &wp2, &wp3 };

	route = Route(waypoints, "route1", 40.2);

	EXPECT_EQ(0, int(route.getDistance()));
	EXPECT_TRUE(true);
}



