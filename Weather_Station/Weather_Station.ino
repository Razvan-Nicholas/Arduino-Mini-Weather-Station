#include "SparkFun_Qwiic_OLED.h" //http://librarymanager/All#SparkFun_Qwiic_OLED
#include "DHT.h"
#define DHTPIN 2          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22     // DHT 22  (AM2302), AM2321 //#define DHTTYPE DHT11   // DHT 11 //#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.
QwiicNarrowOLED myOLED;
void setup()
{
    Serial.begin(115200);
    Serial.println("Running OLED example");
    dht.begin();
    Wire.begin();

    // Initalize the OLED device and related graphics system
    if (myOLED.begin() == false)
    {
        Serial.println("Device begin failed. Freezing...");
        while (true)
            ;
    }
    Serial.println("Begin success");
}
void loop()
{
      // Reading temperature or humidity takes about 250 milliseconds!
    float h = dht.readHumidity();
    float t = dht.readTemperature();        // Read temperature as Celsius (the default)
    float f = dht.readTemperature(true);    // Read temperature as Fahrenheit (isFahrenheit = true)

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    float hif = dht.computeHeatIndex(f, h);           // Compute heat index in Fahrenheit (the default)
    float hic = dht.computeHeatIndex(t, h, false);    // Compute heat index in Celsius (isFahreheit = false)
    // Fill a rectangle on the screen that has a 4 pixel board
    myOLED.rectangleFill(0, 0, myOLED.getWidth(), myOLED.getHeight());
    String temp =  String(hic) +  " C";
    String hum  =  String(h)   +  " %"; 
    // Center our message on the screen. Get the screen size of the "hello" string,    // calling the getStringWidth() and getStringHeight() methods on the oled
    int x1 = (myOLED.getWidth()  - myOLED.getStringWidth(temp))  / 2;     // starting x position - screen width  minus string width  / 2
    int y1 = (myOLED.getHeight() - myOLED.getStringHeight(temp)) / 2;     // starting y position - screen height minus string height / 2 
    myOLED.text(x1, y1+10, hum, 0);    // Draw the text - color of black (0)
    myOLED.text(x1, y1-10, temp,0);    // Draw the text - color of black (0)
    myOLED.display();                   // There's nothing on the screen yet - Now send the graphics to the device
}
