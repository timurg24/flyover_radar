# flyover_radar :satellite:
Are you tired of missing out on planespotting cool airplanes? Me too! I've missed one too many Chinooks and Stratotankers so I built this software to alert me when a cool airplane is approaching.

You can change the definition of a cool airplane in the `env.example.cpp` file!

# Requirements
- Yourself
- ESP32 with WiFi
- Time
- All of the libraries installed (just install every single library available until the errors go away)
- Computer
- Brain

# Usage Instructions
- Fill out all of the config values in `env.example.cpp` with your data
- Upload to ESP32

# Telegram Usage
- Send `List` to view your alerts
- `Reset` to reset your alerts
- `New` followed by (to create a new alert)
    - `type`
    - `registration` or `reg`
    - `category` or `cat`
    - `squawk` or `s`
    - and then your trigger (like HighPerformance or N123VV)
- `Load template` to load from the template of alerts
- `Delete` followed by the trigger deletes that alert

# Known Issues
- HexDB (ICAO Lookup database) can sometimes not recognize aircraft, resulting in `ICAO DB Request Fail [404] : Aircraft not found.` General Aviation aircraft are the most affected.
- HexDB returning incorrect ICAO type codes for brand new aircraft (registration should still be correct)
- When something refuses to connect, just restart the ESP (always works for me)
