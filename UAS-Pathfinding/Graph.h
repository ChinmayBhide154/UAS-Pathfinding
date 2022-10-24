#pragma once
#include <vector>
#include "Route.h"
#include "Edge.h"

class Graph
{
private:
	std::vector<int*> edges;
	std::vector<Route*> routes;
	std::vector<Waypoint*> waypoints;

public:
	// Constructors

	//Graph of Routes with Rank as edges
	Graph(std::vector<int*> ranks, std::vector<Route*> routes);

	//Graph of Waypoints with Distances as edges
	Graph(std::vector<int*> distances, std::vector<Waypoint*> waypoints);


	// Functions
	Graph buildGraph();
	std::vector<Waypoint*> findShortestTraversal();
	
};

