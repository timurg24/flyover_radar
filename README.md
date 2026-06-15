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

# Known Issues
- HexDB (ICAO Lookup database) can sometimes not recognize aircraft, resulting in `ICAO DB Request Fail [404] : Aircraft not found.`
- HexDB returning incorrect ICAO type codes for brand new aircraft (registration should still be correct)
