/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include <vector>
#include "Route.h"
#include "RouteFinder.h"
#include <string.h>
#include <fstream>
#include "UAS.h"
#include "../submodules/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

#include "Waypoint.h"
#include "RouteRerouter.h"


std::vector<Waypoint*> extractWaypointsFromIds(std::vector<int> ids, std::vector<Waypoint*> waypoints) {
    std::vector<Waypoint*> retList = {};

    for (int id : ids) {
        for (Waypoint* waypoint : waypoints) {
            if (waypoint->id == id) {
                retList.push_back(waypoint);
            }
        }
    }
    return retList;
}


int main()
{
    bool isMidFlight = true;

    std::cout << "program start\n";
    std::ifstream f("Text.json");
    json data = json::parse(f);

    uint32_t NUM_ROUTES = data["numRoutes"];
    uint32_t NUM_WAYPOINTS = data["numWaypoints"];
    uint32_t startPointIndex;

    std::vector<Waypoint*> listWaypoints{};
    json routeFinder = data["RouteFinder"];

    double uasSpeed = routeFinder["speed"];
    double uasAltitude = routeFinder["altitude"];
    double uasClimbRate = routeFinder["climbRate"];
    //double maxFlyingDistance = routeFinder["maxFlyingDistance"];

    std::cout << "start reading waypoint\n";
    uint32_t startPointId = routeFinder["startingWaypointId"];

    //UAS uas(uasSpeed, uasAltitude, uasClimbRate, 4.6);

    json waypoints = data["waypoints"];
    for (uint32_t i = 0; i < NUM_WAYPOINTS; i++) {
        //json waypoint = data[(std::string) ("Waypoint" + std::to_string(i))];
        json waypoint = waypoints[i];
        if (waypoint["id"] == startPointId) {
            startPointIndex = i;
        }
        listWaypoints.push_back(new Waypoint(waypoint["latitude"], waypoint["longitude"], true, std::to_string((uint32_t)waypoint["id"]), 0, 0, waypoint["id"]));
    }

    if (!isMidFlight) {

        
        std::cout << "start reading routes\n";
        std::vector<Route*> listRoutes{};
        json routes = data["routes"];
        for (uint32_t i = 0; i < NUM_ROUTES; i++) {
            json route = routes[i];
            std::vector<Waypoint*> waypointsInRoute;
            for (auto it = route["waypointIds"].begin(); it != route["waypointIds"].end(); ++it) {
                waypointsInRoute.push_back(listWaypoints[(uint32_t)it.value()]);
            }
            listRoutes.push_back(new Route(waypointsInRoute, std::to_string((uint32_t)route["routeID"]), route["dollarValue"]));
        }
        
        UAS uas(uasSpeed, uasAltitude, uasClimbRate, listRoutes, 4.6);
        double maxFlyingDistance = uas.getTotalDistance();

        std::vector<Route*> result;
        if (NUM_ROUTES < 19) {
            RouteFinder finder(listRoutes, listWaypoints[startPointIndex], maxFlyingDistance, false);
            result = finder.findShortestTraversalAccurate();
        }
        else {
            RouteFinder finder(listRoutes, listWaypoints[startPointIndex], maxFlyingDistance, true);
            result = finder.findShortestTraversal();
        }

        //serialize
        std::vector<int> routeIDs = {};

        for (int i = 0; i < result.size(); i++) {
            routeIDs.push_back(std::stoi(result[i]->name));
        }

        json serializeRouteFinder = {
            {"Routes", routeIDs}
        };

        std::ofstream output("output.json");
        output << serializeRouteFinder;

        output.close();


        // Temp: Print pathfinding results
        for (int i = 0; i < result.size(); i++) {
            std::cout << result[i]->name << std::endl;
        }
        std::cout << "Size: " << result.size() << std::endl;

        // Free memory
        for (uint32_t i = 0; i < NUM_ROUTES; i++) {
            delete (Route*)listRoutes.back();
            listRoutes.pop_back();

        }
        for (uint32_t i = 0; i < NUM_WAYPOINTS; i++) {
            delete listWaypoints.back();
            listWaypoints.pop_back();
        }
    }
    else {

        /*
            Rerouter:
        */

        //JSON parsing for Rerouter module:
        json reRouter = data["ReRouter"];

        double currentLong = reRouter["currentLong"];
        double currentLat = reRouter["currentLat"];
        int intermediateWaypoint = reRouter["reRouteWaypointId"];
        int destinationWaypointId = reRouter["reRouteWaypointId"];

        //Logic

        RouteRerouter routeReRouter(listWaypoints);
        cout << listWaypoints.size() << endl;
        Waypoint* currentLocation = new Waypoint(0, 0, false, "currentLocation", currentLat, currentLong, 100);
        listWaypoints.push_back(currentLocation);
        std::vector<std::vector<double>> matrix;
        std::vector<int> waypointObstacleIds = {};
        std::vector<Waypoint*> waypointObstacles = {};
        vector<int> shortestPath = {};


        for (auto it = reRouter["waypointObstacleIds"].begin(); it != reRouter["waypointObstacleIds"].end(); ++it) {
            waypointObstacleIds.push_back(it.value());
        }

        waypointObstacles = extractWaypointsFromIds(waypointObstacleIds, listWaypoints);

        matrix = routeReRouter.getGraphMatrix(waypointObstacles, currentLocation->x, currentLocation->y);
        shortestPath = routeReRouter.reroute(intermediateWaypoint, matrix, NUM_WAYPOINTS, currentLocation->id, destinationWaypointId);

        for (int i = 0; i < shortestPath.size(); i++)
            std::cout << shortestPath.at(i) << ' ';
    }
    return 0;
}
