# ESP32 MQTT Temperature Monitor

An IoT system that reads temperature and humidity with a DHT22 sensor
and publishes the data in real time over MQTT.

## Technologies
- ESP32, C++ (Arduino framework)
- DHT22 sensor
- MQTT (HiveMQ public broker)
- Wokwi simulator

## How it works
Sensor -> ESP32 -> WiFi -> MQTT broker -> Dashboard

## Run it
1. Open the project in Wokwi: [PASTE YOUR WOKWI LINK HERE]
2. Press Play
3. Open the HiveMQ web client and subscribe to `emri123/iot/#`

## Topics
- `emri123/iot/temperature`
- `emri123/iot/humidity`

## Future improvements
- Alarm when temperature passes a threshold
- Dashboard with Node-RED
- Data storage and history charts
