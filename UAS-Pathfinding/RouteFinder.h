#pragma once
#include <vector>
#include <string>
#include "Route.h"
#include "Edge.h"
#include "Waypoint.h"
#include "../submodules/Minimum-Cost-Perfect-Matching/Matching.h"
#include "../submodules/Minimum-Cost-Perfect-Matching/Graph.h"

class RouteFinder
{
private:
	std::vector<Route*> routes;
	double** adjMatrix;
	uint32_t numNodes;
	double distToStartingRoute;
	Waypoint* startingPoint;
	double maxDist;

public:
	// Constructors
	RouteFinder(std::vector<Route*> routes, Waypoint* firstPoint, double maxDist);

	// Destructors
	~RouteFinder();

	// Functions
	std::vector<Route*> findShortestTraversal();

private:
	// non-poly time
	void minimumCost(uint32_t routeIndex, bool* visited, double* cost, std::vector<Route*>* retArr);
	uint32_t closest(uint32_t routeIndex, bool* visited, double* cost);
	// Traversal helper functions
	void primsMST(double** result, bool* chosen);
	void edmondsMST(double** result, bool* chosen);
	void getOddDegreeNodes(double** subEdges, bool* subNodes, bool* result);
	void extractSubgraph(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** result);
	void findMinWeightPerfectMatching(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** subGraph, double** result);
	void findEulerTour(bool* subNodes, double** subGraph, vector<Route*>* result);

	// Function to port to library

};