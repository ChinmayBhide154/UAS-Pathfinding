#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Route.h"

using namespace std;

class UAS 
{
	public:
		double speed;
		double flightTime;
		double altitude;
		double climbRate;
		double horizontalDistance;
		std::vector<Route*> routesToCover;
		uint32_t numWaypoints;
		double distanceBuffer;

		UAS();
		UAS(double speed, double altitude, double climbRate, std::vector<Route*> routesToCover, double distanceBuffer);
		double getHorizontalDistance();
		double getTotalDistance();


};