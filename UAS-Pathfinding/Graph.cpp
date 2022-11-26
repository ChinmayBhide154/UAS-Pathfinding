#include "Graph.h"
#include <iostream>


Graph::Graph(std::vector<Waypoint*> waypoints) {
    this->waypoints = waypoints;
}

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

void Graph::dijkstra(int n, int startnode, vector<Waypoint*> obstacles, Waypoint* target) {
    vector<vector<double>> G = this->getGraphMatrix(obstacles, target);
    int cost[5][5], distance[5], pred[5];
    int visited[5], count, mindistance, nextnode, i, j;
    
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
    for (i = 0;i < n;i++)
        if (i != startnode) {
            cout << "Distance of node"<<i<<" = "<<distance[i];
            cout << "Path = "<<i;
            j = i;
            
            do {
                j = pred[j];
                cout << "<-" << j;
            } while (j != startnode);
        }
}


	




