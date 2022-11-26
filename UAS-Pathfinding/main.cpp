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
    std::vector<std::vector<json>> waypointData = {};
    std::vector<std::vector<json>> routeData = {};
    std::vector <json> routefinderData = {};
    std::string waypointNumber = "";
    std::string routeNumber = "";
    
    
    // for (int i = 0; i < 4; i++) {
    //     waypointNumber = std::to_string(i);
    //     json waypoint = data.at("Waypoint" + waypointNumber);
    //     waypointData.push_back({ waypoint.at("refLat"), waypoint.at("refLong"), waypoint.at("waypointId")});
    // }

    // for (int i = 0; i < 3; i++) {
    //     routeNumber = std::to_string(i);
    //     json route = data.at("Route" + routeNumber);
    //     routeData.push_back({ route.at("waypointIds"), route.at("routeID"), route.at("dollarValue")});
    // }
    
    
    json routeFinder = data.at("RouteFinder");
    routefinderData.push_back(routeFinder.at("routeIds"));
    routefinderData.push_back(routeFinder.at("maxFlyingDistance"));
    routefinderData.push_back(routeFinder.at("startingWaypointId"));

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

    RouteFinder finder(listRoutes, listWaypoints[routeFinder["startingWaypointId"]], routeFinder["maxFlyingDistance"]);
    std::vector<Route*> result = finder.findShortestTraversal();

    // Temp: Print pathfinding results
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i]->name << std::endl;
    }
    std::cout << "Size: " << result.size() << std::endl;
    return 0;
}
