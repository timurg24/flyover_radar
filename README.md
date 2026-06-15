# flyover_radar
Are you tired of missing out on planespotting cool airplanes? Me too! I've missed one too many Chinooks and Stratotankers so I built this software to alert me when a cool airplane is approaching.

You can change the definition of a cool airplane in the `env.example.cpp` file!

# Requirements
- Yourself
- ESP32 with WiFi
- Time
- All of the libraries installed (just install every single library available until the errors go away)
- Computer
- Brain

# Config
Everything needs to be configured inside `env.example.cpp` (or your own `.cpp` file with the exact same variables).

# Aircraft Categories (use Enum AircraftCategory)
0 = No information at all

1 = No ADS-B Emitter Category Information

2 = Light (< 15500 lbs)

3 = Small (15500 to 75000 lbs)

4 = Large (75000 to 300000 lbs)

5 = High Vortex Large (aircraft such as B-757)

6 = Heavy (> 300000 lbs)

7 = High Performance (> 5g acceleration and 400 kts)

8 = Rotorcraft

9 = Glider / sailplane

10 = Lighter-than-air

11 = Parachutist / Skydiver

12 = Ultralight / hang-glider / paraglider

14 = Unmanned Aerial Vehicle

15 = Space / Trans-atmospheric vehicle

16 = Surface Vehicle – Emergency Vehicle

17 = Surface Vehicle – Service Vehicle

18 = Point Obstacle (includes tethered balloons)

19 = Cluster Obstacle

40 = United States Air Force

20 = Line Obstacle
