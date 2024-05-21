# Arduino Portable Weather Station using a DHT22 Temp/Humidity Sensor

![190e9f85-be47-4f23-a2a4-ac07462da537](https://github.com/Razvan-Nicholas/Arduino-Mini-Weather-Station/assets/129912215/43581265-c635-4c71-b3ff-b6512a833cba)

This project demonstrates how to use a DHT22 temperature and humidity sensor with an OLED display on an Arduino. The sensor data is read and displayed on the OLED screen. This project is useful for applications requiring environmental monitoring and display, such as indoor climate control systems.

## Table of Contents
- [Introduction](#introduction)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Circuit Diagram](#circuit-diagram)
- [Code Explanation](#code-explanation)
- [License](#license)

## Introduction
This project uses an Arduino to read temperature and humidity data from a DHT22 sensor and display the data on a Qwiic OLED display. The data is refreshed continuously, showing real-time environmental conditions.

## Hardware Requirements
- Arduino board (e.g., Uno, Mega, etc.)
- DHT22 sensor
- SparkFun Qwiic OLED display
- Jumper wires
- Breadboard (optional)

## Software Requirements
- Arduino IDE
- [SparkFun Qwiic OLED library](http://librarymanager/All#SparkFun_Qwiic_OLED)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)

## Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/DHT22_OLED_Arduino.git
   cd DHT22_OLED_Arduino
   ```

2. **Install the required libraries:**
   - Open Arduino IDE.
   - Go to `Sketch` -> `Include Library` -> `Manage Libraries...`.
   - Search for "SparkFun Qwiic OLED" and install it.
   - Search for "DHT sensor library" and install it.

3. **Upload the code:**
   - Connect your Arduino to the computer.
   - Open `DHT22_OLED_Arduino.ino` in Arduino IDE.
   - Select the correct board and port from `Tools` menu.
   - Click the `Upload` button.

## Usage
After uploading the code, the Arduino will start reading the temperature and humidity data from the DHT22 sensor and display it on the OLED screen. The data will be refreshed every few seconds.

## Circuit Diagram
![Circuit Diagram](circuit_diagram.png)

## Code Explanation
### Libraries and Definitions
```cpp
#include "SparkFun_Qwiic_OLED.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
QwiicNarrowOLED myOLED;
```
- Includes necessary libraries.
- Defines the pin and type for the DHT22 sensor.
- Initializes the DHT sensor and OLED display objects.

### Setup Function
```cpp
void setup()
{
    Serial.begin(115200);
    Serial.println("Running OLED example");
    dht.begin();
    Wire.begin();

    if (myOLED.begin() == false)
    {
        Serial.println("Device begin failed. Freezing...");
        while (true);
    }
    Serial.println("Begin success");
}
```
- Sets up serial communication and initializes the DHT sensor.
- Initializes the OLED display and checks for successful initialization.

### Loop Function
```cpp
void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println(F("Failed to read from DHT sensor!"));

        return;
    }

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    myOLED.rectangleFill(0, 0, myOLED.getWidth(), myOLED.getHeight());
    String temp =  String(hic) +  " C";
    String hum  =  String(h)   +  " %";

    int x1 = (myOLED.getWidth()  - myOLED.getStringWidth(temp))  / 2;
    int y1 = (myOLED.getHeight() - myOLED.getStringHeight(temp)) / 2;

    myOLED.text(x1, y1+10, hum, 0);
    myOLED.text(x1, y1-10, temp,0);
    myOLED.display();
}
```
- Reads temperature and humidity from the DHT22 sensor.
- Checks for reading errors.
- Computes heat index values.
- Updates and displays the readings on the OLED screen.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
