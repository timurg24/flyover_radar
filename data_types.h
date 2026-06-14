#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>

struct LocationBounds {
  float lamin, lamax;
  float lomin, lomax;
};

// TODO: Expand for more alert options
struct AircraftData {
  String icaoType      = "";
  String registration  = "";
  String country       = "";
};

#endif
