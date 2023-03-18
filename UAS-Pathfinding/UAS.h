#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class UAS 
{
	public:
		double speed;
		double flightTime;
		double altitude;
		double climbRate;
		double horizontalDistance;
		uint32_t numWaypoints;

		UAS();
		UAS(double speed, double altitude, double climbRate, double horizontalDistance);
		double getTotalDistance();


};