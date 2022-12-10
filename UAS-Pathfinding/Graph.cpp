#include "Graph.h"
#include <iostream>


Graph::Graph(std::vector<Waypoint*> waypoints) {
    this->waypoints = waypoints;
}

Graph::Graph(){}

vector<vector<double>> Graph::getGraphMatrix(vector<Waypoint*> obstacles, double currentX, double currentY) {
    Waypoint* currentLocation = new Waypoint();
    currentLocation->x = currentX;
    currentLocation->y = currentY;
    this->waypoints.insert(this->waypoints.begin(), currentLocation);
    bool destIsObstruction = false;
    bool currentIsObstruction = false;

    vector<vector<double>> matrix(max, vector<double>(max));
    for (int i = 0; i < this->waypoints.size(); i++) {
        for (int j = 0; j < this->waypoints.size(); j++) {
            //if (std::find(obstacles.begin(), obstacles.end(), this->waypoints[i]) != obstacles.end() || 
            //    std::find(obstacles.begin(), obstacles.end(), this->waypoints[j]) != obstacles.end()) {
            //    destIsObstruction = true;
            //}
            if (std::find(obstacles.begin(), obstacles.end(), this->waypoints[i]) != obstacles.end()) {
                currentIsObstruction = true;
            }
            if (std::find(obstacles.begin(), obstacles.end(), this->waypoints[j]) != obstacles.end()) {
                destIsObstruction = true;
            }

            if (this->waypoints[j]->isObstructionN(obstacles, this->waypoints[i], destIsObstruction, currentIsObstruction, this->waypoints[i])) {
                matrix[i][j] = INFINITY;
            }
            else {
                double dx = this->waypoints[j]->x - this->waypoints[i]->x;
                double dy = this->waypoints[j]->y - this->waypoints[i]->y;
                matrix[i][j] = sqrt((dx * dx) + (dy * dy));
                    //cout << matrix[i][j] << " ";
            }

            std::cout << "matrix[" << i << "]" << "[" << j << "]" << "\n";

            destIsObstruction = false;
            currentIsObstruction = false;
        }
    }

    return matrix;
}

vector<int> Graph::dijkstra(vector<vector<double>> G, int n, int startnode, int destinationNode) {
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


vector<int> Graph::reroute(int continueOn, vector<vector<double>> G, int n, int startnode, int destinationNode) {
    vector<int> totalPath = {};
    vector<int> destinationPath = {};

    totalPath = dijkstra(G, n, startnode, continueOn);
    destinationPath = dijkstra(G, n, continueOn, destinationNode);
    destinationPath.erase(destinationPath.begin());
    totalPath.insert(totalPath.end(), destinationPath.begin(), destinationPath.end());
    return totalPath;
}


	




