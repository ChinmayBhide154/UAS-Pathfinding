#include "pch.h"
#include <vector>
#include <iostream>
#include <string>
#include "..\UAS-Pathfinding\RouteFinder.h"
#include "..\UAS-Pathfinding\RouteFinder.cpp"
#include "..\UAS-Pathfinding\Route.cpp"
//#include "..\submodules\Minimum-Cost-Perfect-Matching\Graph.cpp"
//#include "..\submodules\Minimum-Cost-Perfect-Matching\Matching.cpp"
//#include "..\submodules\Minimum-Cost-Perfect-Matching\BinaryHeap.cpp"

Waypoint wp0 = Waypoint::Waypoint(0, 10, false, "wp0", 49.269309, -123.242703);
Waypoint wp1 = Waypoint::Waypoint(10, 10, false, "wp1", 49.269309, -123.242703);
Waypoint wp2 = Waypoint::Waypoint(10, 0, false, "wp2", 49.269309, -123.242703);
Waypoint wp3 = Waypoint::Waypoint(0, 0, false, "wp3", 49.269309, -123.242703);
Waypoint wp4 = Waypoint::Waypoint(5, 5, false, "wp4", 49.269309, -123.242703);
Waypoint wp10 = Waypoint::Waypoint(0, 20, false, "wp0", 49.269309, -123.242703);
Waypoint wp11 = Waypoint::Waypoint(20, 20, false, "wp1", 49.269309, -123.242703);
Waypoint wp12 = Waypoint::Waypoint(20, 0, false, "wp2", 49.269309, -123.242703);
Waypoint wp13 = Waypoint::Waypoint(0, 0, false, "wp3", 49.269309, -123.242703);
Waypoint wp14 = Waypoint::Waypoint(7, 7, false, "wp4", 49.269309, -123.242703);
Waypoint wp20 = Waypoint::Waypoint(0, 17, false, "wp0", 49.269309, -123.242703);
Waypoint wp21 = Waypoint::Waypoint(17, 17, false, "wp1", 49.269309, -123.242703);
Waypoint wp22 = Waypoint::Waypoint(17, 0, false, "wp2", 49.269309, -123.242703);
Waypoint wp23 = Waypoint::Waypoint(0, 0, false, "wp3", 49.269309, -123.242703);
Waypoint wp24 = Waypoint::Waypoint(16, 4, false, "wp4", 49.269309, -123.242703);
Waypoint wp30 = Waypoint::Waypoint(0, 27, false, "wp0", 49.269309, -123.242703);
Waypoint wp31 = Waypoint::Waypoint(31, 19, false, "wp1", 49.269309, -123.242703);
Waypoint wp32 = Waypoint::Waypoint(18, 0, false, "wp2", 49.269309, -123.242703);
Waypoint wp33 = Waypoint::Waypoint(11, 10, false, "wp3", 49.269309, -123.242703);
Waypoint wp34 = Waypoint::Waypoint(3, 2, false, "wp4", 49.269309, -123.242703);

TEST(RouteFinderTests, projectConfigTest) {
	std::vector<Waypoint*> test0{&wp4, &wp2, &wp3};
	Route r0 = Route::Route(test0, "r0", 200.0);
	std::vector<Waypoint*> test1{&wp3, &wp2};
	Route r1 = Route::Route(test1, "r1", 200);
	std::vector<Waypoint*> test2{&wp2, &wp1};
	Route r2 = Route::Route(test2, "r2", 200.0);
	std::vector<Waypoint*> test4{&wp20, &wp22};
	Route r3 = Route::Route(test4, "r2", 132.0);
	
	std::vector<Waypoint*> test5{&wp21, &wp23};
	Route r4 = Route::Route(test5, "r2", 12.0);
	
	std::vector<Waypoint*> test6{&wp30, &wp24};
	Route r5 = Route::Route(test6, "r2", 94.0);
	
	std::vector<Waypoint*> test7{&wp31, &wp32};
	Route r6 = Route::Route(test7, "r2", 132.0);
	
	std::vector<Waypoint*> test8{&wp32, &wp21};
	Route r7 = Route::Route(test8, "r2", 132.0);
	
	std::vector<Waypoint*> test9{&wp24, &wp22};
	Route r8 = Route::Route(test9, "r2", 132.0);
	
	std::vector<Waypoint*> test10{&wp13, &wp32};
	Route r9 = Route::Route(test10, "r2", 132.0);
	
	std::vector<Waypoint*> test11{&wp22, &wp23};
	Route r10 = Route::Route(test11, "r2", 132.0);
	
	std::vector<Waypoint*> test12{&wp1, &wp12};
	Route r11 = Route::Route(test12, "r2", 132.0);
	
	std::vector<Waypoint*> test13{&wp3, &wp32};
	Route r12 = Route::Route(test13, "r2", 132.0);
	
	std::vector<Waypoint*> test14{&wp34, &wp0};
	Route r13 = Route::Route(test14, "r2", 132.0);

	std::vector<Route*> listRoutes{&r0, &r1, &r2, &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 , &r2 };
	RouteFinder finder(listRoutes, &wp3, 12000);
	std::cout << "Accurate ver:\n";
	std::vector<Route*> result = finder.findShortestTraversalAccurate();
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i]->name << std::endl;
	}
	std::cout << "Size: " << result.size() << std::endl;


	std::cout << "Naive-Fast ver:\n";
	result = finder.findShortestTraversal();
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i]->name << std::endl;
	}
	std::cout << "Size: " << result.size() << std::endl;


	ASSERT_TRUE(true);
}

