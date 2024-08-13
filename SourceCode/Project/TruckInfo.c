#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "TruckInfo.h"
#include "customerShipment.h"
#include "mapping.h"
#include "configure.h"


int getTruck(struct ShipmentInfo input) {
    int size = 0;
    int selectedTruck = -1;
    struct Route routesArray[MAX_ROUTE] = { 0 };

    struct Route routes[] = { getBlueRoute(), getGreenRoute(), getYellowRoute() };

    for (int i = 0; i < 3; i++) {
        trucks[i].currentRoute = &routes[i];
        double currentSpaceScore = spaceConsumption(trucks[i].currentWeight, trucks[i].currentVol);

        if ((currentSpaceScore + spaceConsumption(input.weight, input.vol) > 0.0) &&
            (trucks[i].currentWeight + input.weight <= MAX_WEIGHT) && (trucks[i].currentVol + input.vol <= MAX_VOL))
            populateValidRoutesForTruck(input, trucks[i], baseMap, &routesArray, &size);
    }

    int shortestRouteIdx = 0;
    for (int i = 1; i < size; i++) {
        if (routesArray[i].numPoints < routesArray[shortestRouteIdx].numPoints)
            shortestRouteIdx = i;
    }

    int routeSymbols[] = { 2, 4, 8 };
    for (int i = 0; i < 3; i++) {
        if (routesArray[shortestRouteIdx].routeSymbol == routeSymbols[i]) {
            trucks[i].currentVol += input.vol;
            trucks[i].currentWeight += input.weight;
            selectedTruck = routeSymbols[i];
            break;
        }
    }

    return selectedTruck;
}

float spaceConsumption(int w, double v) {
    if (w <= 0 || v <= 0) {
        return 0.0f;
    }

    float weightScore = (float)w / MAX_WEIGHT;
    float volumeScore = (float)v / MAX_VOL;

    return weightScore / volumeScore;
}

void populateValidRoutesForTruck(struct ShipmentInfo shipment, struct TruckInfo truck, const struct Map* currentMap, struct Route routeOptions[MAX_ROUTE], int* routeCount) {
    struct Map populatedMap = populateMap();

    for (int routeIndex = 0; routeIndex < truck.currentRoute->numPoints; routeIndex++) {
        struct Route calculatedRoute = shortestPath(&populatedMap, truck.currentRoute->points[routeIndex], shipment.dropLocation);
        const struct Point endPoint = calculatedRoute.points[calculatedRoute.numPoints - 1];
        const struct Point dropPoint = shipment.dropLocation;

        int isAdjacent = ((endPoint.row - dropPoint.row) * (endPoint.row - dropPoint.row) + (endPoint.col - dropPoint.col) * (endPoint.col - dropPoint.col)) <= 1 ? 1 : 0;

        int destinationInPath = isDestinationInRoute(&calculatedRoute, shipment);
        if (calculatedRoute.numPoints == 2 && destinationInPath == 0) {
            if (calculatedRoute.points[0].row == truck.currentRoute->points[routeIndex].row && calculatedRoute.points[0].col == truck.currentRoute->points[routeIndex].col) {
                calculatedRoute.points[0] = shipment.dropLocation;
                calculatedRoute.numPoints = 1;
            }
            calculatedRoute.routeSymbol = truck.currentRoute->routeSymbol;
            routeOptions[(*routeCount)++] = calculatedRoute;
        }
        else if ((destinationInPath == 1) || (isAdjacent && !destinationInPath)) {
            calculatedRoute.routeSymbol = truck.currentRoute->routeSymbol;
            routeOptions[(*routeCount)++] = calculatedRoute;
        }
    }
}

int isDestinationInRoute(struct Route* potentialRoute, struct ShipmentInfo shipmentDetails) {
    for (int i = 0; i < potentialRoute->numPoints; i++) {
        if (potentialRoute -> points[i].col == shipmentDetails.dropLocation.col && potentialRoute->points[i].row == shipmentDetails.dropLocation.row) {
            return 1;
        }
    }
    return 0;
}