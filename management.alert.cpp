#include "alert.h"
#include "env.h"
#include <Preferences.h>

/// @brief Creates a new alert
/// @param msg Telegram message
/// @param type Type of alert (0 = type code, 1 = registration, 2 = category, 3 = squawk)
/// @param trigger Alert trigger
void newAlert(TBMessage msg, int type, const String& trigger) {
  AircraftData newAircraftAlert;

  if (type == 0) {  // type code
    newAircraftAlert.icaoType = trigger;
    alerts.push_back(newAircraftAlert);

    bot.sendMessage(msg, "New type code alert created");
  } else if (type == 1) {  // registration
    newAircraftAlert.registration = trigger;
    alerts.push_back(newAircraftAlert);

    bot.sendMessage(msg, "New registration alert created");
  } else if (type == 2) {
    newAircraftAlert.category = stringToCategory(trigger);
    alerts.push_back(newAircraftAlert);
    bot.sendMessage(msg, "New category alert created");
  } else if (type == 3) {
    newAircraftAlert.squawk = trigger.toInt();
    alerts.push_back(newAircraftAlert);
    bot.sendMessage(msg, "New squawk alert created");
  }
  saveAlerts();
}

/// @brief Deletes alert
/// @param msg Telegram message
/// @param trigger Alert trigger
void deleteAlert(TBMessage msg, const String& trigger) {
  for (int i = 0; i < alerts.size(); i++) {
    if (alerts[i].icaoType == trigger || alerts[i].registration == trigger || alerts[i].squawk == trigger.toInt() || alerts[i].category == stringToCategory(trigger)) {
      alerts.erase(alerts.begin() + i);
      bot.sendMessage(msg, "Deleted alert");
    }
  }
  saveAlerts();
}

/// @brief Saves your alerts to ESP32's flash memory
void saveAlerts() {
  Preferences prefs;

  prefs.begin("tg_alerts", false);

  String data = "";

  for (int i = 0; i < alerts.size(); i++) {
    data += alerts[i].icaoType + ",";
    data += alerts[i].registration + ",";
    data += categoryToStringSimple(alerts[i].category) + ",";
    data += String(alerts[i].squawk);
    data += "\n";
  }

  prefs.putString("list", data);
  prefs.end();
}

/// @brief Clears your alerts
void clearAlerts() { alerts.clear(); }

/// @brief Loads your alerts from ESP32's flash memory
void loadAlerts() {
  Preferences prefs;
  prefs.begin("tg_alerts", true);

  clearAlerts();

  String data = prefs.getString("list", "");
  if(data == "") {
    prefs.end();
    return;
  }
  for(String line : splitCommand(data, '\n')) {
    AircraftData aircraft;
    std::vector<String> data = splitCommand(line, ',');
    aircraft.icaoType = data[0];
    aircraft.registration = data[1];
    aircraft.category = stringToCategory(data[2]);
    aircraft.squawk = data[3].toInt();
    alerts.push_back(aircraft);
  }

  saveAlerts();
  prefs.end();
}

/// @brief Loads alerts from the template
void fillAlertsFromTemplate() {
  alerts = alertsTemplate;
}