/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include <vector>
#include "Route.h"
#include "RouteFinder.h"
#include <string.h>
#include <fstream>
#include "../submodules/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
    std::cout << "program start\n";
    std::ifstream f("Text.json");
    json data = json::parse(f);

    uint32_t NUM_ROUTES = data["numRoutes"];
    uint32_t NUM_WAYPOINTS = data["numWaypoints"];
    uint32_t startPointIndex;
    std::vector<Waypoint *> listWaypoints{};
    json routeFinder = data["RouteFinder"];

    std::cout << "start reading waypoint\n";
    uint32_t startPointId = routeFinder["startingWaypointId"];
    for (uint32_t i = 0; i < NUM_WAYPOINTS; i++) {
        json waypoint = data[(std::string) ("Waypoint" + std::to_string(i))];
        if (waypoint["waypointId"] == startPointId) {
            startPointIndex = i;
        }
        listWaypoints.push_back(new Waypoint(waypoint["refLat"], waypoint["refLong"], true, std::to_string((uint32_t) waypoint["waypointId"]), 0, 0));
    }
    std::cout<<"start reading routes\n";
    std::vector<Route*> listRoutes{};
    for (uint32_t i = 0; i < NUM_ROUTES; i++) {
        json route = data["Route" + std::to_string(i)];
        std::vector<Waypoint*> waypointsInRoute;
        for (auto it = route["waypointIds"].begin(); it != route["waypointIds"].end(); ++it) {
            waypointsInRoute.push_back(listWaypoints[(uint32_t) it.value()]);
        }
        listRoutes.push_back(new Route(waypointsInRoute, std::to_string((uint32_t) route["routeID"]), route["dollarValue"]));
    }


    RouteFinder finder(listRoutes, listWaypoints[startPointIndex], routeFinder["maxFlyingDistance"]);
    std::vector<Route*> result = finder.findShortestTraversalAccurate();

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
    return 0;
}
