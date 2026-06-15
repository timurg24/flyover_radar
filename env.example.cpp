#include "env.h"
#include <math.h>

// =====================
//   Config and Values
// =====================

// WiFi
const char* wifiName = "WIFI NAME HERE!!";
const char* wifiPassword = "super cool password";

// OpenSky
const char* clientID = "OpenSky Client ID goes here";
const char* clientSecret = "is the secret in the room with us";
int openSkyInterval = 30000;

// Telegram
const char* telegramBotID = "bot id";
int64_t  telegramChatID = 123;

// Location
// Change only this VVVV
#define HOME_LAT 46.97313
#define HOME_LON 7.94648
#define BOX_RADIUS_MILES 3.0

// Do not change VV

#define MILES_PER_LAT_DEGREE 69.0
#define DEG_TO_RAD 0.017453292519943295

#define LAT_DELTA (BOX_RADIUS_MILES / MILES_PER_LAT_DEGREE)
#define LON_DELTA (BOX_RADIUS_MILES / (MILES_PER_LAT_DEGREE * cos(HOME_LAT * DEG_TO_RAD)))

LocationBounds bounds = {
  HOME_LAT - LAT_DELTA,  // lamin - minimum latitude, bottom
  HOME_LAT + LAT_DELTA,  // lamax - maximum latitude, top
  HOME_LON - LON_DELTA,  // lomin - minimum longitude, left
  HOME_LON + LON_DELTA   // lomax - maximum longitude, right
};

// Do not change ^^

// Web interface
int interfacePort = 24001;

// Alerts
AircraftData alerts[] = {
  // Aircraft Types
  {"a310"}, {"an12"}, {"a124"}, {"a148"}, {"an26"}, {"an32"}, {"v22"}, {"b742"}, {"b743"}, {"b74s"}, {"b52"}, {"c135"}, {"c17"}, {"blcf"}, {"e3tf"}, {"e6"}, {"k35r"}, {"p8"}, {"r135"}, {"dc3"},
  {"eufi"}, {"f16"}, {"il62"}, {"il76"}, {"il96"}, {"c5m"}, {"c130"}, {"c130j"}, {"f22"}, {"f35"}, {"p3"}, {"u2"}, {"dc10"}, {"f15"}, {"f18"}, {"md11"}, {"md81"},{"md82"},{"md83"},{"md87"},{"md88"},
  {"md90"},{"hawk"},{"t38"},{"p51"}, {"su95"}, {"t154"}, {"b1"},
  // Registrations
  // Unfortunately, I haven't gotten a single FR24 alert about these aircraft except N859NA. If any of these trigger above your house, tell me!
  {.registration = "n859na"}, {.registration = "n993sf"}, {.registration = "n936ca"}, {.registration = "n7501v"}, {.registration = "n749cf"},
  // Category
  {.category = 15}, {.category = 7}
  // TODO: Add support for military alerts (but that is prob handled by the military aircraft icao types)
};
int alertCount = sizeof(alerts) / sizeof(alerts[0]);
