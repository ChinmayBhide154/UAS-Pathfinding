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

		Graph(std::vector<Waypoint*> waypoints); 
		vector<vector<double>> getGraphMatrix(vector<Waypoint*> obstacles, Waypoint* target);
		void dijkstra(int n, int startnode, vector<Waypoint*> obstacles, Waypoint* target);
};



