/* UAS Pathfinding
*  Created by: Justin Wong, Chinmay Bhide, Benjamin Brett
*/
#include <iostream>
#include <vector>
#include "Route.h"
#include "RouteFinder.h"
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
}