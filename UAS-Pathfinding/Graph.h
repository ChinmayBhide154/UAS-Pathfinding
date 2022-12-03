using namespace std;
#include <vector>
#include "Waypoint.h"
#include "Route.h"
#include "Edge.h"
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <stdio.h>
#include <math.h>
#define INFINITY 9999
#define max 5


class Graph {
	public:
		//std::vector<Waypoint*> waypoints;
		//Waypoint* destination;
		vector<Waypoint*> waypoints;
		vector<Waypoint*> obstacles;
		Waypoint* target;
		Waypoint* startnode;
		int destinationNode;
		Graph();
		Graph(std::vector<Waypoint*> waypoints); 
		vector<vector<double>> getGraphMatrix(vector<Waypoint*> obstacles, Waypoint* target);
		vector<int> reroute(int continueOn, vector<vector<int>> G, int n, int startnode, int destinationNode);
		vector<int> dijkstra(vector<vector<int>> G, int n, int startnode, int destinationNode);
};



