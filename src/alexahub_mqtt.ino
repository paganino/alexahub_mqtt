/*
 * This is a basic example on how to use Espalexa, MQTT and WebOTA 
 *  
 */ 

//#define ESPALEXA_ASYNC            //uncomment for async operation (can fix empty body issue)
#define ESPALEXA_NO_SUBPAGE         //disable /espalexa status page
//#define ESPALEXA_DEBUG             //activate debug serial logging
//#define ESPALEXA_MAXDEVICES 15    //set maximum devices add-able to Espalexa

#include <SoftwareSerial.h>   
#include "EspMQTTClient.h"   //https://github.com/plapointe6/EspMQTTClient
#include <Espalexa.h>       //https://github.com/Aircoookie/Espalexa
#include <WebOTA.h>         //https://github.com/scottchiefbaker/ESP-WebOTA


EspMQTTClient client(
  "wifi_ssid_here",  // SSID wifi
  "password_wifi",   // password
  "xxx.xxx.x.x",  // your MQTT Broker server ip
  // "",          // username mqtt -  Can be omitted if not needed
  // "",          // password mqtt - Can be omitted if not needed
  "alexahub",      // Client name that uniquely identify your device
  1883            // The MQTT port, default to 1883. this line can be omitted
);


//callback functions max default 10
void firstLightChanged(uint8_t brightness); 
//void secondLightChanged(uint8_t brightness);
//void thirdLightChanged(uint8_t brightness);
//void fourthLightChanged(uint8_t brightness);


Espalexa espalexa;

void setup() {
   Serial.begin(115200);
  
  // Optionnal functionnalities of EspMQTTClient : 
  //client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
   
   webota.init(8081, "/update");  // change WebOTA default due to conflict with Espalexa internal  webserver

 // Define your devices here (default max 10 devices). 
    espalexa.addDevice("lamp", firstLightChanged); //simplest definition, default state off
    espalexa.begin();
}



// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished(){}

void loop() {
  client.loop();
  espalexa.loop();
  webota.handle();
  webota.delay(1);
}
//our callback functions
void firstLightChanged(uint8_t brightness) {

//Serial.print("Device 1 changed to ");
//do what you need to do here
    if (brightness) {
      client.publish("/alexahub/lamp", "1");  // ON
    //Serial.println(brightness);
      }
    else {
      client.publish("/alexahub/divano", "0"); //  OFF
    //Serial.println("OFF");
    }
  }


