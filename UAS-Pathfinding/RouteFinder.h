#pragma once
#include <vector>
#include "Route.h"
#include "Edge.h"

class RouteFinder
{
private:
	std::vector<Route*> routes;
	double** adjMatrix;
	uint32_t numNodes;

public:
	// Constructors
	RouteFinder(std::vector<Route*> routes, Waypoint* firstPoint);

	// Destructors
	~RouteFinder();

	// Functions
	std::vector<Route*> findShortestTraversal(double maxDist);

private:
	// Traversal helper functions
	void primsMST(double** result, bool* chosen);
	void getOddDegreeNodes(double** subEdges, bool* subNodes, bool* result);
	void extractSubgraph(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** result);
	void findMinWeightPerfectMatching(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** subGraph, double** result);
	void findEulerTour(bool* subNodes, double** subGraph, vector<Route*>* result);

	// Function to port to library

};