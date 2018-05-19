
//Headers
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHTesp.h"

// Definition of the pin
#define OLED_CLK 18 //Pin 18 is the clock 
#define OLED_MOSI 23// Pin 23 is MOSI
#define OLED_CS 2// Pin 2 is the chip select
#define OLED_DC 25// Pin 25 is the DC pin
#define OLED_RESET 'RST' // Pin RST is the reset pin

//Blynk app definition
#define BLYNK_PRINT Serial

Adafruit_SSD1305 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);// start of the ssd1305 oled monochrome display


const char* ssid       = "dlink1";// Network name
const char* password   = "130EB75B45";//Network password

char auth[] = "06ec4fbf293e4ed0ba54d3dd0d4b81bc";//token for the Blynk App

#define PIN_UPTIME V5 // Blynk Virtual pin V5
#define PIN_UPTIME V0 // Blynk Virtual pin V0
#define PIN_UPTIME V1 // Blynk Virtual pin V1
 



DHTesp dht;//DH test

void setup() {
  Serial.begin(115200);//Begin
  Blynk.begin(auth, ssid, password);//Start Blynk App
  Serial.println();//Prints data to the serial port
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");//Prints data to the serial port
  
  dht.setup(4); // Connect DHT sensor to GPIO 4
  display.begin();//Initializes the interface to the oled screen

// Start connections to WIFI
    Serial.print("Connecting to ");//Prints data to the serial port
    Serial.println(ssid);//Prints data to the serial port

    WiFi.begin(ssid, password);//Start the connection

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");//Prints data to the serial port
    }

    Serial.println("");//Prints data to the serial port
    Serial.println("WiFi connected.");//Prints WiFi connected to the serial port
    Serial.println("IP address: ");//Prints IP address to the serial port
    Serial.println(WiFi.localIP());//Prints data to the serial port

   
   
}

void loop(){
  
 delay(2000);//delay for 2 seconds

 display.clearDisplay();// clears the oled display 



float converted = 0.00; // define float variable converted.
float humidity = dht.getHumidity();// define float variable humidity
float temperature = dht.getTemperature();// define float variable temperature
converted = ( temperature * 1.8 ) + 32;// definition of converted to find Fahrenheit
float sensor1= dht.getHumidity();// define float sensor1 temperature


#ifdef USE_FAHRENHEIT
  float hi = dht.computeHeatIndex(temperature, humidity, true);
#else
  float hi = dht.computeHeatIndex(temperature, humidity, false);
#endif

  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);//Prints data to the serial port
  Serial.print("\t\t");//Prints data to the serial port
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);//Prints data to the serial port
Serial.print("Celsius = ");//Prints Celsius to the serial port
Serial.println(temperature);//Prints the temperature to the serial port



  
Serial.print("Humidity = ");//Prints Humidity = to the serial port
Serial.println(humidity);//Prints the humidity to the serial port


Serial.print("Fahrenheit = ");//Prints Fahrenheit = to the serial port
Serial.println(converted);//Prints the Fahrenheit temperature to the serial port


display.setCursor(12, 13);//specify where on the display we're going to display the text.
display.println(converted);//displays the Fahrenheit temperature to the oled display
display.setCursor(45, 13);//specify where on the display we're going to display the text.
 display.println("*F");//displays the *F to the oled display
display.display(); // tell the display to...display


display.display();// tell the display to...display
display.setTextColor(WHITE);// Set the color of the Text
display.setCursor(20,1);//specify where on the display we're going to display the text.
display.setTextSize(1);//set the size of the text
display.println("Temp");//displays the Temp to the oled display
display.drawRoundRect(0, 0, 63, 30, 8, WHITE);// draws a round rectangle at X=0, Y=0, width = 63,height 30, corner radius = 8, color white

 

  

   
display.display();// tell the display to...display
display.setTextColor(WHITE);// Set the color of the Text
display.setCursor(70,1);//specify where on the display we're going to display the text.
display.setTextSize(1);//set the size of the text
display.println("HeatIndex");//displays the HeatIndex to the oled display
display.drawRoundRect(64, 0, 63, 30, 8, WHITE);// draws a round rectangle at X=64, Y=0, width = 63,height 30, corner radius = 8, color white
display.setCursor(75,13);//specify where on the display we're going to display the text.
display.println(hi);//displays the heat index to the oled display 
display.setCursor(107,13);//specify where on the display we're going to display the text.
display.println("*C");//displays the *C to the oled display
display.display(); //tell the display to...display


display.setCursor(12,45);//specify where on the display we're going to display the text.
display.println(temperature);//displays the Celsius temperature to the oled display
display.setCursor(45,45);//specify where on the display we're going to display the text.
display.println("*C");//displays the *C to the oled display
display.display(); // tell the display to...display
display.display();//tell the display to...display
display.setTextColor(WHITE);// Set the color of the Text
display.setCursor(20,34);//specify where on the display we're going to display the text.
display.setTextSize(1);//set the size of the text
display.println("Temp");//displays the Temp to the oled display
display.drawRoundRect(0,32, 63, 30, 8, WHITE);// draws a round rectangle at X=0, Y=32, width = 63,height 30, corner radius = 8, color white


 
display.setCursor(80,47);//specify where on the display we're going to display the text.
display.println(sensor1);
display.setCursor(112,47);//specify where on the display we're going to display the text.
display.println("%");//displays % to the oled display
display.display(); //you have to tell the display to...display
display.display();//you have to tell the display to...display
display.setTextColor(WHITE);// Set the color of the Text
display.setCursor(73,34);//specify where on the display we're going to display the text.
display.setTextSize(1);// Set the color of the Text
display.println("Humidity");//displays Humidity to the oled display
display.drawRoundRect(64,32, 63, 30, 8, WHITE);// draws a round rectangle at X=64, Y=32, width = 63,height 30, corner radius = 8, color white
display.display();//you have to tell the display to...display
display.setTextColor(WHITE);// Set the color of the Text
display.setCursor(73,34);//specify where on the display we're going to display the text.
display.setTextSize(1);// Set the color of the Text
display.println("Humidity");//displays Humidity to the oled display
display.drawRoundRect(64, 32, 63, 30, 8, WHITE);// draws a round rectangle at X=64, Y=32, width = 63,height 30, corner radius = 8, color white

{
 Blynk.run();// Run Blynk app
 Blynk.virtualWrite(V5, hi);//Send the heat index data to virtual pin V5
 Blynk.virtualWrite(V0, converted);//Send the Fahrenheit Temperature data to virtual pin V0
 Blynk.virtualWrite(V1, sensor1);//Send the Humidity data to virtual pin V1
}
}


