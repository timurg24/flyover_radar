#include "alert.h"
#include "env.h"

#include <WiFiClientSecure.h>
#include <AsyncTelegram2.h>

WiFiClientSecure client;
AsyncTelegram2 bot(client);

void setupAlerts() {
  Serial.print("Telegram Bot Auth ");
  client.setInsecure();

  bot.setUpdateTime(1000);
  bot.setTelegramToken(telegramBotID);

  if(bot.begin()) {
    Serial.println("OK");
  } else Serial.println("FAIL");
}

void sendAlert(AircraftData data) {
  client.setInsecure();
  String message = "Flight Alert\n";
  message += "ICAO: " + data.icaoType;
  message += "\nRegistration: " + data.registration;
  bot.sendTo(telegramChatID, message);
}

void compareAlerts(int aircraftCount, AircraftData aircraft[], int alertCount, AircraftData alertAircraft[]) {
  for(int i = 0; i < aircraftCount; i++) {
    for(int j = 0; j < alertCount; j++) {

      String aircraftRegistration = aircraft[i].registration;
      String alertRegistration = alertAircraft[j].registration;
      String aircraftType = aircraft[i].icaoType;
      String alertType = alertAircraft[j].icaoType;

      aircraftRegistration.toUpperCase();
      alertRegistration.toUpperCase();
      aircraftType.toUpperCase();
      alertType.toUpperCase();

      bool registrationMatch =
        aircraftRegistration.length() > 0 &&
        alertRegistration.length() > 0 &&
        aircraftRegistration == alertRegistration;

      bool typeMatch =
        aircraftType.length() > 0 &&
        alertType.length() > 0 &&
        aircraftType == alertType;

      if (registrationMatch || typeMatch) {
        sendAlert(aircraft[i]);
        Serial.print("\t> Aircraft Alert Sent: ");
        Serial.print(aircraft[i].registration);
        break; // prevents sending multiple alerts for same aircraft
      }
    }
  }
}
