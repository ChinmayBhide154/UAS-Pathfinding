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

#include "Waypoint.h"
#include "RouteRerouter.h"
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
        listWaypoints.push_back(new Waypoint(waypoint["refLat"], waypoint["refLong"], true, std::to_string((uint32_t) waypoint["waypointId"]), 0, 0, 0));
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


    std::vector<Route*> result;
    if (NUM_ROUTES < 19) {
        RouteFinder finder(listRoutes, listWaypoints[startPointIndex], routeFinder["maxFlyingDistance"], false);
        result = finder.findShortestTraversalAccurate();
    }
    else {
        RouteFinder finder(listRoutes, listWaypoints[startPointIndex], routeFinder["maxFlyingDistance"], true);
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

    //
    //Waypoint w1;
    //Waypoint w2;
    //Waypoint w3;
    //Waypoint w4;
    //Waypoint w5;
    //Waypoint w6;
    //Waypoint w7;
    //w1.x = -5; w1.y = 2; w1.id = 0;
    //w2.x = 1; w2.y = 1; w2.id = 1;
    //w3.x = 5; w3.y = 10; w3.id = 2;
    //w4.x = -1; w4.y = -2; w4.id = 3;
    //w5.x = 3; w5.y = -3; w5.id = 4;
    //w6.x = -3; w6.y = -6; w6.id = 5;
    //w7.x = 4; w7.y = -13; w7.id = 6;
    //vector<Waypoint*> waypoints = {&w1, &w2, &w3, &w4, &w5, &w6, &w7};
    //vector<Waypoint*> obstacles = { &w2, &w5, &w6, &w4, &w2 };
    //
    //int n = 5;
    //RouteRerouter graph = RouteRerouter(waypoints);
    //vector<vector<double>> matrix;
    //matrix = graph.getGraphMatrix(obstacles, -2, 1);
    //vector<int> shortestPath = {};
    ////shortestPath = graph.dijkstra(matrix, 7, 0, 4);
    //shortestPath = graph.reroute(5, matrix, 8, 0, 6);
    ///*
    //vector<vector<int>> G = { {0,1,0,3,10},{1,0,5,0,0},{0,5,0,2,1},{3,0,2,0,6},{10,0,1,6,0}};
    //int n = 5;
    //int u = 0;
    //Graph graph = Graph();
    //vector<int> shortestPath = {};
    //shortestPath = graph.dijkstra(G, n, u, 3);
    //*/
    //for (int i = 0; i < shortestPath.size(); i++)
    //    std::cout << shortestPath.at(i) << ' ';
    //
    //
    //return 0;

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
