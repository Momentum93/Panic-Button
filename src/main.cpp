#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "WiFi.h"
#include <ESPAsyncWebServer.h>
//#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

AsyncWebServer  server(80);


bool show = true;
unsigned long currentMillis; 

Adafruit_NeoPixel strip(8, 16, NEO_RGB + NEO_KHZ800);

void setup(){
  strip.begin();          
  strip.setBrightness(50);
  strip.clear();
  strip.show();

  
  Serial.begin(9600);
  WiFi.softAP("PanicButton");
  Serial.println(WiFi.softAPIP());

  server.on("/ON", HTTP_GET, [](AsyncWebServerRequest *request){
        for (int i=0;i<8;i++){
          strip.setPixelColor(i, strip.Color(0,255,0));
        }
        strip.show();
        Serial.println("ON");
        request->send(200);
        
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200);

  });
  server.on("/OFF", HTTP_GET, [](AsyncWebServerRequest *request){
        strip.clear();
        strip.show();
        request->send(200);
  });


  server.begin();

  
  
  //strip.show();
  currentMillis =  millis(); 
  //on();
}


void loop(){
  /*
  unsigned long tmp = millis();
  if (tmp - currentMillis> 1000){
    currentMillis = tmp;
    show = !show;
  }
  if (show){
    for (int i=0;i<8;i++){
      strip.setPixelColor(i, strip.Color(0,255,0));
    }
  }else{strip.clear();}
  strip.show();
  */
}