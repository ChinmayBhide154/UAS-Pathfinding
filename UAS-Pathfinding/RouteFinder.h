#pragma once
#include <vector>
#include "Route.h"
#include "Edge.h"

class RouteFinder
{
private:
	std::vector<Edge*> edges;
	std::vector<Route*> routes;

public:
	// Constructors
	RouteFinder(std::vector<Edge*> edges, std::vector<Route*> routes);

	// Destructors


	// Functions
	std::vector<Route*> findShortestTraversal(Waypoint* firstPoint, double maxDist);
	// void graphRecursionHelper(vector<vector<double>>* memoizedRankCalc, vector<vector<double>>* memoizedDistTravelled, vector<vector<uint32_t>>* memoizedTravelledRoutes, vector<vector<double>>* ranks);


private:
	// Graph variables
	vector<int> oddNodes;


	// Traversal functions
	void findMST();
};