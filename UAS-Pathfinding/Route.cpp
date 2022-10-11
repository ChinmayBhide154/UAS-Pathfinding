#include "Route.h"

Route::Route(std::vector<Waypoint*> waypoints, std::string name, double dollarValue)
	: waypoints(waypoints), name(name), dollarValue(dollarValue) {};


/*
* double getDistance()
*	- Returns: The total distance of this route
*/
double Route::getDistance() {
	// TODO
	return 0;
}
