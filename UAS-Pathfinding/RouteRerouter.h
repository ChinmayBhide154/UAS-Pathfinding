using namespace std;
#include <vector>
#include <algorithm>
#include "Waypoint.h"
#include "Route.h"
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <stdio.h>
#include <math.h>
#define INFINITY 9999
#define max 8


class RouteRerouter {

	private:
		vector<Waypoint*> waypoints;

	public:
		//constructors
		RouteRerouter();
		RouteRerouter(std::vector<Waypoint*> waypoints); 

		//functions
		vector<vector<double>> getGraphMatrix(vector<Waypoint*> obstacles, double currentX, double currentY);
		vector<int> reroute(int continueOn, vector<vector<double>> G, int n, int startnode, int destinationNode);
		vector<int> dijkstra(vector<vector<double>> G, int n, int startnode, int destinationNode);
};



