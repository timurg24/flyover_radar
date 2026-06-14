// DO NOT EDIT. GO EDIT THE .CPP FILE

#ifndef ENV_H
#define ENV_H

#include "data_types.h"

extern const char* wifiName;
extern const char* wifiPassword;

extern const char* clientID;
extern const char* clientSecret;

extern LocationBounds bounds;

extern int interfacePort;

extern int openSkyInterval;

extern int alertCount;
extern AircraftData alertData[];

#endif