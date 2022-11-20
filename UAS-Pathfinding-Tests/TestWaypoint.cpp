#include "pch.h"
#include "..\UAS-Pathfinding\Waypoint.h"
#include "..\UAS-Pathfinding\Waypoint.cpp"

Waypoint waypointA;
Waypoint waypointB;

TEST(WaypointTests, projectConfigTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
TEST(WaypointTests, distanceFrom1A) {
	waypointA.x = 5;
	waypointB.x = 5;
	waypointA.y = 5;
	waypointB.y = 6;

	ASSERT_EQ (1, waypointA.distanceFrom(&waypointB));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom1B) {
	waypointA.x = 5;
	waypointB.x = 5;
	waypointA.y = 5;
	waypointB.y = 6;

	ASSERT_EQ(1, waypointB.distanceFrom(&waypointA));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom2A) {
	waypointA.x = 1.6;
	waypointB.x = 345.7;
	waypointA.y = 56.7;
	waypointB.y = 556.678;

	ASSERT_EQ(606.945, waypointA.distanceFrom(&waypointB));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom2B) {
	waypointA.x = 1.6;
	waypointB.x = 345.7;
	waypointA.y = 56.7;
	waypointB.y = 556.678;

	ASSERT_EQ(606.94547570931, waypointB.distanceFrom(&waypointA));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom3A) {
	waypointA.x = 456.7;
	waypointB.x = 334.7;
	waypointA.y = 234.8;
	waypointB.y = 68.456;

	ASSERT_EQ(206.28699992001, waypointA.distanceFrom(&waypointB));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom3B) {
	waypointA.x = 456.7;
	waypointB.x = 334.7;
	waypointA.y = 234.8;
	waypointB.y = 68.456;

	ASSERT_EQ(206.28699992001, waypointB.distanceFrom(&waypointA));
	EXPECT_TRUE(true);
}




