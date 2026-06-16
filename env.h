// DO NOT EDIT. GO EDIT THE .CPP FILE

#ifndef ENV_H
#define ENV_H

#include "data_types.h"
#include <vector>

extern const char* wifiName;
extern const char* wifiPassword;

extern const char* clientID;
extern const char* clientSecret;
extern int openSkyInterval;

extern const char* telegramBotID;
extern int64_t telegramChatID;

extern LocationBounds bounds;


extern std::vector<AircraftData> alertsTemplate;
extern std::vector<AircraftData> alerts;

#endif
