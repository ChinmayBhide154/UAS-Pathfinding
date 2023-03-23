#include "UAS.h"

UAS::UAS(double speed, double altitude, double climbRate, std::vector<Route*> routesToCover, double distanceBuffer) : speed(speed), altitude(altitude), climbRate(climbRate), routesToCover(routesToCover), distanceBuffer(distanceBuffer){
	this->flightTime = (this->speed * 0.8) - (1.1 * this->altitude / this->climbRate) - (0.1 * this->getHorizontalDistance() / 16) - this->numWaypoints * (this->altitude / this->climbRate);
}

double UAS::getHorizontalDistance() {
	double totalHorizontalDistance = 0;
	for (auto route : routesToCover) {
		totalHorizontalDistance += route->getDistance();
	}
	return totalHorizontalDistance;
}

double UAS::getTotalDistance() {
	return (this->speed * this->flightTime) - distanceBuffer;
}