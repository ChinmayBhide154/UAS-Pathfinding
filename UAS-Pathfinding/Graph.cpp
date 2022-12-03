#include "Graph.h"
#include <iostream>


Graph::Graph(std::vector<Waypoint*> waypoints) {
    this->waypoints = waypoints;
}

Graph::Graph(){}

vector<vector<double>> Graph::getGraphMatrix(vector<Waypoint*> obstacles, Waypoint* target) {
    vector<vector<double>> matrix(max, vector<double>(5));
    for (int i = 0; i < waypoints.size() - 1; i++) {
        for (int j = 0; j < waypoints.size() - 1; j++) {
            if (waypoints[j]->isObstructionN(obstacles, target)) {
                matrix[i][j] = INFINITY;
            }
            else {
                matrix[i][j] = sqrt((waypoints[i]->x * waypoints[i]->x) + (waypoints[j]->y * waypoints[j]->y));
                    cout << matrix[i][j] << " ";
            }

        }
    }

    return matrix;
}

vector<int> Graph::dijkstra(vector<vector<int>> G, int n, int startnode, int destinationNode) {
    int cost[max][max], distance[max], pred[max];
    vector<int> shortestPath = {};
    int visited[max], count, mindistance, nextnode, i, j;
    for (i = 0;i < n;i++)
        for (j = 0;j < n;j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];
    for (i = 0;i < n;i++) {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1) {
        mindistance = INFINITY;
        for (i = 0;i < n;i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        visited[nextnode] = 1;
        for (i = 0;i < n;i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    shortestPath.push_back(destinationNode);
    j = destinationNode;
    do {
        j = pred[j];
        shortestPath.push_back(j);
    } while (j != startnode);

    reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}


vector<int> Graph::reroute(int continueOn, vector<vector<int>> G, int n, int startnode, int destinationNode) {
    vector<int> totalPath = {};
    vector<int> destinationPath = {};

    totalPath = dijkstra(G, n, startnode, continueOn);
    destinationPath = dijkstra(G, n, continueOn, destinationNode);
    totalPath.insert(totalPath.end(), destinationPath.begin(), destinationPath.end());
    return totalPath;
}


	




