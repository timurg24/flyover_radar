#ifndef ALERT_H
#define ALERT_H

#include "data_types.h"
#include <AsyncTelegram2.h>

extern WiFiClientSecure client;
extern AsyncTelegram2 bot;
extern std::vector<String> alertedRegistrations;

// defined in category.alert.cpp
String categoryToString(AircraftCategory cat);
String categoryToStringSimple(AircraftCategory cat);
AircraftCategory stringToCategory(const String& cat);

// defined in management.alert.cpp 
void newAlert(TBMessage msg, int type, const String& trigger);
void deleteAlert(TBMessage msg, const String& trigger);
void saveAlerts();
void clearAlerts();
void loadAlerts(); 
void fillAlertsFromTemplate();

// defined in alert.cpp
void setupAlerts();
std::vector<String> splitCommand(const String& original, char delimeter);
void sendListOfAlerts(TBMessage msg);
void sendAlert(AircraftData data);
void handleTelegramMessage();
void compareAlerts(int aircraftCount, AircraftData aircraft[]);

#endif