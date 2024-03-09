# arduino_esp_mini
This Arduino Mini project gathers data from DHT22 (temperature/humidity), soil moisture, and BH1750 (light intensity) sensors. Utilizing an ESP8266 module, data is sent via Wi-Fi to ThingSpeak IoT. Ideal for environmental monitoring, it enables remote analysis for informed decisions.

## Getting Started

### Prerequisites

- Arduino IDE (Download and Install from [Arduino Official Website](https://www.arduino.cc/en/Main/Software))
- Arduino board (e.g., Arduino Uno)
- ESP8266 Wi-Fi Module
- DHT22 Temperature and Humidity Sensor
- Soil Moisture Sensor
- BH1750 Light Sensor
- Jumper Wires
- LEDs, Fans, and other relevant components

### Hardware Setup

1. Connect the DHT22 sensor, soil moisture sensor, and BH1750 sensor to the appropriate pins on your Arduino board. Refer to the comments in the code for pin assignments.

2. Connect LEDs, Fans, or other devices you want to control based on sensor data. Make sure to connect them to the correct pins as defined in the code.

3. Connect the RX and TX pins of the ESP8266 module to the Arduino's TX and RX pins, respectively.

### Installing Libraries

This sketch uses several libraries to interface with the sensors, Wi-Fi module, and communicate with ThingSpeak. To install the required libraries:

1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries**.
3. Search for and install the following libraries:
   - DHT Sensor Library
   - BH1750 Library
   - SoftwareSerial Library

## Configuration

Before uploading the sketch, you need to configure the following settings:

- Replace `AP` with your Wi-Fi network name (SSID).
- Replace `PASS` with your Wi-Fi password.
- Replace `API` with your ThingSpeak API key.
- Ensure the pin assignments match your hardware setup, or modify them as needed.

## Usage

1. Upload the sketch to your Arduino board using the Arduino IDE.
2. Open the Serial Monitor to see the sensor readings and control actions.
3. The code will read sensor data, control LEDs and fans based on conditions, and upload data to ThingSpeak.
4. Monitor the ThingSpeak channel associated with your API key to view and analyze the collected data.

## Contributions

Contributions are welcome! If you find any issues or want to enhance the functionality of this code, feel free to create pull requests.
