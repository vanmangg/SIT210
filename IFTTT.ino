// Libraries
#include <WiFiNINA.h>
#include <BH1750FVI.h>
#include "secrets.h"

// Light Sensor Instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

// Network Details (secret.h tab)
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// IFTTT
WiFiClient client;
char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME_PRESENT = "/trigger/Sunlight_Present/with/key/1UTidKHrb2S3T8uSR0CQR"; // sunlight present
String PATH_NAME_ABSENT =  "/trigger/Sunlight_Absent/with/key/1UTidKHrb2S3T8uSR0CQR"; // sunlight absent
String PATH_NAME_MAX = "/trigger/max_sunlight/with/key/1UTidKHrb2S3T8uSR0CQR"; // sunlight limit

// Variables
bool sunlight = false;
int daily_limit = 7200; // 2 hours = 120 minutes = 7200 seconds
int sunlight_duration = 0; 

// Functions
void SendRequest(String path){
  if(client.connect(HOST_NAME, 80)){
    // make a HTTP request:
    // send HTTP header
    client.println("GET " + path + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP reader
    while(client.connected()) {
      if(client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
  } else{
    Serial.println("CONNECTION TO SERVER FAILED");
  }
}

void setup(){
  Serial.begin(9600); // set baud rate
  while (!Serial); // open serial monitor to begin
  WiFi.begin(ssid, pass); // initialise network connection
  LightSensor.begin(); // initialise light sensor
}

void loop() {
  while(sunlight_duration < daily_limit){
    uint16_t lux = LightSensor.GetLightIntensity();
    if(lux > 0){
      sunlight_duration++;
      if(!sunlight){
        SendRequest(PATH_NAME_PRESENT);
        sunlight = true;
      }
    }
    else if(lux == 0 && sunlight){
      SendRequest(PATH_NAME_ABSENT);
      sunlight = false;
    }
    Serial.print("lux: ");
    Serial.println(lux);
    Serial.print("Duration: ");
    Serial.println(sunlight_duration);
    delay(1000);
  }

  SendRequest(PATH_NAME_MAX);

  // stop client
  client.stop();
  Serial.println();
  Serial.println("DISCONNECTED");
  exit(0);
}
