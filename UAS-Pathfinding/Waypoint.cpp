#include "Waypoint.h"
#include "../submodules/WGS84toCartesian/WGS84toCartesian.hpp"
#include <array>
#include <cmath>
#include <vector>


Waypoint::Waypoint(){}
Waypoint::Waypoint(double xLat, double yLong, bool isGps, string name, double refLat, double refLong) : name(name) {
	if (isGps) {
		lat = xLat;
		lon = yLong;

		// Convert to Cartesian
		std::array<double, 2> GISRef{ refLat, refLong };
		std::array<double, 2> GISGiven{ xLat, yLong };
		std::array<double, 2> result{ wgs84::toCartesian(GISRef, GISGiven) };
		x = result[0];
		y = result[1];
	}
	else {
		x = xLat;
		y = yLong;

		// Convert to GIS
		std::array<double, 2> GISRef{ refLat, refLong };
		std::array<double, 2> CartGiven{ xLat, yLong };
		std::array<double, 2> result{ wgs84::fromCartesian(GISRef, CartGiven) };

		lat = result[0];
		lon = result[1];
	}
}

double Waypoint::distanceFrom(Waypoint* target) {
	return sqrt(pow(target->x - this->x, 2) + pow(target->y - this->y, 2));
}

bool Waypoint::isObstructionN(vector<Waypoint*> waypoints, Waypoint* target) {
	for (int i = 0; i < waypoints.size() - 1; i++) {
		if (isObstruction2(waypoints[i], waypoints[i + 1], target)) {
			return false;
		}
	}
	return true;
}

//isObstruciton determines if an obstacle created mid flight will cause a disruption in the Route.

bool Waypoint::isObstruction2(Waypoint* waypoint1, Waypoint* waypoint2, Waypoint* target) {
	int o1 = findOrientation(waypoint1, waypoint2, this);
	int o2 = findOrientation(waypoint1, waypoint2, target);
	int o3 = findOrientation(this, target, waypoint1);
	int o4 = findOrientation(this, target, waypoint2);

	if ((o1 != o2 && o3 != o4) || 
		(o1 == 0 && onWaypointLineSegment(waypoint1, this, waypoint2)) || 
		(o2 == 0 && onWaypointLineSegment(waypoint1, target, waypoint2)) ||
		(o3 == 0 && onWaypointLineSegment(this, waypoint1, target)) ||
		(o4 == 0 && onWaypointLineSegment(this, waypoint2, target))) return true;

	return false;
}


/*
* 
* bool Waypoint::OnWaypointLineSegment(Waypoint* waypoint1, Waypoint* waypoint2)
* Given three collinear points waypoint1, this pointer, waypoint2, the function checks if
* point this pointer lies on line segment 'waypoint1 - waypoint2'
*/

bool Waypoint::onWaypointLineSegment(Waypoint* waypoint1, Waypoint* waypoint2, Waypoint* waypoint3) {
	if (waypoint2->x <= max(waypoint1->x, waypoint3->x) && waypoint2->x >= min(waypoint1->x, waypoint3->x) && 
		waypoint2->y <= max(waypoint1->y, waypoint3->y) && waypoint2->y >= min(waypoint1->y, waypoint3->y)) {
		return true;
	}
	return false;
}

// To find orientation of ordered triplet (waypoint1, this pointer, waypoint2).
// The function returns following values
// 0 --> waypoint1, this pointer and waypoint2 are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int Waypoint::findOrientation(Waypoint* waypoint1, Waypoint* waypoint2, Waypoint* waypoint3) {
	double orientation = (waypoint2->y - waypoint1->y) * (waypoint3->x - waypoint2->x) - (waypoint2->x - waypoint1->x) * (waypoint3->y - waypoint2->y);

	if (orientation == 0) return 0; // collinear

	return (orientation > 0) ? 1 : 2; //clockwise or counter clockwise orientation
}







