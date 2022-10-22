#pragma once
#include <vector>
#include <string>
#include "Waypoint.h"

class Route
{
public:
	std::vector<Waypoint*> waypoints;
	std::string name;
	double dollarValue;
	
	// Constructors
	Route();
	Route(std::vector<Waypoint*> waypoints, std::string name, double dollarValue);

	// Destructors

	// Functions
	/*
	* double getDistance()
	* - Returns: The total distance of this route
	*/
	double getDistance();
};

