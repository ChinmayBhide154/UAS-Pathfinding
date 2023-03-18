#include "UAS.h"

UAS::UAS(double speed, double altitude, double climbRate, double horizontalDistance) : speed(speed), altitude(altitude), climbRate(climbRate), horizontalDistance(horizontalDistance){
	this->flightTime = (this->speed * 0.8) - (1.1 * this->altitude / this->climbRate) - (0.1 * horizontalDistance / 16) - this->numWaypoints * (this->altitude / this->climbRate);
}

double UAS::getTotalDistance() {
	return this->speed * this->flightTime;
}