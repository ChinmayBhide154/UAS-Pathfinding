#include <algorithm>
#include "RouteFinder.h"

//#include "../submodules/Minimum-Cost-Perfect-Matching/Matching.h"
//#include "../submodules/Minimum-Cost-Perfect-Matching/Graph.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <iostream>

#define FLOAT_MAX 			3.402823465E38
#define DOUBLE_MAX			1.7976931348623157E308
#define UINT32_MAX  		4294967295
#define INT_DOUBLE_ACCURACY 1E12

RouteFinder::RouteFinder(std::vector<Route*> routes, Waypoint* firstPoint, double maxDist)
	: routes(routes), maxDist(maxDist) {
		// Find route closest to the first point, use that as first node of traversal
		double distToStartingRoute = FLOAT_MAX;
		this->startingPoint = firstPoint;
		uint32_t firstRouteIndex = 0;
		// n-time
		for (uint32_t i = 0; i < this->routes.size(); i++) {
			double distAway = this->routes[i]->waypoints[0]->distanceFrom(firstPoint);
			if (distAway < distToStartingRoute) {
				distToStartingRoute = distAway;
				firstRouteIndex = i;
			}
		}
		this->distToStartingRoute = distToStartingRoute;

		// Set first route to the first element of routes vector
		this->routes.insert(this->routes.begin(), this->routes[firstRouteIndex]);
		this->routes.erase(this->routes.begin()+firstRouteIndex+1);

		this->numNodes = routes.size();

		// Adjacency Matrix: https://www.programiz.com/dsa/graph-adjacency-matrix
		adjMatrix = new double*[this->numNodes];
		for (uint32_t i = 0; i < this->numNodes; i++) {
			adjMatrix[i] = new double[this->numNodes];
			for (uint32_t j = 0; j < this->numNodes; j++) {
				if (i == j) adjMatrix[i][j] = -1;
				else {
					Waypoint* endOfFirst = routes[i]->waypoints[routes[i]->waypoints.size() - 1];
					Waypoint* startOfNext = routes[j]->waypoints[0];

					double distance = endOfFirst->distanceFrom(startOfNext);
					if (distance >= this->maxDist) adjMatrix[i][j] = -1;

					// Edge weight = total_dist / $ => smaller is better
					adjMatrix[i][j] = (distance + routes[j]->getDistance()) / routes[j]->dollarValue;
					// _ASSERT(adjMatrix[i][j] >= 0);
				}
			}
		}
	};

RouteFinder::~RouteFinder() {
	for (uint32_t i = 0; i < this->numNodes; i++) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
}

/*
* std::vector<Route*> RouteFinder::findShortestTraversal()
*	- Returns: the optimal sequence of routes to take
*/
std::vector<Route*> RouteFinder::findShortestTraversal() {
	std::vector<Route*> retArr = std::vector<Route*>();


	bool* visited = new bool[this->numNodes];
	memset(visited, false, sizeof(bool) * this->numNodes);
	double cost = 0;
	minimumCost(0, visited, &cost, &retArr);
	retArr.pop_back();



	// // Edges: ranks
	// // Vertices: [starting loc], and after that this->routes
	// // https://en.wikipedia.org/wiki/Christofides_algorithm
	//
	//
	// // Initialize helper node lists and adjacency matrices
	// bool* mstNodes = new bool[this->numNodes];
	// bool* mstOddDegreeNodes = new bool[this->numNodes];
	// memset(mstNodes, false, sizeof(bool) * this->numNodes);
	// memset(mstOddDegreeNodes, false, sizeof(bool) * this->numNodes);

	// double** mstEdges = new double*[this->numNodes];
	// double** subgraphO = new double*[this->numNodes];
	// double** minWeightMatch = new double*[this->numNodes];

	// for (uint32_t i = 0; i < this->numNodes; i++) {
	// 	mstEdges[i] = new double[this->numNodes];
	// 	subgraphO[i] = new double[this->numNodes];
	// 	minWeightMatch[i] = new double[this->numNodes];
		
	// 	for (uint32_t j = 0; j < this->numNodes; j++) {
	// 		mstEdges[i][j] = -1;
	// 		subgraphO[i][j] = -1;
	// 		minWeightMatch[i][j] = -1;
	// 	}
	// }

	// // Find MST via Prim's
	// primsMST(mstEdges, mstNodes);

	// // Find set O of nodes with odd degree in MST. This set should have an even number of nodes.
	// getOddDegreeNodes(mstEdges, mstNodes, mstOddDegreeNodes);

	// // Find min-weight perfect matching M from induced subgraph by nodes from O
	// uint32_t subGraphONumNodes, subGraphONumEdges;
	// extractSubgraph(&subGraphONumEdges, &subGraphONumNodes, mstOddDegreeNodes, subgraphO);
	// _ASSERT(subGraphONumNodes % 2 == 0);		// Enforce even number of nodes
	// findMinWeightPerfectMatching(&subGraphONumNodes, &subGraphONumEdges, mstOddDegreeNodes, subgraphO, minWeightMatch);
	
	// // Combine edges of of mst and minWeightMatch to form connected multigraph (each node should have an even number degree)
	// // DEBUG: Not sure if MST and MinWeightMatch has mutually exlusive edges
	// for (uint32_t i = 0; i < this->numNodes; i++) {
	// 	for (uint32_t j = 0; j < this->numNodes; j++) {
	// 		if (i == j) {
	// 			_ASSERT(mstEdges[i][j] == -1);
	// 			_ASSERT(minWeightMatch[i][j] == -1);
	// 		}
	// 		else if (minWeightMatch[i][j] != -1) {
	// 			_ASSERT(mstEdges[i][j] == -1);
	// 			mstEdges[i][j] = minWeightMatch[i][j];
	// 		}
	// 		else if (mstEdges[i][j] != -1) {
	// 			_ASSERT(minWeightMatch[i][j] == -1);
	// 		}
	// 	}
	// }
	
	// // Form Eulerian Circuit, without repeating nodes
	// vector<Route*>* eulerTour = new vector<Route*>();
	// findEulerTour(mstNodes, mstEdges, eulerTour);		// mstEdges unsuable after this

	// TODO: Get subset of routes that won't exceed travel distance, reject if < 50% routes traversed
	// DEBUG: Must include the "first" Route stored in this->routes AND account for time to return to it at the end!

	// // Get working first, first subset probably best
	// double distance = this->distToStartingRoute;
	// uint32_t iter = 0;
	// while (distance < this->maxDist && iter < eulerTour->size()) {
	// 	// Check if we can return to start point from this
	// 	double distFromPrevRoute = 0;
	// 	double distBackToStart = (*eulerTour)[iter]->waypoints[(*eulerTour)[iter]->waypoints.size() - 1]->distanceFrom(this->startingPoint);
	// 	if (retArr.size() != 0) {
	// 		distFromPrevRoute = retArr[retArr.size() - 1]->waypoints[retArr[retArr.size() - 1]->waypoints.size() - 1]->distanceFrom((*eulerTour)[iter]->waypoints[0]);
	// 	}
	// 	if (distFromPrevRoute + distance + distBackToStart > this->maxDist) {
	// 		break;
	// 	}
	// 	distance += distFromPrevRoute + (*eulerTour)[iter]->getDistance();
	// 	retArr.push_back((*eulerTour)[iter]);
	// 	iter++;
	// }

	// // Stretch TODO: Get route with greatest value out of the subset


	// // Delete created vectors in heap. only deletes the vectors, not the edges/nodes in it
	// for (uint32_t i = 0; i < this->numNodes; i++) {
	// 	delete[] mstEdges[i];
	// 	delete[] subgraphO[i];
	// 	delete[] minWeightMatch[i];
	// }
	// delete[] mstEdges;
	// delete[] subgraphO;
	// delete[] minWeightMatch;

	// delete[] mstNodes;
	// delete[] mstOddDegreeNodes;

	// delete eulerTour;
	
	return retArr;
}

// Dynamic Programming TSP (non-poly time) Helper
void RouteFinder::minimumCost(uint32_t routeIndex, bool* visited, double* cost, std::vector<Route*>* retArr) {
	uint32_t nIndex;
	visited[routeIndex] = true;
	retArr->push_back(this->routes[routeIndex]);
	nIndex = closest(routeIndex, visited, cost);

	if (nIndex == UINT32_MAX) {
		nIndex = 0;
		retArr->push_back(this->routes[nIndex]);
		*cost += this->adjMatrix[routeIndex][nIndex];
		return;
	}

	minimumCost(nIndex, visited, cost, retArr);
}

// Dynamic Programming TSP (non-poly time) Second Helper
uint32_t RouteFinder::closest(uint32_t routeIndex, bool* visited, double* cost) {
	double minimum = DOUBLE_MAX;
	double nc = UINT32_MAX;
	double kmin;
	
	for (uint32_t i = 0; i < this->numNodes; i++) {
		if (this->adjMatrix[routeIndex][i] != -1 && !visited[i]) {
			if (this->adjMatrix[routeIndex][i] + this->adjMatrix[i][routeIndex] < minimum) {
				minimum = this->adjMatrix[i][0] + this->adjMatrix[routeIndex][i];
				kmin = this->adjMatrix[routeIndex][i];
				nc = i;
			}
		}
	}

	if (minimum != DOUBLE_MAX) {
		*cost += kmin;
	}
	return nc;
}

// Algorithm: https://www.programiz.com/dsa/prim-algorithm
// NOTE: Prims wont work for directed graphs, which is what we have
// Switch to Edmond's Algorithm
//void RouteFinder::primsMST(double** result, bool* chosen) {
//	uint32_t numEdges = 0;
//	chosen[0] = true;
//	uint32_t nodeInd0, nodeInd1;
//
//	while (numEdges < this->numNodes - 1) {
//		double min = DOUBLE_MAX;
//		nodeInd0 = 0;
//		nodeInd1 = 0;
//
//		for (uint32_t i = 0; i < this->numNodes; i++) {
//			if (chosen[i]) {
//				for (uint32_t j = 0; j < this->numNodes; j++) {
//					if (!chosen[j] && this->adjMatrix[i][j] != -1) {
//						_ASSERT(i != j);
//						if (this->adjMatrix[i][j] < min) {
//							min = this->adjMatrix[i][j];
//							nodeInd0 = i;
//							nodeInd1 = j;
//						}
//					}
//				}
//			}
//		}
//		result[nodeInd0][nodeInd1] = adjMatrix[nodeInd0][nodeInd1];
//		result[nodeInd1][nodeInd0] = adjMatrix[nodeInd0][nodeInd1];
//		chosen[nodeInd1] = true;
//		numEdges++;
//	}
//}



//void RouteFinder::getOddDegreeNodes(double** subEdges, bool* subNodes, bool* result) {
//	uint32_t count;
//	for (uint32_t i = 0; i < this->numNodes; i++) {
//		if (subNodes[i]) {
//			count = 0;
//			for (uint32_t j = 0; j < this->numNodes; j++) {
//				if (subEdges[i][j] != -1) {
//					count++;
//				}
//			}
//			if (count % 2 == 1) result[i] = true;
//		}
//	}
//}
//
//void RouteFinder::extractSubgraph(uint32_t* numEdges, uint32_t* numNodes, bool* subNodes, double** result) {
//	*numEdges = 0;
//	*numNodes = 0;
//	for (uint32_t i = 0; i < this->numNodes; i++) {
//		if (subNodes[i]) {
//			for (uint32_t j = 0; j < this->numNodes; j++) {
//				if (subNodes[j] && adjMatrix[i][j] != -1) {
//					result[i][j] = adjMatrix[i][j];
//					(*numEdges)++;
//				}
//			}
//			(*numNodes)++;
//		}
//	}
//}

// This algorithm is too big brain for me to comprehend
// Just gonna port it to use this library: https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching
//void RouteFinder::findMinWeightPerfectMatching(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** subGraph, double** result) {
//	Graph G(this->numNodes);
//	vector<double> cost(*numEdges);
//	for (uint32_t i = 0; i < this->numNodes; i++) {
//		if (subNodes[i]) {
//			for (uint32_t j = 0; j < this->numNodes; j++) {
//				if (subGraph[i][j] != -1) {
//					G.AddEdge(i, j);
//					uint64_t tmp = G.GetEdgeIndex(i, j);
//					cost[G.GetEdgeIndex(i, j)] = (int)(subGraph[i][j] * INT_DOUBLE_ACCURACY);		// This library processes ints, multiply for fixed accuracy increase
//				}
//			}
//		}
//	}
//	
//	Matching M(G);
//	try {
//		pair<list<int>, double> solution = M.SolveMinimumCostPerfectMatching(cost);
//		for (list<int>::iterator it = solution.first.begin(); it != solution.first.end(); it++) {
//			pair<int, int> e = G.GetEdge(*it);
//			result[e.first][e.second] = (double)G.GetEdgeIndex(e.first, e.second) / (double)INT_DOUBLE_ACCURACY;
//			result[e.second][e.first] = (double)G.GetEdgeIndex(e.first, e.second) / (double)INT_DOUBLE_ACCURACY;
//		}
//	}
//	catch (...) {
//		// Perfect matching not found, graph probably too small for matching
//		for (uint32_t i = 0; i < this->numNodes; i++) {
//			for (uint32_t j = 0; j < this->numNodes; j++) {
//				if (subGraph[i][j] != -1)
//					result[i][j] = subGraph[i][j];
//			}
//		}
//	}
//	
//}

// Algorithm: https://cp-algorithms.com/graph/euler_path.html#algorithm
// DEBUG: Mutates subgraph
//void RouteFinder::findEulerTour(bool* subNodes, double** subGraph, vector<Route*>* result) {
//	bool* addedToTour = new bool[this->numNodes];
//	memset(addedToTour, false, sizeof(bool) * this->numNodes);
//	std::stack<uint32_t> nodeStack;
//	nodeStack.push(0);		// We must start at index 0, it is the starting waypoint
//	result->push_back(this->routes[0]);
//
//	uint32_t degreeCount, currIndex;
//	while (!nodeStack.empty()) {
//		degreeCount = 0;
//		currIndex = nodeStack.top();
//		for (uint32_t i = 0; i < this->numNodes; i++) {
//			if (subGraph[currIndex][i] != -1 && !addedToTour[i]) {
//				degreeCount++;
//
//				// Remove edge from subgraph
//				subGraph[currIndex][i] = -1;
//				subGraph[i][currIndex] = -1;
//				nodeStack.push(i);
//			} 
//		}
//		
//		if (degreeCount == 0) {
//			if (!addedToTour[currIndex]) {
//				if (currIndex != 0) result->push_back(this->routes[currIndex]);
//				addedToTour[currIndex] = true;
//			}
//			nodeStack.pop();
//		}
//	}
//	
//	delete[] addedToTour;
//}

