/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include "Waypoint.h"
#include "Graph.h"
int main()
{
    /*
    Waypoint w1;
    Waypoint w2;
    Waypoint w3;
    Waypoint w4;
    Waypoint w5;
    w1.x = 0; w1.y = 0;
    w2.x = 0; w2.y = 0;
    w3.x = 0; w3.y = 0;
    w4.x = 0; w4.y = 0;
    w5.x = 0; w5.y = 0;
    vector<Waypoint*> waypoints = {&w1, &w2, &w3, &w4, &w5};
    vector<Waypoint*> obstacles = { &w2, &w3 };
    
    int n = 5;
    Graph graph = Graph(waypoints);
    graph.reroute(n, &w1, obstacles, &w5);
    */

    vector<vector<int>> G = { {0,1,0,3,10},{1,0,5,0,0},{0,5,0,2,1},{3,0,2,0,6},{10,0,1,6,0}};
    int n = 5;
    int u = 0;
    Graph graph = Graph();
    vector<int> shortestPath = {};
    shortestPath = graph.dijkstra(G, n, u, 3);

    for (int i = 0; i < shortestPath.size(); i++)
        std::cout << shortestPath.at(i) << ' ';
    //return 0;
    return 0;


    std::cout << "Hello World!\n";
}