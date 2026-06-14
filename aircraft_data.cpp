#include "aircraft_data.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

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
  http.setTimeout(20000);        // 20 seconds instead of default timeout
  http.setReuse(false);
  http.begin(hexdb);

  int responseCode = http.GET();
    
  if(responseCode == 200) {
    String payload = http.getString();
    StaticJsonDocument<2048> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("JSON Parse failure: ");
      Serial.println(error.c_str());
      http.end();
      return aircraftData;
    }

    if (!doc["Registration"].isNull()) {
      aircraftData.registration = doc["Registration"].as<String>();
      aircraftData.icaoType = doc["ICAOTypeCode"].as<String>();
    }

  } else if(responseCode == 404) {
    Serial.println("ICAO BD Request : 404");
    // Serial.println(doc["message"].as<String>());
  } else if(responseCode == 429) {
    Serial.println("ICAO BD Request : 429");
    // Serial.println(doc["message"].as<String>());
  } else {
    Serial.print("ICAO BD HTTP Error: ");
    Serial.println(http.errorToString(responseCode));
  }

  http.end();
  return aircraftData;
}

// OpenSky
void getAircraftData(int& count, AircraftData data[]) {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(getRequestString(bounds));
    http.setAuthorization(clientID, clientSecret);

    int responseCode = http.GET();
    
    if(responseCode > 0) {
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
          i++;
      }
      count = i;
      Serial.print(". Aircraft Count: ");
      Serial.print(count);

    } else {
      Serial.print("ASVR Failure\nGET Response Code: ");
      Serial.println(responseCode);
      Serial.print("HTTP Error: ");
      Serial.println(http.errorToString(responseCode));
    }
    http.end();
  } else {
    Serial.println("ASVR FAILURE\nReason: Not connected to WiFi.");
  }
}
