#pragma once
#include <string>
#include <iostream>

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

	//Constructors
	Waypoint();
	Waypoint(double xLat, double yLong, bool isGps, string name, double refLat, double refLong);

	//Functions
	double distanceFrom(Waypoint* target);
};

