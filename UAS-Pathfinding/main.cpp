/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include "Waypoint.h"
#include "Graph.h"
int main()
{
    
    Waypoint w1;
    Waypoint w2;
    Waypoint w3;
    Waypoint w4;
    Waypoint w5;
    Waypoint w6;
    Waypoint w7;
    w1.x = -5; w1.y = 2; w1.id = 0;
    w2.x = 1; w2.y = 1; w2.id = 1;
    w3.x = 5; w3.y = 10; w3.id = 2;
    w4.x = -1; w4.y = -2; w4.id = 3;
    w5.x = 3; w5.y = -3; w5.id = 4;
    w6.x = -3; w6.y = -6; w6.id = 5;
    w7.x = 4; w7.y = -13; w7.id = 6;
    vector<Waypoint*> waypoints = {&w1, &w2, &w3, &w4, &w5, &w6, &w7};
    vector<Waypoint*> obstacles = { &w2, &w5, &w6, &w4, &w2 };
    
    int n = 5;
    Graph graph = Graph(waypoints);
    vector<vector<double>> matrix;
    matrix = graph.getGraphMatrix(obstacles, -2, 1);
    vector<int> shortestPath = {};
    //shortestPath = graph.dijkstra(matrix, 7, 0, 4);
    shortestPath = graph.reroute(5, matrix, 8, 0, 6);
    /*
    vector<vector<int>> G = { {0,1,0,3,10},{1,0,5,0,0},{0,5,0,2,1},{3,0,2,0,6},{10,0,1,6,0}};
    int n = 5;
    int u = 0;
    Graph graph = Graph();
    vector<int> shortestPath = {};
    shortestPath = graph.dijkstra(G, n, u, 3);
    */
    for (int i = 0; i < shortestPath.size(); i++)
        std::cout << shortestPath.at(i) << ' ';
    
    
    return 0;


    std::cout << "Hello World!\n";
}