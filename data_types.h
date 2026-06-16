#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>

struct LocationBounds {
  float lamin, lamax;
  float lomin, lomax;
};

enum AircraftCategory : int {
  Undefined = -1,
  Unknown = 0,
  NoCat = 1,
  Light = 2,
  Small = 3,
  Large = 4,
  HighVortexLarge = 5,
  Heavy = 6,
  HighPerformance = 7,
  Rotorcraft = 8,
  Glider = 9,
  LighterThanAir = 10,
  Parachutist = 11,
  Ultralight = 12,
  UAV = 14,
  SpaceVehicle = 15,
  EmergencyGroundVehicle = 16,
  ServiceGroundVehicle = 17,
  PointObstacle = 18,
  ClusterObstacle = 19,
  LineObstacle = 20,

  USMilitary = 40
};

struct AircraftData {
  String icaoType           = "";
  String registration       = "";
  AircraftCategory category = Undefined;
  int squawk                = -1;
};

#endif