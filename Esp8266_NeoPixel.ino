#include <time.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
=======
>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff
#include <WiFiUdp.h>

#include "FastLED.h"


#define FASTLED_ESP8266_DMA // better control for ESP8266 will output or RX pin requires fork https://github.com/coryking/FastLED
#define FASTLED_ALLOW_INTERRUPTS 0  // Reduce flickering

#define NUM_LEDS      300
<<<<<<< HEAD
#define DATA_PIN      04
=======
#define NeoPIN 14
#define DATA_PIN      05
>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff
//#define CLOCK_PIN     2
#define CHIPSET       WS2811
#define COLOR_ORDER   GRB
WiFiUDP port;
CRGB leds[NUM_LEDS];

<<<<<<< HEAD
#include "Secrets.h" //File with your creditionals for connection 
// it should contain the following -
// const char *ssid = "your-ssid";
// const char *password = "your-password";

ESP8266WebServer server ( 80 );

#define NeoPIN 04
//#define NUM_LEDS 8
=======
const char* sensor_name = "TEST_SENSOR_HOSTNAME";
const int udp_port = 7778;
>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff

int brightness = 189;
int point1 = 0;
int point2 = strip.numPixels();
String color = "#ffffff";
//String color = "#065de8";

int timezone = 3;
int dst = 0;
int wake = 0;


#include "Secrets.h" //File with your creditionals for connection 
// it should contain the following -
// const char *ssid = "your-ssid";
// const char *password = "your-password";

ESP8266WebServer server ( 80 );

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_GRB + NEO_KHZ400);

void setup ( void ) {

  Serial.begin ( 115200 );

  // ##############
  // NeoPixel start
  Serial.println();
  strip.setBrightness(brightness);
  strip.begin();
  strip.show();
  delay(50);
  Serial.println("NeoPixel started");

  // #########
  // Webserver
  WiFi.begin ( ssid, password );
  Serial.print ("ssid ");
  Serial.println (ssid);
  Serial.print ("password ");
  Serial.println (password);
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 5 );
    //Serial.print ( "." );
  }
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );
  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }
  // what to do with requests
  server.on ( "/", handleRoot );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "HTTP server started" );
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Time get");
<<<<<<< HEAD
  wake = 1;
  
=======


>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff

#ifdef CLOCK_PIN
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
#else
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
#endif

  // Initialize the UDP port
  port.begin(udp_port);
  Serial.println ( "Colormusic done" );

  setNeoColor(color, point1, point2);
  Serial.println ( "All white" );

  //################
  //OTA Update setup
  ArduinoOTA.onStart([]() {
    Serial.println("Start");  //  "Начало OTA-апдейта"
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");  //  "Завершение OTA-апдейта"
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    //  "Ошибка при аутентификации"
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    //  "Ошибка при начале OTA-апдейта"
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    //  "Ошибка при подключении"
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    //  "Ошибка при получении данных"
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    //  "Ошибка при завершении OTA-апдейта"
  });
  ArduinoOTA.begin();
  Serial.println("Ready");  //  "Готово"
  Serial.print("IP address: ");  //  "IP-адрес: "
  Serial.println(WiFi.localIP());
  
}

void loop ( void ) {
  // waiting for a client
  server.handleClient();
<<<<<<< HEAD
  // waiting for OTA
  ArduinoOTA.handle();
  //Checking alarm clock
  handletime();
  //Waiting for music signals
  handlecolormusic();
  
}

void handlecolormusic() {
  int packetSize = port.parsePacket();
  if (packetSize == sizeof(leds)) {
    port.read((char*)leds, sizeof(leds));
    //Serial.printf(".");
    FastLED.show();
    // flush the serial buffer
    while (Serial.available()) {
      Serial.read();
    }
  } else if (packetSize) {
    Serial.printf("Invalid packet size: %u (expected %u)\n", packetSize, sizeof(leds));
    port.flush();
    return;
  }
}

void handletime() {
=======
  
>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff
  time_t now;
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);
  if (timeinfo->tm_hour == 9 && timeinfo->tm_min >= 44 && timeinfo->tm_min <= 45) {
    wake = 1;
  }
  if (timeinfo->tm_hour == 9 && timeinfo->tm_min >= 45 && timeinfo->tm_min <= 59 && wake == 0 ) {
    
    int sun_speed = 1000;
    sunrise(sun_speed);
    delay(20000);
    sun_speed = 100;
    sunrise(sun_speed);
    int brightness = 255;
    int point1 = 0;
    int point2 = strip.numPixels();
    while (digitalRead(16) == LOW) {
      time_t now;
      struct tm * timeinfo;
      time(&now);
      timeinfo = localtime(&now);
      Serial.println(timeinfo->tm_min);
      color = "#1eceff";
      setNeoColor(color, point1, point2);
      delay(1000);
      color = "#ffffff";
      setNeoColor(color, point1, point2);
      delay(1000);
    }
  }
<<<<<<< HEAD
=======
  
  int packetSize = port.parsePacket();
  if (packetSize == sizeof(leds)) {
    port.read((char*)leds, sizeof(leds));
    //Serial.printf(".");
    FastLED.show();
    // flush the serial buffer
    while (Serial.available()) {
      Serial.read();
    }
  } 
  else if (packetSize) {
    Serial.printf("Invalid packet size: %u (expected %u)\n", packetSize, sizeof(leds));
    port.flush();
    return;
  }

>>>>>>> 3b6360d7e6b72bbd7ee445d5142c5381b687f2ff
}

void handleRoot() {
  Serial.print("Client connected. ");
  String getip = server.client().remoteIP().toString();
  Serial.print("IP :");
  Serial.println(getip);
  if (server.hasArg("plain") == false) { //Check if body received
    // data from the colorpicker
    // building a website
    char temp[5000];
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    snprintf ( temp, 5000,
               //<input type="range" min="0" max="100" step="1" value="50">
               "<!DOCTYPE html>\n<html>\n\
              <head>\n\
                <title>Esp8266 NeoPixel Controler</title>\n\
                <style>\
                  body { background-color: #cccccc; font-family: Arial; Color: #008; }\
                </style>\n\
                <meta name=\"viewport\" content=\"width=device-width, height=device-height, initial-scale=1.0, user-scalable=0, minimum-scale=1.0, maximum-scale=1.0\" />\n\
              </head>\n\
              <body>\n\
                <h1>Ceiling light</h1>\n\
                <p>Uptime: %02d:%02d:%02d</p>\n\
                \n\
                <form action=\"\" name=\"pick\" method=\"post\">\n\
                <input type=\"color\" name=\"c\" value=\"%02d\" onchange=\"document.forms['pick'].submit();\" />\n\
                &nbsp;<span onclick=\"document.forms['pick'].submit();\" style=\"font-size:16pt;\"> Change </span>\n\
                </form>\n\
                \n\
              </body>\
            </html>",

               hr, min % 60, sec % 60
             );
    server.send ( 200, "text/html", temp );

    // setting the color to the strip
    if (server.hasArg("c") )
    { color = server.arg("c");
      Serial.println("Color: " + color);
      char clr [7];
      color.toCharArray(clr, 7);
      setNeoColor(color, point1, point2);
    }

    //server.send(200, "text/plain", "Body not received");
    return;

  }

  String message = server.arg("plain");
  if (message.lastIndexOf("$") == 0) {
    //server.send(200, "text/plain", message);
    message.remove(0, 1);
    Serial.println("message is : " + message);
    String buff = message;
    if (message.equalsIgnoreCase("only bed")) {
      point1 = 144; //left part of stipe on that comand
      point2 = 175; // right part
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("all")) {
      point1 = 0;
      point2 = strip.numPixels();
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("pc")) {
      point1 = 250;
      point2 = 278;
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("exp")) {
      point1 = 253;
      point2 = 278;
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("green")) {
      color = "#00ff00";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("red")) {
      color = "#ff0000";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("blue")) {
      color = "#0000ff";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("white")) {
      color = "#ffffff";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("yellow")) {
      color = "#dfe839";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("magenta")) {
      color = "#ff1ef7";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("magento")) {
      color = "#ff1ef7";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("lounge")) {
      color = "#1eceff";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("orange")) {
      color = "#f97f1b";
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("rainbow")) {
      Serial.println("Rainbow begins)");
      rainbow(10);
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("random")) {
      int r = random(0, 255);
      delay(1);
      int g = random(0, 255);
      delay(1);
      int b = random(0, 255);
      delay(1);
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
      // setting cut from 0 to 1 point to black
      for (int i = 0; i < point1; i++) {
        strip.setPixelColor(i, strip.Color( 0, 0, 0 ) );
      }
      // setting cut from 1 point to 2 point to given color
      for (int i = point1; i < point2; i++) {
        strip.setPixelColor(i, strip.Color( r, g, b ) );
      }
      // setting cut from 2 point to end to black
      for (int i = point2; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color( 0, 0, 0 ) );
      }
      strip.show();
    }
    if (message.equalsIgnoreCase("sunrise")) {
      Serial.println("Sunrise began");
      int sun_speed = 100;
      sunrise(sun_speed);
    }
    if (message.equalsIgnoreCase("on")) {
      color = "#ffffff";
      point1 = 0;
      point2 = strip.numPixels();
      setNeoColor(color, point1, point2);
    }
    if (message.equalsIgnoreCase("off")) {
      color = "#000000";
      setNeoColor(color, point1, point2);
    }

    if (message.lastIndexOf("s") == 9 ) {
      Serial.print("Brightness current:");
      Serial.println(brightness);
      String buffe = "";
      for (int i = 9; i <= 13; i++) {

        if (buff[i] >= '0' && buff[i] <= '9') // capturing numbers
          buffe += buff[i];
      }
      brightness = buffe.toInt();
      //for(int i=0; i < NUM_LEDS; i++) {
      //strip.setPixelColor(i, strip.Color( 0, 0, 255 ) );
      //}
      if (brightness >= 1 or brightness <= 256) {
        Serial.print("new brigtness");
        Serial.println(brightness);
        strip.setBrightness(brightness);
      }
      if (buffe == 0) {
        color = "#000000";
        setNeoColor(color, point1, point2);
      }
    }
    strip.show();


    if (message.lastIndexOf("t") == 3 ) {

      String buffe = "";
      for (int i = 4; i <= 8; i++) {

        if (buff[i] >= '0' && buff[i] <= '9') // capturing numbers
          buffe += buff[i];
      }
      int num = buffe.toInt();
      test(num);

      //color = server.arg("c");
    }
  }
  else {
    Serial.print("not valid message : ");
    Serial.println(message);
    Serial.print("ind of $ : ");
    Serial.println(message.lastIndexOf("$"));
  }

}
void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );

}

void setNeoColor(String value, int point1, int point2) {

  Serial.print("Setting ceiling...");
  // converting Hex to Int
  int number = (int) strtol( &value[1], NULL, 16);

  // splitting into three parts
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;

  //    start-point1;point1-point2;end
  // setting cut from 0 to 1 point to black
  for (int i = 0; i < point1; i++) {
    strip.setPixelColor(i, strip.Color( 0, 0, 0 ) );
  }
  // setting cut from 1 point to 2 point to given color
  for (int i = point1; i < point2; i++) {
    strip.setPixelColor(i, strip.Color( r, g, b ) );
  }
  // setting cut from 2 point to end to black
  for (int i = point2; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color( 0, 0, 0 ) );
  }

  strip.show();


  Serial.println("Complete.");
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = point1; i < point2; i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }

}

void test(int num) {
  Serial.print("testing ");
  Serial.println(num);

  strip.setPixelColor(num, strip.Color( 255, 0, 0 ));
  strip.show();
  delay(1000);
  strip.setPixelColor(num, strip.Color( 255, 255, 255 ));
  strip.show();
}

void sunrise(int sun_speed) {
  for (int i = 0; i < 60; i++) { // to point 1
    int col = i;
    int pos = i;
    strip.setPixelColor(pos, strip.Color( col, 0, 0 ) );
    strip.show();
    pos = (300 - pos);
    strip.setPixelColor(pos, strip.Color( col, 0, 0 ) );
    strip.show();
    delay(sun_speed);
  }
  for (int i = 0; i < 33; i++) { // to point 2
    int col = i * 3;
    int pos = i;
    strip.setPixelColor(pos, strip.Color( col, col, 0 ) );
    strip.show();
    pos = (300 - pos);
    strip.setPixelColor(pos, strip.Color( col, col, 0 ) );
    strip.show();
    delay(sun_speed);
  }
  for (int i = 0; i < 60; i++) { // to point 2.5
    int col = 255;
    int pos = i;
    strip.setPixelColor(pos, strip.Color( col, col, 0 ) );
    strip.show();
    pos = (300 - pos);
    strip.setPixelColor(pos, strip.Color( col, col, 0 ) );
    strip.show();
    delay(sun_speed);
  }
  for (int i = 0; i < 80; i++) { // to point 3
    int col = i * 3;
    int pos = i;
    strip.setPixelColor(pos, strip.Color( 255, 255, col ) );
    strip.show();
    pos = (300 - pos);
    strip.setPixelColor(pos, strip.Color( 255, 255, col ) );
    strip.show();
    delay(sun_speed);
  }
  for (int i = 0; i < 150; i++) { // to finish
    int pos = i;
    strip.setPixelColor(pos, strip.Color( 255, 255, 255 ) );
    strip.show();
    pos = (300 - pos);
    strip.setPixelColor(pos, strip.Color( 255, 255, 255 ) );
    strip.show();
    delay(sun_speed);
  }

}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
