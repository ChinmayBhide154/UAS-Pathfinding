#include "RouteFinder.h"
#define FLOAT_MAX 	3.402823465E38
#define DOUBLE_MAX	1.7976931348623157E308

RouteFinder::RouteFinder(std::vector<Edge*> edges, std::vector<Route*> routes)
	: edges(edges), routes(routes) {};

/*
* std::vector<Route*> RouteFinder::findShortestTraversal()
*	- Returns: the optimal sequence of routes to take
*/
std::vector<Route*> RouteFinder::findShortestTraversal(Waypoint* firstPoint, double maxDist) {
	std::vector<Route*> retArr = std::vector<Route*>();

	// Find route closest to the first point, use that as first node of traversal
	double distToStartingRoute = FLOAT_MAX;
	uint32_t firstRouteIndex = 0;
	// n-time
	for (uint16_t i = 0; i < this->routes.size(); i++) {
		double distAway = this->routes[i]->waypoints[0]->distanceFrom(firstPoint);
		if (distAway < distToStartingRoute) {
			distToStartingRoute = distAway;
			firstRouteIndex = i;
		}
	}

	// Set first route to the first element of routes vector
	this->routes.insert(this->routes.begin(), this->routes[firstRouteIndex]);
	this->routes.erase(this->routes.begin()+firstRouteIndex+1);

	// Create edges
	vector<vector<double>>* ranks = new vector<vector<double>>();
	for (uint16_t i = 0; i < this->routes.size(); i++) {
		// Create subarrays
		ranks->push_back(vector<double>());
		for (uint16_t j = 0; j < this->routes.size(); j++) {
			// 0s for same edge ranks, filled to keep indexing consistent
			if (i == j) {
				(*ranks)[i].push_back(0.0);
			}
			// Calc rank
			else {
				Waypoint* endOfFirst = routes[i]->waypoints[routes[i]->waypoints.size() - 1];
				Waypoint* startOfNext = routes[j]->waypoints[0];

				// Edge weight = total_dist / $ => smaller is better
				(*ranks)[i].push_back((endOfFirst->distanceFrom(startOfNext) + routes[j]->getDistance()) / routes[j]->dollarValue);
			}
		}
	}

	// Edges: ranks
	// Nodes: [starting loc], and after that this->routes
	// https://en.wikipedia.org/wiki/Christofides_algorithm

	// TODO: Find MST via Prim's


	// TODO: Find set O of nodes with odd degree in MST. This set should have an even number of nodes.


	// TODO: Find min-weight perfect matching M from induced subgraph by nodes from O

	
	// TODO: Comedges of of M and T to form connected multigraph H (each node should have an even number degree)

	
	// TODO: Form Eulerian Circuit C in H


	// TODO: Make C a Hamiltonian circuit by skipping repeated nodes, => our sol that connects back to start


	// TODO: Get subset of routes that won't exceed travel distance, reject if < 50% routes traversed


	// TODO: Get 
	
	return retArr;
}