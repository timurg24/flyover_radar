#include "alert.h"
#include "env.h"

#include <WiFiClientSecure.h>
#include <vector>



WiFiClientSecure client;
AsyncTelegram2 bot(client);


/// @brief Splits a command by a delimeter
/// @param original Source string
/// @param delimeter Character used to split the original string
/// @return Vector
std::vector<String> splitCommand(const String& original, char delimeter) {
  std::vector<String> result;
  String acc;
  for(char c : original) {
    if(c == delimeter) {
      result.push_back(acc);
      acc.clear();
    } else acc += c;
  }
  result.push_back(acc);
  return result;
}

/// @brief Checks if the registration is USAF
/// @param registration Registration
/// @return True if USAF
bool isMilitaryReg(const String& registration) {
  if (registration.length() < 3) {
    return false;
  }

  return isDigit(registration[0]) &&
         isDigit(registration[1]) &&
         registration[2] == '-';
}

/// @brief Setups Telegram bot
void setupAlerts() {
  Serial.print("Telegram Bot Auth ");
  client.setInsecure();

  bot.setUpdateTime(1000);
  bot.setTelegramToken(telegramBotID);

  if(bot.begin()) {
    Serial.print("OK");
  } else Serial.print("FAIL");
}

/// @brief Sends a Telegram alert containing aircraft information
/// @param data Aircraft data (contents used in message)
void sendAlert(AircraftData data) {
  client.setInsecure();
  String message = "Flight Alert\n";
  message += "ICAO: " + data.icaoType;
  message += "\nRegistration: " + data.registration;
  message += "\nCategory: " + categoryToString(data.category);
  message += "\nSquawk: " + String(data.squawk);
  bot.sendTo(telegramChatID, message);
}




/// @brief Sends a pretty list of all of the alerts
/// @param msg Telegram message
void sendListOfAlerts(TBMessage msg) {
  String message = "List of your alerts:\n";
  if(alerts.size() == 0) {
    bot.sendMessage(msg, String("There are no alerts set."));
    return;
  }
  for(int i = 0; i < alerts.size(); i++) {
    AircraftData& alert = alerts[i];
    message += String(i + 1);
    message += ". ";
    if(alert.icaoType.length() > 0) {
        message += "Type: ";
        message += alert.icaoType;
    } else if(alert.registration.length() > 0) {
      message += "Registration: ";
      message += alert.registration;
    } else if(alert.category != Undefined && alert.category != Unknown) {
      message += "Category: ";
      message += categoryToString(alert.category);
    } else {
      message += "Squawk: ";
      message += String(alert.squawk);
    }
    message += "\n";
  }
  bot.sendMessage(msg, message);
}

String joinFrom(const std::vector<String>& parts, int startIndex) {
  String result = "";

  for (int i = startIndex; i < parts.size(); i++) {
    if (i > startIndex) {
      result += " ";
    }

    result += parts[i];
  }

  return result;
}

unsigned long lastTelegramCheck = 0;
const unsigned long telegramCheckInterval = 1000;

/// @brief Checks Telegram and if user sends a command to act upon it
void handleTelegramMessage() {
  if(millis() - lastTelegramCheck < telegramCheckInterval) {
    return;
  }

  lastTelegramCheck = millis();

  TBMessage msg;

  if (bot.getNewMessage(msg)) {
      std::vector<String> message = splitCommand(msg.text, ' ');
      message[0].toLowerCase();

      if (message[0] == "list") {
          sendListOfAlerts(msg);
      } else if (message[0] == "new") {

        if(message.size() < 3) {
          bot.sendMessage(msg, "Usage: new type b762, new reg N123VV, squawk 7740, category high performance");
          return;
        }

        if(message[1] == "type") newAlert(msg, 0, message[2]);
        else if(message[1] == "registration" || message[1] == "reg") newAlert(msg, 1, message[2]);
        else if(message[1] == "category" || message[1] == "cat") newAlert(msg, 2, joinFrom(message, 2));
        else if(message[1] == "squawk" || message[1] == "s") newAlert(msg, 3,message[2]);

      } else if(message[0] == "delete") {
        deleteAlert(msg, message[1]);
      } else if (message[0] == "reset") {
        clearAlerts();
        bot.sendMessage(msg, "Reset your alerts.");
      } else if (message[0] == "load" && message[1] == "template") {
        fillAlertsFromTemplate();
        bot.sendMessage(msg, "Your alerts are filled with the template.");
      }
  }
}



void compareAlerts(int aircraftCount, AircraftData aircraft[]) {
  for(int i = 0; i < aircraftCount; i++) {
    for(int j = 0; j < alerts.size(); j++) {

      String aircraftRegistration = aircraft[i].registration;
      String alertRegistration = alerts[j].registration;

      String aircraftType = aircraft[i].icaoType;
      String alertType = alerts[j].icaoType;

      int aircraftCategory = aircraft[i].category;
      int alertCategory = alerts[j].category;

      int aircraftSquawk = aircraft[i].squawk;
      int alertSquawk = alerts[j].squawk;

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

      bool categoryMatch =
        aircraftCategory != Undefined &&
        aircraftCategory != Unknown &&
        alertCategory != Undefined &&
        alertCategory != Unknown &&
        aircraftCategory == alertCategory;
      
      bool squawkMatch =
        aircraftSquawk != -1 &&
        alertSquawk != -1 &&
        aircraftSquawk == alertSquawk;

      bool militaryMatch =
        isMilitaryReg(aircraftRegistration) &&
        aircraftCategory == USMilitary;

      bool alreadyAlerted = false;
      for(String reg : alertedRegistrations) {
        if (aircraftRegistration.length() > 0 && aircraftRegistration == reg) {
          alreadyAlerted = true;
          break;
        }
      }

      if (registrationMatch || typeMatch || categoryMatch || squawkMatch || militaryMatch) {
        if (!alreadyAlerted) {
          sendAlert(aircraft[i]);

          Serial.print(" (Alert Sent)");

          if (aircraftRegistration.length() > 0) {
            alertedRegistrations.push_back(aircraftRegistration);
          }

          break; // prevents sending multiple alerts for same aircraft
        }
      }
    }
  }
}