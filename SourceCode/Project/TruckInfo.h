#ifndef TRUCK_INFO_H
#define TRUCK_INFO_H

#define MAX_WEIGHT 900
#define MAX_VOL 30
#define WEIGHT_MAX_VOL 10 //max vol when weight is max
#define VOL_MAX_WEIGHT 200 //max weight when volume is max
#include "mapping.h"

//Current Info Of the truck
struct TruckInfo {
	int currentWeight; // current Wieght of the truck
	double currentVol; // current Vol of the truck
	struct Route* currentRoute; //The Route which the truck is following
};

/*
* Function Name : getTruck
* Function Description : Determines the truck according to the shipment input entered by the user
* Function Parameters : Structure ShipmentInfo
* Function Return Type : Integer
* Returns : Integer of value of the truck assigned 
			for example : returns 2 if blue 
						: returns 4 if green
						: returns 8 if yellow
						: returns -1 if no truck is avalabile to deliver customer shipment
*/
int getTruck(struct ShipmentInfo input);



/***
* Function: spaceConsumption
* Determines spaceConsumption in float
* further this spaceConsumption can be determined to check if the shipment can be assigned to a particular truck without exceeding its weight and volume capacity.
* Function Parameters:
*	  - w : input weight
*	  - v : input volume 
* Returns : float
*/
float spaceConsumption(int w, double v);


/*
* Function Name: populateValidRoutesForTruck
* Function Description: Fills the "routeOptions" array with potential routes that the specified "truck" can use to reach the "shipment" destination.
* Function Parameters:
*     - shipment: The ShipmentInfo structure specifying the details and destination of the shipment.
*     - truck: The TruckInfo structure containing the details about the truck, including its current route.
*     - currentMap: The Map structure providing all the information about possible paths on the map.
*     - routeOptions: An array that will be populated with all valid routes for the specified truck.
*     - routeCount: A pointer to an integer tracking the number of valid routes added to the "routeOptions" array.
* Returns: void
* Populates the "routeOptions" array with valid routes for the specified truck.
*/
void populateValidRoutesForTruck(struct ShipmentInfo shipment, struct TruckInfo truck, const struct Map* currentMap, struct Route* routeOptions[], int* routeCount);

/*
* Function Name: getBestRoute
* Function Description: Loops through all valid routes in the "routes" array and returns the index of the route with the shortest distance.
* Function Parameters:
*     - routes: Holds all valid routes (i.e. struct Route)
*     - s0: Index of the starting point in the route
*     - s: Shipment struct, containing the Shipment destination
* Returns: int
* Index of the route in the "routes" array with the shortest distance.
*/
int getBestRoute(struct Route routes[], int s0, struct Shipment s);

/*
* Function Name: isDestinationInRoute
* Function Description: Verifies if the given route includes the shipment destination.
* Function Parameters:
*     - potentialRoute: The shortest calculated route from the current point of a truck's path.
*     - shipment: Shipment struct containing the shipment's destination.
* Returns: int
* Returns 1 if the destination is included in the route, otherwise returns 0.
*/
int isDestinationInRoute(struct Route* potentialRoute, struct ShipmentInfo shipment);



#endif
