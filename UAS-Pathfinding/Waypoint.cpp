#include "Waypoint.h"
#include <cmath>
double Waypoint::distanceFrom(Waypoint* target) {
	return sqrt(pow(target->x - this->x, 2) + pow(target->y - this->y, 2));
}

