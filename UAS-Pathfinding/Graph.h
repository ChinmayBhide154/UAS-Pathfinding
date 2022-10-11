#pragma once
#include <vector>
#include "Route.h"
#include "Edge.h"

class Graph
{
private:
	std::vector<Edge*> edges;
	std::vector<Route*> routes;

public:
	// Constructors
	Graph(std::vector<Edge*> edges, std::vector<Route*> routes);

	// Destructors


	// Functions
	std::vector<Route*> findShortestTraversal();

};

