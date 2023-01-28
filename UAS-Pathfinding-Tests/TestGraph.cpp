#include "pch.h"

#include "..\UAS-Pathfinding\Graph.cpp"

Waypoint w1;
Waypoint w2;
Waypoint w3;
Waypoint w4;
Waypoint w5;
Waypoint w6;
Waypoint w7;

TEST(GraphTests, projectConfigTest) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(GraphTests, reRouteTest) {

    w1.x = -5; w1.y = 2; w1.id = 0;
    w2.x = 1; w2.y = 1; w2.id = 1;
    w3.x = 5; w3.y = 10; w3.id = 2;
    w4.x = -1; w4.y = -2; w4.id = 3;
    w5.x = 3; w5.y = -3; w5.id = 4;
    w6.x = -3; w6.y = -6; w6.id = 5;
    w7.x = 4; w7.y = -13; w7.id = 6;

    vector<Waypoint*> waypoints = { &w1, &w2, &w3, &w4, &w5, &w6, &w7 };
    vector<Waypoint*> obstacles = { &w2, &w5, &w6, &w4, &w2 };

    Graph graph = Graph(waypoints);
    vector<vector<double>> matrix;
    matrix = graph.getGraphMatrix(obstacles, -2, 1);
    vector<int> shortestPath = {};
    //shortestPath = graph.dijkstra(matrix, 7, 0, 4);
    shortestPath = graph.reroute(3, matrix, 7, 0, 6);
    vector<int> expectedShortestPath = { 1, 3, 7 };

    EXPECT_EQ(shortestPath, expectedShortestPath);

    EXPECT_TRUE(true);
}