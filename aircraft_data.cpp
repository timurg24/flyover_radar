#include "ArduinoJson/Deserialization/DeserializationError.hpp"
#include "aircraft_data.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

String openSkyToken = "";

bool refreshOpenSkyToken() {
  Serial.print("\nASVR Token Gen. ");
  if(!WiFi.isConnected()) return false;
  HTTPClient http;

  http.begin("https://auth.opensky-network.org/auth/realms/opensky-network/protocol/openid-connect/token");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = 
    "grant_type=client_credentials"
    "&client_id=" + String(clientID) +
    "&client_secret=" + String(clientSecret);

  int httpCode = http.POST(body);
  
  if(httpCode <= 0) {
    Serial.print("FAIL (Request failed)\n");
    http.end();
    return false;
  }

  String response = http.getString();
  http.end();

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, response);

  if(error) {
    Serial.print("FAIL (Failed to parse JSON)\n");
    return false;
  }

  const char* accessToken = doc["access_token"];

  if(!accessToken) {
    Serial.print("FAIL (No access token found)\n");
    return false;
  }

  openSkyToken = String(accessToken);
  Serial.print("OK\n");
  return true;
}

bool ensureOpenSkyToken() {
  if (openSkyToken.length() == 0) {
    return refreshOpenSkyToken();
  }

  return true;
}

// Returns the URL for the GET call within the desired bounds
String getRequestString(LocationBounds location) {
  String base = "https://opensky-network.org/api";
  base += "/states/all?";
  base += "lamin=" + String(location.lamin, 6) + "&";
  base += "lomin=" + String(location.lomin, 6) + "&";
  base += "lamax=" + String(location.lamax, 6) + "&";
  base += "lomax=" + String(location.lomax, 6);
  return base;
}

// Hexdb.io
AircraftData getDataFromICAO(String icao) {
  AircraftData aircraftData{};
  HTTPClient http;

  String hexdb = "https://hexdb.io/api/v1/aircraft/" + icao;
  http.setTimeout(20000);
  http.setReuse(false);
  http.begin(hexdb);

  int responseCode = http.GET();

  if (responseCode <= 0) {
    Serial.print("\nHexDB connection error: ");
    Serial.println(http.errorToString(responseCode));
    http.end();
    return aircraftData;
  }

  String payload = http.getString();

  if (payload.length() == 0) {
    Serial.print("\nHexDB empty payload. HTTP code: ");
    Serial.println(responseCode);
    http.end();
    return aircraftData;
  }

  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if(responseCode == 200) { // success

    if (!doc["Registration"].isNull()) {
      aircraftData.registration = doc["Registration"].as<String>();
      aircraftData.icaoType = doc["ICAOTypeCode"].as<String>();
      Serial.print("\n    Registration: ");
      Serial.print(aircraftData.registration);
      Serial.print(" ICAO: ");
      Serial.print(aircraftData.icaoType);
    }

  } else if(responseCode == 404) {
    Serial.print("\n    ICAO BD Request Fail [404] : ");
    Serial.print(doc["error"].as<String>());
    Serial.print(" (");
    Serial.print(icao);
    Serial.print(")");
  } else if(responseCode == 429) {
    Serial.print("\n    ICAO BD Request Fail [429] : ");
    Serial.print(doc["error"].as<String>());
    Serial.print(" (");
    Serial.print(icao);
    Serial.println(")");
  } else {
    Serial.print("\n\tICAO BD HTTP Error: ");
    Serial.println(http.errorToString(responseCode));
  }

  http.end();
  return aircraftData;
}

// OpenSky
void getAircraftData(int& count, AircraftData data[]) {
  if(WiFi.status() == WL_CONNECTED) {
    
    if (!ensureOpenSkyToken()) {
      Serial.println("ASVR FAILURE\nReason: Could not get OpenSky token.");
      return;
    }

    HTTPClient http;


    http.begin(getRequestString(bounds));
    http.addHeader("Authorization", "Bearer " + openSkyToken);

    int responseCode = http.GET();
    if(responseCode == 200) {
      Serial.println();
      Serial.print("ASVR OK [");
      Serial.print(responseCode);

      String payload = http.getString();
      DynamicJsonDocument doc(16384);

      DeserializationError error = deserializeJson(doc, payload);
      if(error) {
        Serial.print("JSON Parse failure: ");
        Serial.println(error.c_str());
        return;
      }

      Serial.print("] UNIX Epoch: ");
      Serial.print(doc["time"].as<long>());

      JsonArray states = doc["states"].as<JsonArray>();
      int i = 0;
      for (JsonArray state : states) {
          String icao = state[0].as<String>();
          data[i] = getDataFromICAO(icao);
          data[i].category = static_cast<AircraftCategory>(state[17].as<int>());
          if(!state[14].isNull()) {
            data[i].squawk = state[14].as<int>();
          }
          i++;
      }
      count = i;

    }
    else if (responseCode == 401) {
      Serial.print("\nASVR Failure [401] Token expired or invalid. Refreshing token...");

      http.end();

      refreshOpenSkyToken();
      ensureOpenSkyToken();

      return;
    }
    else if (responseCode == 429) {
      Serial.println("ASVR Failure [429] Too many requests / credits exhausted");
      Serial.println(http.getString());
    }
    http.end();
  } else {
    Serial.println("ASVR FAILURE\nReason: Not connected to WiFi.");
  }
}
