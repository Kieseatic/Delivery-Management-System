#include "configure.h"
#include "TruckInfo.h"

void configure(void) {
	

	struct Map baseMap = populateMap();

    struct Route routes[] = { getBlueRoute(), getGreenRoute(), getYellowRoute() };

    for (int i = 0; i < 3; i++) {
        trucks[i].currentRoute = &routes[i];
        trucks[i].currentVol = 0;
        trucks[i].currentWeight = 0;
    }
}