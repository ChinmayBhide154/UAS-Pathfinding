#include "pch.h"
#include <C:\Users\chinm\OneDrive\Documents\UAS-PathFinding\pathfinding\UAS-Pathfinding\Waypoint.h>
#include <C:\Users\chinm\OneDrive\Documents\UAS-PathFinding\pathfinding\UAS-Pathfinding\Waypoint.cpp>

Waypoint waypointA;
Waypoint waypointB;

Waypoint waypoint1;
Waypoint waypoint2;
Waypoint waypoint3;
Waypoint waypoint4;

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

	ASSERT_EQ(606.945, int(waypointA.distanceFrom(&waypointB) * 1000) / (double) 1000);
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom2B) {
	waypointA.x = 1.6;
	waypointB.x = 345.7;
	waypointA.y = 56.7;
	waypointB.y = 556.678;

	ASSERT_EQ(606, int(waypointB.distanceFrom(&waypointA)));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom3A) {
	waypointA.x = 456.7;
	waypointB.x = 334.7;
	waypointA.y = 234.8;
	waypointB.y = 68.456;

	ASSERT_EQ(206, int(waypointA.distanceFrom(&waypointB)));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, distanceFrom3B) {
	waypointA.x = 456.7;
	waypointB.x = 334.7;
	waypointA.y = 234.8;
	waypointB.y = 68.456;

	ASSERT_EQ(206, int(waypointB.distanceFrom(&waypointA)));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment1) {
	waypoint1.x = 0; waypoint1.y = 0;
	waypoint2.x = 0; waypoint2.y = 0;
	waypoint3.x = 0; waypoint3.y = 0;

	ASSERT_EQ(true, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment2) {
	waypoint1.x = 0; waypoint1.y = 0;
	waypoint2.x = 1; waypoint2.y = 1;
	waypoint3.x = 2; waypoint3.y = 2;

	ASSERT_EQ(true, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment3) {
	waypoint1.x = 0; waypoint1.y = 0;
	waypoint2.x = 1; waypoint2.y = 1;
	waypoint3.x = 5; waypoint3.y = 5;

	ASSERT_EQ(true, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment4) {
	waypoint1.x = 0; waypoint1.y = 0;
	waypoint2.x = 100; waypoint2.y = 100;
	waypoint3.x = 2; waypoint3.y = 3;

	ASSERT_EQ(false, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment5) {
	waypoint1.x = 100; waypoint1.y = 100;
	waypoint2.x = 100; waypoint2.y = 100;
	waypoint3.x = 2; waypoint3.y = 3;

	ASSERT_EQ(true, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, onWaypointLineSegment6) {
	waypoint1.x = -1; waypoint1.y = -1;
	waypoint2.x = 0; waypoint2.y = 0;
	waypoint3.x = 5; waypoint3.y = 1;

	ASSERT_EQ(false, waypoint2.onWaypointLineSegment(&waypoint1, &waypoint2, &waypoint3));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, CheckObstructions1) {
	waypoint1.x = -1; waypoint1.y = 0;
	waypoint2.x = 1; waypoint2.y = 0;
	waypoint3.x = 0; waypoint3.y = -1;
	waypoint4.x = 0; waypoint4.y = 1;

	EXPECT_EQ(true, waypoint3.isObstruction2(&waypoint1, &waypoint2, &waypoint4));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, CheckObstructions2) {
	waypoint1.x = -1; waypoint1.y = 0;
	waypoint2.x = 1; waypoint2.y = 0;
	waypoint3.x = 1; waypoint3.y = -1;
	waypoint4.x = 2; waypoint4.y = 1;

	EXPECT_EQ(false, waypoint3.isObstruction2(&waypoint1, &waypoint2, &waypoint4));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, CheckObstructions3) {
	waypoint1.x = 0; waypoint1.y = 0;
	waypoint2.x = 5; waypoint2.y = 0;
	waypoint3.x = -5; waypoint3.y = 0;
	waypoint4.x = -1; waypoint4.y = 0;

	EXPECT_EQ(false, waypoint3.isObstruction2(&waypoint1, &waypoint2, &waypoint4));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, CheckObstructions4) {
	waypoint1.x = -1; waypoint1.y = -1;
	waypoint2.x = 1; waypoint2.y = 1;
	waypoint3.x = 2; waypoint3.y = 2;
	waypoint4.x = 3; waypoint4.y = 3;

	EXPECT_EQ(false, waypoint3.isObstruction2(&waypoint1, &waypoint2, &waypoint4));
	EXPECT_TRUE(true);
}

TEST(WaypointTests, CheckObstructions5) {
	waypoint1.x = 5.2; waypoint1.y = 6.2;
	waypoint2.x = 9.56; waypoint2.y = 10.67;
	waypoint3.x = 5.2; waypoint3.y = 7;
	waypoint4.x = 8; waypoint4.y = -1;

	EXPECT_EQ(true, waypoint3.isObstruction2(&waypoint1, &waypoint2, &waypoint4));
	EXPECT_TRUE(true);
}




