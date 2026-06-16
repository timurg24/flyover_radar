#include "alert.h"

/// @brief Returns a string based on the aircraft category
/// @param cat AircraftCategory
/// @return String representation of the category
String categoryToString(AircraftCategory cat) {
  switch(cat) {
    case Undefined: return "Undefined"; break;
    case Unknown: return "Unknown"; break;
    case NoCat: return "No Category"; break;
    case Light: return "Light (<15,500lbs)"; break;
    case Small: return "Small (15,550lbs to 75,000lbs)"; break;
    case Large: return "Large (75,000lbs to 300,000lbs)"; break;
    case HighVortexLarge: return "High Vortex Large (Such as B757)"; break;
    case Heavy: return "Heavy (> 300,000lbs)"; break;
    case HighPerformance: return "High Performance (Fighter and Training Jets)"; break;
    case Rotorcraft: return "Rotorcraft"; break;
    case Glider: return "Gliders"; break;
    case LighterThanAir: return "Lighter-than-air"; break;
    case Parachutist: return "Parachutist/Skydiver"; break;
    case Ultralight: return "Ultralight"; break;
    case UAV: return "UAV"; break;
    case SpaceVehicle: return "Space/Trans-atmospheric Vehicle"; break;
    case EmergencyGroundVehicle: return "Emergency Ground Vehicle"; break;
    case ServiceGroundVehicle: return "Service Ground Vehicle"; break;
    case PointObstacle: return "Point Obstacle"; break;
    case ClusterObstacle: return "Cluster Obstacle"; break;
    case LineObstacle: return "Line Obstacle"; break;
    case USMilitary: return "United States Air Force"; break;
    default: return "Not set";
  }
}

/// @brief Returns a simplified string based on the aircraft category (like light, uav, or spacevehicle)
/// @param cat AircraftCategory
/// @return Simple string representation of aircraft category
String categoryToStringSimple(AircraftCategory cat) {
  switch (cat) {
      case Undefined: return "undefined";
      case Unknown: return "unknown";
      case NoCat: return "nocat";
      case Light: return "light";
      case Small: return "small";
      case Large: return "large";
      case HighVortexLarge: return "highvortexlarge";
      case Heavy: return "heavy";
      case HighPerformance: return "highperformance";
      case Rotorcraft: return "rotorcraft";
      case Glider: return "glider";
      case LighterThanAir: return "lighterthanair";
      case Parachutist: return "parachutist";
      case Ultralight: return "ultralight";
      case UAV: return "uav";
      case SpaceVehicle: return "spacevehicle";
      case EmergencyGroundVehicle: return "emergencygroundvehicle";
      case ServiceGroundVehicle: return "servicegroundvehicle";
      case PointObstacle: return "pointobstacle";
      case ClusterObstacle: return "clusterobstacle";
      case LineObstacle: return "lineobstacle";
      case USMilitary: return "usaf";
      default: return "unknown";
    }
}

/// @brief Returns the aircraft category based on a string
/// @param cat String category
/// @return Aircraft Category
AircraftCategory stringToCategory(const String& cat) {
  String value = cat;
  value.toLowerCase(); // then why even have const string&???
  if (value == "undefined") return Undefined;
  else if (value == "unknown") return Unknown;
  else if (value == "no category" || value == "nocat") return NoCat;
  else if (value == "light") return Light;
  else if (value == "small") return Small;
  else if (value == "large") return Large;
  else if (value == "high vortex large" || value == "highvortexlarge") return HighVortexLarge;
  else if (value == "heavy") return Heavy;
  else if (value == "high performance" || value == "highperformance") return HighPerformance;
  else if (value == "rotorcraft") return Rotorcraft;
  else if (value == "glider" || value == "gliders") return Glider;
  else if (value == "lighter-than-air" || value == "lighter than air" || value == "lighterthanair") return LighterThanAir;
  else if (value == "parachutist" || value == "skydiver" || value == "parachutist/skydiver") return Parachutist;
  else if (value == "ultralight") return Ultralight;
  else if (value == "uav") return UAV;
  else if (value == "space vehicle" || value == "spacevehicle" || value == "space/trans-atmospheric vehicle") return SpaceVehicle;
  else if (value == "emergency ground vehicle" || value == "emergencygroundvehicle") return EmergencyGroundVehicle;
  else if (value == "service ground vehicle" || value == "servicegroundvehicle") return ServiceGroundVehicle;
  else if (value == "point obstacle" || value == "pointobstacle") return PointObstacle;
  else if (value == "cluster obstacle" || value == "clusterobstacle") return ClusterObstacle;
  else if (value == "line obstacle" || value == "lineobstacle") return LineObstacle;
  else if (value == "united states air force" || value == "us military" || value == "usmilitary" || value == "usaf" || value == "military") return USMilitary;
  return Unknown;
}