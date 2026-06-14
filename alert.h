#ifndef ALERT_H
#define ALERT_H

#include "data_types.h"

void setupAlerts();
void sendAlert(AircraftData data);
void compareAlerts(int aircraftCount, AircraftData aircraft[], int alertCount, AircraftData alertAircraft[]);

#endif