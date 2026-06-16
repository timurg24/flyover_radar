# flyover_radar :satellite:
![ESP32](https://img.shields.io/badge/ESP32-supported-blue)
![Telegram](https://img.shields.io/badge/Telegram-bot%20alerts-blue)
![Status](https://img.shields.io/badge/status-active%20development-brightgreen)

Are you tired of missing out on planespotting cool airplanes? Me too! After missing out on one too many Chinooks and Poseidons, I decided to build something that alerts me when a unique airplane is approaching.

You can control and recieve your aircraft alerts via Telegram!

# Requirements
- Yourself
- ESP32 with WiFi
- Time
- All of the libraries installed (just install every single library available until the errors go away)
- OpenSky API keys
- Telegram

# Usage Instructions
- Fill out all of the config values in `env.example.cpp` with your data.
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
- HexDB returning incorrect ICAO type codes for brand new aircraft (registration should still be correct).
- When something refuses to connect, just restart the ESP (maybe even a couple of times until the errors go away).
