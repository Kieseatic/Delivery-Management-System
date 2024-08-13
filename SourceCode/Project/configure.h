#ifndef INIT_H
#define INIT_H
#include "TruckInfo.h"
#include "customerShipment.h"
#include "mapping.h"

struct Map* baseMap;
struct TruckInfo trucks[3];

/**
 * Function Name: init
 * Function Description: This function is responsible for creation and initialization of variables which will
 * be used by the structures.
 */
void configure();

#endif