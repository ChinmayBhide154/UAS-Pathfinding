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

    std::vector<json> waypoints = {};
    std::string waypointNumber = "";
    for (int i = 0; i < 4; i++) {
        waypointNumber = std::to_string(i);
        waypoints.push_back(data.at("Waypoint" + waypointNumber));
        std::cout << "Waypoint" + waypointNumber << "\n";
    }


    

    //json waypoint0 = data.at("Waypoint0");
    //json refLat = waypoint0.at("refLat");
    //json refLong = waypoint0.at("refLong");

    //std::cout << refLat;

    return 0;
}
