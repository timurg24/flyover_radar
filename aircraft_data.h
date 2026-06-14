#ifndef AIRCRAFT_DATA
#define AIRCRAFT_DATA

#include <WiFi.h>

#include "data_types.h"
#include "env.h"

String getRequestString(LocationBounds location);
AircraftData getDataFromICAO(String icao);
void getAircraftData(int& count, AircraftData data[]);

#endif