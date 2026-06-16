#include "env.h"
#include "data_types.h"
#include "aircraft_data.h"
#include "alert.h"

/*
  Flyover Radar v1.0.0
  Copyright MMXXVI Timur Gabdrakhmanov. GPL-3.0 license.

  A sketch that allows you to get notifications about certain aircraft that will fly over your house.
  Aircraft alerts can be configured inside the ENV CPP file and notifications are
  sent via Telegram bot.
*/

// Aircraft
int aircraftCount = 0;
AircraftData aircraft[512];

// =====================
//        Code
// =====================


void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.print("\n\n\n");
  Serial.print(R"banner(
  ███████╗██╗  ██╗   ██╗ ██████╗ ██╗   ██╗███████╗██████╗ 
  ██╔════╝██║  ╚██╗ ██╔╝██╔═══██╗██║   ██║██╔════╝██╔══██╗
  █████╗  ██║   ╚████╔╝ ██║   ██║██║   ██║█████╗  ██████╔╝
  ██╔══╝  ██║    ╚██╔╝  ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
  ██║     ███████╗██║   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
  ╚═╝     ╚══════╝╚═╝    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝
                                                          
  ██████╗  █████╗ ██████╗  █████╗ ██████╗                 
  ██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔══██╗                
  ██████╔╝███████║██║  ██║███████║██████╔╝                
  ██╔══██╗██╔══██║██║  ██║██╔══██║██╔══██╗                
  ██║  ██║██║  ██║██████╔╝██║  ██║██║  ██║                
  ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝            
  )banner");
  Serial.println("Copyright MMXXVI Timur Gabdrakhmanov. GPL-3.0 license.");

  //===========
  // WiFi setup
  //===========
  WiFi.begin(wifiName, wifiPassword);
  Serial.print("Connecting to WiFi");

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("OK");

  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

  setupAlerts();
}

unsigned long lastOpenSkyCheck = 0;

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - lastOpenSkyCheck >= openSkyInterval) {
        lastOpenSkyCheck = currentMillis;

        getAircraftData(aircraftCount, aircraft);
        compareAlerts(aircraftCount, aircraft, alerts);
    }
}
