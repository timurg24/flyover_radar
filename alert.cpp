#include "alert.h"
#include "env.h"

#include <WiFiClientSecure.h>
#include <AsyncTelegram2.h>

WiFiClientSecure client;
AsyncTelegram2 bot(client);

void setupAlerts() {
  client.setInsecure();

  bot.setUpdateTime(1000);
  bot.setTelegramToken(telegramBotID);

  if(bot.begin()) {
    Serial.println("Telegram Bot OK");
  } else Serial.println("Telegram Bot FAIL");
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
      bool registrationMatch =
        aircraft[i].registration.length() > 0 &&
        alertAircraft[j].registration.length() > 0 &&
        aircraft[i].registration == alertAircraft[j].registration;

      bool typeMatch =
        aircraft[i].icaoType.length() > 0 &&
        alertAircraft[j].icaoType.length() > 0 &&
        aircraft[i].icaoType == alertAircraft[j].icaoType;

      if (registrationMatch || typeMatch) {
        sendAlert(aircraft[i]);
        Serial.print("\t> Aircraft Alert Sent: ");
        Serial.print(aircraft[i].registration);
        break; // prevents sending multiple alerts for same aircraft
      }
    }
  }
}
