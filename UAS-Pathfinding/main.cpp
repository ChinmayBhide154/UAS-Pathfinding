/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include <vector>
#include <string.h>
#include "JSON.h"
#include <fstream>
#include <stdexcept>
#include <map>
#include "../submodules/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
int main()
{
    
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
