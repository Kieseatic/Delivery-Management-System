#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "TruckInfo.h"
#include "customerShipment.h"


/// in progress

void readInput() {
    double volume;
    int weight, scanStatus;
    char destinationInput[4];
    struct Point shipmentDestination;
    struct ShipmentInfo shipment;

    printf("=================\n");
    printf("Seneca Deliveries\n");
    printf("=================\n");

    // Loop until stop conditions are met
    while (1) {
        printf("Enter shipment weight, box volume and destination (0 0 x to stop): ");
        scanStatus = scanf("%d %lf %s", &weight, &volume, destinationInput);

        // Clear input buffer
        while (getchar() != '\n') {}

        // Ensure correct format was entered
        if (scanStatus != 3) {
            printf("Invalid input. Follow this example: 1 1 1A\n");
            continue;
        }

        parseDestination(destinationInput, &shipmentDestination);

        int validationResult = validateShipment(volume, weight, shipmentDestination);

        if (validationResult < 1) {
            if (validationResult == 0) break;
            continue;
        }

        shipment.weight = weight;
        shipment.vol = volume;
        shipment.dropLocation = shipmentDestination;
        getTruck(shipment);
    }
}

void parseDestination(const char* destinationInput, struct Point* destination) {
    int row = 0, col = 0;
    int len = strlen(destinationInput);
    for (int i = 0; i < len; i++) {
        char c = destinationInput[i];
        if (c >= '0' && c <= '9') {
            row = row * 10 + (c - '0');
        }
        else if (c >= 'A' && c <= 'Z') {
            col = col * 26 + (c - 'A' + 1);
        }
    }
    destination->row = row - 1;
    destination->col = col - 1;
}

int validateShipment(double volume, int weight, struct Point destination) {
    const int maxDestination = 26;
    const int minDestination = 0;

    struct Map map =  populateMap(); 
    struct Map* mapPtr = &map;

    if (weight == 0 && volume == 0 && destination.row == 'x') {
        printf("Thank you for shipping with Seneca!\n");
        return 0; 
    }

    if (weight < 1 || weight > 1000) {
        printf("Invalid weight (must be 1-1000 Kg.)\n");
        return -2;
    }

    if (volume != CAP_VOL_ONE && volume != CAP_VOL_TWO && volume != CAP_VOL_THREE) {
        printf("Invalid size\n");
        return -1;
    }

    if (destination.row < minDestination || destination.row > maxDestination
        || destination.col < minDestination || destination.col > maxDestination) {
        printf("Invalid destination\n");
        return -3;
    }

    if (mapPtr->squares[destination.row][destination.col] == 0) {
        printf("Invalid destination\n");
        return -3;
    }

    return 1;
}

