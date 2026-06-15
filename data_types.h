#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>

struct LocationBounds {
  float lamin, lamax;
  float lomin, lomax;
};

struct AircraftData {
  String icaoType      = "";
  String registration  = "";
  // String country       = "";
  int category;
  String squawk        = "";
};

#endif
