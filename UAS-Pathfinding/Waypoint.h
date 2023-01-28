#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Waypoint
{
	//Properties
	public:
		double x;
		double y;
		double lat;
		double lon;
		string name;
		int id;

	//Constructors
	Waypoint();
	Waypoint(double xLat, double yLong, bool isGps, string name, double refLat, double refLong, int id);

	//Functions
	double distanceFrom(Waypoint* target);
	bool isObstructionN(vector<Waypoint*> waypoints, Waypoint* target, bool targetIsObstructor, bool currentIsObstructor, Waypoint* currentWaypoint);
	
private:
	bool isObstruction2(Waypoint* p1, Waypoint* p2, Waypoint* target);
	bool onWaypointLineSegment(Waypoint* waypoint1, Waypoint* waypoint2, Waypoint* waypoint3);
	int findOrientation(Waypoint* waypoint1, Waypoint* waypoint2, Waypoint* waypoint3);
	bool doIntersect(Waypoint* target, Waypoint* waypoint1, Waypoint* waypoint2);
	bool waypointsConnectedByBoundary(Waypoint* waypoint1, Waypoint* waypoint2, vector<Waypoint*> obstacles);
};

