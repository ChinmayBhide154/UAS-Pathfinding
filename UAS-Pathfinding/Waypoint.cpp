#include "Waypoint.h"
#include "../submodules/WGS84toCartesian/WGS84toCartesian.hpp"
#include <array>
#include <cmath>
Waypoint::Waypoint(double xLat, double yLong, bool isGps, string name, double refLat, double refLong) : name(name) {
	if (isGps) {
		lat = xLat;
		lon = yLong;

		// Convert to Cartesian
		std::array<double, 2> GISRef{ refLat, refLong };
		std::array<double, 2> GISGiven{ xLat, yLong };
		std::array<double, 2> result{ wgs84::toCartesian(GISRef, GISGiven) };
		x = result[0];
		y = result[y];
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

