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
int main()
{
    Waypoint waypoint1;
    Waypoint waypoint2;
    waypoint1.x = 5;
    waypoint1.y = 5;
    waypoint2.x = 5;
    waypoint2.y = 5;


    // RouteFinder example usage
    Waypoint wp0 = Waypoint::Waypoint(0, 10, false, "wp0", 49.269309, -123.242703);
    Waypoint wp1 = Waypoint::Waypoint(10, 10, false, "wp1", 49.269309, -123.242703);
    Waypoint wp2 = Waypoint::Waypoint(10, 0, false, "wp2", 49.269309, -123.242703);
    Waypoint wp3 = Waypoint::Waypoint(0, 0, false, "wp3", 49.269309, -123.242703);
    Waypoint wp4 = Waypoint::Waypoint(5, 5, false, "wp4", 49.269309, -123.242703);
    Waypoint wp10 = Waypoint::Waypoint(0, 20, false, "wp0", 49.269309, -123.242703);

    std::vector<Waypoint*> test0{ &wp4, &wp2, &wp3 };
    Route r0 = Route::Route(test0, "r0", 200.0);
    std::vector<Waypoint*> test1{ &wp3, &wp2 };
    Route r1 = Route::Route(test1, "r1", 200);
    std::vector<Waypoint*> test2{ &wp2, &wp1 };
    Route r2 = Route::Route(test2, "r2", 200.0);

    std::vector<Route*> listRoutes{ &r0, &r1, &r2 };
    RouteFinder finder(listRoutes, &wp3, 12000);
    std::vector<Route*> result = finder.findShortestTraversal();

    // Temp: Print pathfinding results
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i]->name << std::endl;
    }
    std::cout << "Size: " << result.size() << std::endl;


    std::cout << "Hello World!\n";

    std::ifstream f("Text.json");
    json data = json::parse(f);
    std::vector<std::vector<json>> waypointData = {};
    std::vector<std::vector<json>> routeData = {};
    std::vector <json> routefinderData = {};
    std::string waypointNumber = "";
    std::string routeNumber = "";
    
    
    for (int i = 0; i < 4; i++) {
        waypointNumber = std::to_string(i);
        json waypoint = data.at("Waypoint" + waypointNumber);
        waypointData.push_back({ waypoint.at("refLat"), waypoint.at("refLong"), waypoint.at("waypointId")});
    }

    for (int i = 0; i < 3; i++) {
        routeNumber = std::to_string(i);
        json route = data.at("Route" + routeNumber);
        routeData.push_back({ route.at("waypointIds"), route.at("routeID"), route.at("dollarValue")});
    }
    
    
    json routeFinder = data.at("RouteFinder");
    routefinderData.push_back(routeFinder.at("routeIds"));
    routefinderData.push_back(routeFinder.at("maxFlyingDistance"));
    routefinderData.push_back(routeFinder.at("startingWaypointId"));
    
    //Testing (Temporary)
    
    for (int i = 0; i < waypointData.size(); i++)
    {
        for (int j = 0; j < waypointData[i].size(); j++)
        {
            std::cout << waypointData[i][j] << "\n";
        }
    }

    for (int i = 0; i < routeData.size(); i++)
    {
        for (int j = 0; j < routeData[i].size(); j++)
        {
            std::cout << routeData[i][j] << "\n";
        }
    }

    for (int j = 0; j < routefinderData.size(); j++)
    {
        std::cout << routefinderData[j] << "\n";
    }
   

    

    //std::cout << refLat;

    return 0;
}
