/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include <vector>
#include "Route.h"
#include "RouteFinder.h"
#include <string.h>
#include "JSON.h"
#include <fstream>
#include <stdexcept>
#include <map>
#include "../submodules/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

#define NUM_ROUTES 3
#define NUM_WAYPOINTS 4
int main()
{
    std::ifstream f("Text.json");
    json data = json::parse(f);
    std::vector<Waypoint*> listWaypoints{};
    for (uint32_t i = 0; i < NUM_WAYPOINTS; i++) {
        json waypoint = data[(std::string) ("Waypoint" + std::to_string(i))];
        listWaypoints.push_back(new Waypoint(waypoint["refLat"], waypoint["refLong"], true, std::to_string((uint32_t) waypoint["waypointId"]), 0, 0));
    }

    std::vector<Route*> listRoutes{};
    for (uint32_t i = 0; i < NUM_ROUTES; i++) {
        json route = data["Route" + std::to_string(i)];
        std::vector<Waypoint*> waypointsInRoute;
        for (auto it = route["waypointIds"].begin(); it != route["waypointIds"].end(); ++it) {
            waypointsInRoute.push_back(listWaypoints[(uint32_t) it.value()]);
        }
        listRoutes.push_back(new Route(waypointsInRoute, std::to_string((uint32_t) route["routeID"]), route["dollarValue"]));
    }


    json routeFinder = data["RouteFinder"];
    RouteFinder finder(listRoutes, listWaypoints[routeFinder["startingWaypointId"]], routeFinder["maxFlyingDistance"]);
    std::vector<Route*> result = finder.findShortestTraversal();

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


    // Temp: Print pathfinding results
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i]->name << std::endl;
    }
    std::cout << "Size: " << result.size() << std::endl;
    return 0;
}
