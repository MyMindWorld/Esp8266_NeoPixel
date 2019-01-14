#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Secrets.h" //File with your creditionals for connection 
// it should contain the following - 
// const char *ssid = "your-ssid";
// const char *password = "your-password";

ESP8266WebServer server ( 80 );

#define NeoPIN D1
#define NUM_LEDS 32
int brightness = 5;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);

const int led = 13;

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
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );
  
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
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
}

void loop ( void ) {
  // waiting fo a client
  server.handleClient();
}


void handleRoot() {
  Serial.println("Client connected");
  digitalWrite ( led, 1 );
  if (server.hasArg("plain")== false){ //Check if body received
            // data from the colorpicker 
            String color = server.arg("c");
            Serial.println("Color: " + color);
            // building a website
            char temp[5000];
              int sec = millis() / 1000;
              int min = sec / 60;
              int hr = min / 60;
              char clr [7];
              color.toCharArray(clr, 7);
             snprintf ( temp, 5000,
            
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
            
                hr, min % 60, sec % 60, clr
              );
              server.send ( 200, "text/html", temp );
              digitalWrite ( led, 0 );
                        // setting the color to the strip 
                        setNeoColor(color);
                        //server.send(200, "text/plain", "Body not received");
                        return;
 
      }
 
      String message = server.arg("plain");
      //server.send(200, "text/plain", message);
      Serial.println("message is : " + message);
      String buff = message;    
   if (message == "green" or message == "Green") {
           String color = "#00ff00";
      setNeoColor(color);
  }
  if (message.equalsIgnoreCase("red")) {
       String color = "#ff0000";
      setNeoColor(color);
  }
  if (message == "blue" or message == "Blue") {
      String color = "#3333ff";
      setNeoColor(color);
  }
  if (message == "white" or message == "White") {
       String color = "#ffffff";
      setNeoColor(color);
  }
  if (message == "off" or message == "Off") {
       String color = "#000000";
      setNeoColor(color);
  }
  if (message.lastIndexOf("s") == 9 ) {
        
        String buffe = "";
        for (int i=9; i <= 13; i++){

          if(buff[i]>='0'&&buff[i]<='9') // capturing numbers
              buffe += buff[i];
        }
        brightness = buffe.toInt();
        Serial.println(brightness);
        //for(int i=0; i < NUM_LEDS; i++) {
        //strip.setPixelColor(i, strip.Color( 0, 0, 255 ) );
        //}
       strip.setBrightness(brightness);
       strip.show();
  }

  
  //String color = server.arg("c");
            
  
}

void handleNotFound() {
  digitalWrite ( led, 1 );
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
  digitalWrite ( led, 0 );
}



void setNeoColor(String value){
  Serial.print("Setting Neopixel...");
  // converting Hex to Int
  int number = (int) strtol( &value[1], NULL, 16);
  
  // splitting into three parts
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  // DEBUG
  Serial.print("RGB: ");
  Serial.print(r, DEC);
  Serial.print(" ");
  Serial.print(g, DEC);
  Serial.print(" ");
  Serial.print(b, DEC);
  Serial.println(" ");
  
  // setting whole strip to the given color
  for(int i=0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color( g, r, b ) );
  }
  // init
  strip.show();
 
  
  Serial.println("on.");
}
