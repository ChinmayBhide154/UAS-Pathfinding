#include "Route.h"

Route::Route(std::vector<Waypoint*> waypoints, std::string name, double dollarValue)
	: waypoints(waypoints), name(name), dollarValue(dollarValue) {};


/*
* double getDistance()
*	- Returns: The total distance of this route
*/
double Route::getDistance() {
	double totalDist = 0;
	for (uint16_t i = 0; i < this->waypoints.size() - 1; i++) {
		totalDist += waypoints[i]->distanceFrom(waypoints[i + 1]);
	}
	return totalDist;
}
