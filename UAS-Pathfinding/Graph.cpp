#include "Graph.h"

Graph::Graph(std::vector<int*> distances, std::vector<Waypoint*> waypoints) {
	distances = distances;
	waypoints = waypoints;
}

/*
* std::vector<Route*> Graph::findShortestTraversal()
*	- Returns: the optimal sequence of routes to take
*/
std::vector<Waypoint*> Graph::findShortestTraversal() {
	// TODO
	std::vector<Waypoint*> shortestTraversal = std::vector<Waypoint*>();
	return shortestTraversal;
}