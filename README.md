# Dual ESP8266 Traffic Light Control System

This project implements a traffic light control system for intersections using two ESP8266 microcontrollers. The system can handle both T-junctions and four-way intersections, with one ESP8266 acting as the master controller and the other as a slave.

## System Overview

- **Master ESP8266**: Controls the traffic lights for North and West directions
- **Slave ESP8266**: Controls the traffic lights for South and East directions
- Communication between the two ESP8266s is handled via HTTP requests
- Configurable timing for green (30 seconds) and yellow (3 seconds) signals

## Hardware Requirements

- 2× ESP8266 development boards
- 12× LEDs (Red, Yellow, and Green for each direction)
- Appropriate resistors for LEDs
- Power supply for both ESP8266 boards
- WiFi router/network

### Pin Configuration (for each ESP8266)

- D1: First direction Green
- D2: First direction Yellow
- D3: First direction Red
- D4: Second direction Green
- D5: Second direction Yellow
- D6: Second direction Red

## Software Setup

1. Install the following Arduino libraries:
   - ESP8266WiFi
   - ESP8266WebServer (for slave)
   - ESP8266HTTPClient (for master)
   - ArduinoJson

2. Configure the WiFi settings:
   - Open both `.ino` files
   - Replace `YOUR_WIFI_SSID` with your WiFi network name
   - Replace `YOUR_WIFI_PASSWORD` with your WiFi password

3. Set up the slave ESP8266:
   - Upload the `slave_esp8266.ino` sketch
   - Note the IP address printed to Serial Monitor

4. Set up the master ESP8266:
   - Update the `slave_ip` variable with the IP address from step 3
   - Upload the `master_esp8266.ino` sketch

## Features

- Synchronized traffic light control across two ESP8266s
- Four-phase traffic light cycle
- Support for both T-junctions and four-way intersections
- Configurable timing for different traffic conditions
- HTTP-based communication between controllers

## Traffic Light Phases

1. **Phase 0**: North-South Green, East-West Red
2. **Phase 1**: North-South Yellow, East-West Red
3. **Phase 2**: North-South Red, East-West Green
4. **Phase 3**: North-South Red, East-West Yellow

## Future Improvements

- Add traffic sensors for dynamic timing adjustment
- Implement emergency vehicle priority
- Add pedestrian crossing signals
- Web interface for monitoring and configuration
- Add fault detection and reporting

## License

### MIT License
