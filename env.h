// DO NOT EDIT. GO EDIT THE .CPP FILE

#ifndef ENV_H
#define ENV_H

#include "data_types.h"
#include <vector>

extern const char* wifiName;
extern const char* wifiPassword;

extern const char* clientID;
extern const char* clientSecret;

extern const char* telegramBotID;
extern int64_t telegramChatID;

extern LocationBounds bounds;

extern int interfacePort;

extern int openSkyInterval;

extern std::vector<AircraftData> alerts;

#endif
