/**
 * SSDP Device example
 * Process SSDP request and NOTIFY services and presence
 * 
 * This example code is in the public domain.
 **/

#include <WiFi.h>
#include <ESP32WebServer.h>
#include <uSSDP.h>

const char* ssid = "ADD your SSID";
const char* password = "ADD your password";

ESP32WebServer HTTP(80);
uDevice device;
uSSDP SSDP;

void setup(){
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED){
      Serial.println("WiFi Failed");
      while(1) delay(100);
  }
  
	Serial.print("Starting HTTP at ");
	Serial.print(WiFi.localIP());
	Serial.print(":");
	Serial.println(80);
  HTTP.on("/description.xml", HTTP_GET, [](){
      SSDP.schema(HTTP.client());
  });
  HTTP.begin();

	
  byte mac[6];
  char base[UUIDBASE_SIZE];
  WiFi.macAddress(mac);
  sprintf(base, "esp8266x-%02x%02x-%02x%02x-%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  Serial.printf("Starting uSSDP-ESP32: BASE: %s, MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", base, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  device.begin((const char*)base, mac);
  device.serialNumber((char*)"1241");
  device.manufacturer((char*)"Espressif");
  device.manufacturerURL((char*)"http://espressif.com");
  device.modelName((char*)"ESP-32");
  device.modelNumber(1, 0);
  device.friendlyName((char*)"ESP32-WROOM");
  device.presentationURL((char*)"/");SSDP.begin(&device);
  Serial.println("SSDP Started");
}

void loop(){
  HTTP.handleClient();
  SSDP.process();
  delay(1);
}
