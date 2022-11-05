#include <algorithm>
#include "RouteFinder.h"

#include "../submodules/Minimum-Cost-Perfect-Matching/Matching.h"
#include "../submodules/Minimum-Cost-Perfect-Matching/Graph.h"
#include <cstdlib>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>

#define FLOAT_MAX 			3.402823465E38
#define DOUBLE_MAX			1.7976931348623157E308
#define UINT32_MAX  		4294967295
#define INT_DOUBLE_ACCURACY 1E12

RouteFinder::RouteFinder(std::vector<Route*> routes, Waypoint* firstPoint)
	: routes(routes) {
		// Find route closest to the first point, use that as first node of traversal
		double distToStartingRoute = FLOAT_MAX;
		uint32_t firstRouteIndex = 0;
		// n-time
		for (uint32_t i = 0; i < this->routes.size(); i++) {
			double distAway = this->routes[i]->waypoints[0]->distanceFrom(firstPoint);
			if (distAway < distToStartingRoute) {
				distToStartingRoute = distAway;
				firstRouteIndex = i;
			}
		}

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

					// Edge weight = total_dist / $ => smaller is better
					adjMatrix[i][j] = (endOfFirst->distanceFrom(startOfNext) + routes[j]->getDistance()) / routes[j]->dollarValue;
					_ASSERT(adjMatrix[i][j] >= 0);
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
std::vector<Route*> RouteFinder::findShortestTraversal(double maxDist) {
	std::vector<Route*> retArr = std::vector<Route*>();

	// Edges: ranks
	// Vertices: [starting loc], and after that this->routes
	// https://en.wikipedia.org/wiki/Christofides_algorithm

	// Initialize helper node lists and adjacency matrices
	bool* mstNodes = new bool[this->numNodes];
	bool* mstOddDegreeNodes = new bool[this->numNodes];
	memset(mstNodes, false, sizeof(bool) * this->numNodes);
	memset(mstOddDegreeNodes, false, sizeof(bool) * this->numNodes);

	double** mstEdges = new double*[this->numNodes];
	double** subgraphO = new double*[this->numNodes];
	double** minWeightMatch = new double*[this->numNodes];

	for (uint32_t i = 0; i < this->numNodes; i++) {
		mstEdges[i] = new double[this->numNodes];
		subgraphO[i] = new double[this->numNodes];
		minWeightMatch[i] = new double[this->numNodes];
		
		// Init values to -1
		memset(mstEdges[i], -1, sizeof(double) * this->numNodes);
		memset(subgraphO[i], -1, sizeof(double) * this->numNodes);
		memset(minWeightMatch[i], -1, sizeof(double) * this->numNodes);
	}

	// Find MST via Prim's
	primsMST(mstEdges, mstNodes);

	// Find set O of nodes with odd degree in MST. This set should have an even number of nodes.
	getOddDegreeNodes(mstEdges, mstNodes, mstOddDegreeNodes);

	// Find min-weight perfect matching M from induced subgraph by nodes from O
	uint32_t subGraphONumNodes, subGraphONumEdges;
	extractSubgraph(&subGraphONumNodes, &subGraphONumEdges, mstOddDegreeNodes, subgraphO);
	_ASSERT(subGraphONumNodes % 2 == 0);		// Enforce even number of nodes
	findMinWeightPerfectMatching(&subGraphONumNodes, &subGraphONumEdges, mstOddDegreeNodes, subgraphO, minWeightMatch);
	
	// Combine edges of of mst and minWeightMatch to form connected multigraph (each node should have an even number degree)
	// DEBUG: Not sure if MST and MinWeightMatch has mutually exlusive edges
	for (uint32_t i = 0; i < this->numNodes; i++) {
		for (uint32_t j = 0; j < this->numNodes; j++) {
			if (i == j) {
				_ASSERT(mstEdges[i][j] == -1);
				_ASSERT(minWeightMatch[i][j] == -1);
			}
			else if (minWeightMatch[i][j] != -1) {
				_ASSERT(mstEdges[i][j] == -1);		// DEBUG: Remove this if necessary
				mstEdges[i][j] = minWeightMatch[i][j];
			}
			else if (mstEdges[i][j] != -1) {
				_ASSERT(minWeightMatch[i][j] == -1);
			}
		}
	}
	
	// Form Eulerian Circuit, without repeating nodes
	vector<Route*>* eulerTour = new vector<Route*>();
	findEulerTour(mstNodes, mstEdges, eulerTour);		// mstEdges unsuable after this

	// TODO: Get subset of routes that won't exceed travel distance, reject if < 50% routes traversed
	// DEBUG: Must include the "first" Route stored in this->routes AND account for time to return to it at the end!
	

	// TODO: Get route with greatest value out of the subset


	// Delete created vectors in heap. only deletes the vectors, not the edges/nodes in it
	for (uint32_t i = 0; i < this->numNodes; i++) {
		delete[] mstEdges[i];
		delete[] subgraphO[i];
		delete[] minWeightMatch[i];
	}
	delete[] mstEdges;
	delete[] subgraphO;
	delete[] minWeightMatch;

	delete[] mstNodes;
	delete[] mstOddDegreeNodes;

	delete eulerTour;
	
	return retArr;
}

// Algorithm: https://www.programiz.com/dsa/prim-algorithm
void RouteFinder::primsMST(double** result, bool* chosen) {
	uint32_t numEdges = 0;
	chosen[0] = true;
	uint32_t nodeInd0, nodeInd1;

	while (numEdges < this->numNodes - 1) {
		double min = DOUBLE_MAX;
		nodeInd0 = 0;
		nodeInd1 = 0;

		for (uint32_t i = 0; i < this->numNodes; i++) {
			if (chosen[i]) {
				for (uint32_t j = 0; j < this->numNodes; j++) {
					if (!chosen[j] && this->adjMatrix[i][j] != -1) {
						_ASSERT(i != j);
						if (this->adjMatrix[i][j] < min) {
							min = this->adjMatrix[i][j];
							nodeInd0 = i;
							nodeInd1 = j;
						}
					}
				}
			}
		}
		result[nodeInd0][nodeInd1] = adjMatrix[nodeInd0][nodeInd1];
		result[nodeInd1][nodeInd0] = adjMatrix[nodeInd0][nodeInd1];
		chosen[nodeInd1] = true;
		numEdges++;
	}
}

void RouteFinder::getOddDegreeNodes(double** subEdges, bool* subNodes, bool* result) {
	uint32_t count;
	for (uint32_t i = 0; i < this->numNodes; i++) {
		if (subNodes[i]) {
			count = 0;
			for (uint32_t j = 0; j < this->numNodes; j++) {
				if (subEdges[i][j] != -1) {
					count++;
				}
			}
			if (count % 2 == 1) result[i] = true;
		}
	}
}

void RouteFinder::extractSubgraph(uint32_t* numEdges, uint32_t* numNodes, bool* subNodes, double** result) {
	*numEdges = 0;
	*numNodes = 0;
	for (uint32_t i = 0; i < this->numNodes; i++) {
		if (subNodes[i]) {
			for (uint32_t j = 0; j < this->numNodes; j++) {
				if (subNodes[j] && adjMatrix[i][j] != -1) {
					result[i][j] = adjMatrix[i][j];
					(*numEdges)++;
				}
			}
			(*numNodes)++;
		}
	}
}

// This algorithm is too big brain for me to comprehend
// Just gonna port it to use this library: https://github.com/dilsonpereira/Minimum-Cost-Perfect-Matching
void RouteFinder::findMinWeightPerfectMatching(uint32_t* numNodes, uint32_t* numEdges, bool* subNodes, double** subGraph, double** result) {
	Graph G(*numNodes);
	vector<double> cost(*numEdges);
	for (uint32_t i = 0; i < this->numNodes; i++) {
		if (subNodes[i]) {
			for (uint32_t j = 0; j < this->numNodes; j++) {
				if (subGraph[i][j] != -1) {
					G.AddEdge(i, j);
					cost[G.GetEdgeIndex(i, j)] = (int)(subGraph[i][j] * INT_DOUBLE_ACCURACY);		// This library processes ints, multiply for fixed accuracy increase
				}
			}
		}
	}
	
	Matching M(G);
	pair<list<int>, double> solution = M.SolveMinimumCostPerfectMatching(cost);
	for (list<int>::iterator it = solution.first.begin(); it != solution.first.end(); it++) {
		pair<int, int> e = G.GetEdge(*it);
		result[e.first][e.second] = (double) G.GetEdgeIndex(e.first, e.second) / (double) INT_DOUBLE_ACCURACY;
		result[e.second][e.first] = (double) G.GetEdgeIndex(e.first, e.second) / (double) INT_DOUBLE_ACCURACY;
	}
}

// Algorithm: https://cp-algorithms.com/graph/euler_path.html#algorithm
// DEBUG: Destroys subgraph
void RouteFinder::findEulerTour(bool* subNodes, double** subGraph, vector<Route*>* result) {
	bool* addedToTour = new bool[this->numNodes];
	memset(addedToTour, false, sizeof(bool) * this->numNodes);
	std::stack<uint32_t> nodeStack;
	nodeStack.push(0);		// We must start at index 0, it is the starting waypoint
	result->push_back(this->routes[0]);

	uint32_t degreeCount, currIndex;
	while (!nodeStack.empty()) {
		degreeCount = 0;
		currIndex = nodeStack.top();
		for (uint32_t i = 0; i < this->numNodes; i++) {
			if (subGraph[currIndex][i] != -1) {
				degreeCount++;

				// Remove edge from subgraph
				subGraph[currIndex][i] = -1;
				subGraph[i][currIndex] = -1;
				nodeStack.push(i);
			} 
		}
		
		if (degreeCount == 0) {
			if (!addedToTour[currIndex]) {
				result->push_back(this->routes[currIndex]);
				addedToTour[currIndex] = true;
			}
		}
	}
	
	delete[] addedToTour;
}

