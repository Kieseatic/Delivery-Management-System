#ifndef CUSTOMERSHIPMENT_H
#define CUSTOMERSHIPMENT_H

#define CAP_VOL_ONE 0.25
#define CAP_VOL_TWO 0.50
#define CAP_VOL_THREE 1.0

#include "mapping.h"

// shipment information which the cusotmer enters 
struct ShipmentInfo {
	int weight; // input Weight
	double vol; // input volume
	struct Point dropLocation; //destination location
};

/**
* Function Name:  readInput
* Function Description: Reads from the user the shipment information and stores it to ShipmentInfo Struture
*/
void readInput();

/*
* Function Name: validateShipment
* Function Description: Validates shipment details entered by the user.
* Function Parameters:
*               volume: Volume of the shipment.
*               weight: Weight of the shipment.
*               destination: Delivery destination.
* Function Returns:
*               1 if shipment details are valid.	  
*               0 if termination condition met.
*               -1 if volume is invalid.
*               -2 if weight is invalid.
*               -3 if destination is invalid.
*/
int validateShipment(double volume, int weight, struct Point destination);

/*
* Function Name: parseDestination
* Function Description: Parses the input string into row and column indices for a Point structure.
* Function Parameters:
*				destinationInput: input string containing the destination in a format like '1A', '5C' etc.
*				destination: pointer to the Point structure where the parsed destination will be stored.
* Function Returns:
*				void
*/
void parseDestination(const char* destinationInput, struct Point* destination);


#endif