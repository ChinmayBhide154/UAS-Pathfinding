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
		uint32_t numWaypoints;

	UAS();
	double getTotalDistance();


};