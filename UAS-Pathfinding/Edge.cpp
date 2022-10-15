#include "Edge.h"

Edge::Edge(Route route0, Route route1) 
	: route0(route0), route1(route1) {
	/*
	* "Rank" is a measure of how good route1 is, after finishing route0.
	* Lower rank is better.
	* Rank is calculated as (total distance / dollar value), total distance being distance of route0[end] to route1[start] + route1 length
	*/
	std::vector<Waypoint*> route0points = route0.waypoints;
	std::vector<Waypoint*> route1points = route1.waypoints;

	double rankDistance = route0points[route0.waypoints.size() - 1]->distanceFrom(route1points[0]) + this->route1.getDistance();

	this->rank = rankDistance / route1.dollarValue;
};