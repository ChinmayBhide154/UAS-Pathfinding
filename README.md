# Competition Rule Recap

Take off and fly the specified route, staying within 50 m of the route centre line. The route will
be no less than 10 (ten) km long, and no more than 30 km.

During the flight, a message will be received at the ground station by voice and QR code (Voice
and QR code: “Avoid the area bounded by Waypoint 1; Waypoint 2; …Waypoint n. Rejoin the
route at Waypoint X”) advising of a geographical area which must be avoided, and indicating the
waypoint at which the route must be regained. UAMS response may be manual or autonomous.

# About
This Pathfinding interface is a 2 part module. The usage of these modules are described below

# RouteFinder Usage
To be filled in by Justin

# Rerouting Usage
This module is used when the competition announcer announces the obstacles. The obstacle is an area defined by a list of waypoints. For this module to run, the module will require an input json file with data outlined here: https://docs.google.com/presentation/d/1ZtkNaP7A_W1ufFKoNRiZyiWmhXZ6YBcHu0yLnHL2PI0/edit#slide=id.p. In return, the module will generate an output json containing the list of waypoints to traverse in order to reach the destination node of the current route. Please note that the list of waypoints will nessassarely include the obstacle waypoints themselves. Thus, the drone operator should take into consideration that such "dangerous" waypoints should not be followed closely, and that the drone should be outside the trigger radius of the waypoint. How this module will be used (whether it will be run manually or autonimously is yet to be determined)

