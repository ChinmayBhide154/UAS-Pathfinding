/*

#include "JSON.h"


#include <fstream>
// #include <nlohmann/json.hpp>    // NOTE: Change to the line below
#include "../submodules/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

//reads a json file and returns a Graph
//File is named input.json

std::ifstream f("Text.json");
json data = json::parse(f);
*/
/*
namespace ns {
    void to_json(json& j, const graph& g) {
        j = json{{"Route", g.route}, 
        {"Waypoint", g.route.waypoint},
        }};
    }

    void from_json(const json& j, BestRoutes& r) {
        j.at("BestRoute").get_to(r.name);
        j.at("BestRoute").get_to(r.waypoints);
    }


std::ifstream i("file.json");       // NOTE: Just rename the i to f and u can use parse(f) on line 26)
json j; // NOTE: dont need this
i >> j; // NOTE: dont need this
json data = json::parse(f);

// NOTE: It might be hard to directly parse to our data types on the first try

ns::"Graph" g: [
    {
        "Route": "0" //where 0 is the name of route 0
            "waypoint" :[{
             double x,
             double y,
             double lat,
             double long,
             string name,
        }]
        "Route": "1" {
            "waypoint" [{
                double x,
                double y,
                double lat,
                double long,
                string name,
            }]
            double rank,
            double timeSeconds,
            double avgSpeedMeterSec,
        }
    }
]

routes [
    waypoints {
        double x,
        double y,
        double lat,
        double long,
        string name,
    }
    string name,
    double dollarvalue,
]

// conversion: json -> Graph
auto g2 = j.get<ns::"graph">();
assert(g == g2);
*/



//-------------------------------

//writes ______ to a json file
/*
list of waypoints is all that is outputted
File is named output.json

{ BestRoutes: [ {name: 1, waypoints: [ waypoint0, waypoint1]},
            {name: 2, waypoints: [ waypoint2, waypoint6754, waypoint3]},
            {name: 3, waypoints: [ waypoint3, waypoint999]},
            {name: 4, waypoints: [ waypoint69, waypoint420]} ]
}
*/
/*
ns::BestRoutes r: [
    [ {name: 1, waypoints: [ waypoint0, waypoint1]},
            {name: 2, waypoints: [ waypoint2, waypoint6754, waypoint3]},
            {name: 3, waypoints: [ waypoint3, waypoint999]},
            {name: 4, waypoints: [ waypoint69, waypoint420]} ]
]
*/
// conversion: person -> json
/*
json j = BestRoutes;
//std::cout << j << std::endl;

// write prettified JSON to another file
std::ofstream o("output.json");
o << std::setw(4) << j << std::endl;
*/




