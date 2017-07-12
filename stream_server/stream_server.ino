#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>
#include "memorysaver.h"

const int CS = 16;
ESP8266WebServer server(80);
ArduCAM myCAM(OV2640, CS);

void startCapture() {
  myCAM.clear_fifo_flag();
  myCAM.start_capture();
}

void serverStream() {
  WiFiClient client = server.client();
  
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);
  
  while (1) {
    startCapture();
    while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));
    size_t len = myCAM.read_fifo_length();
    
    myCAM.CS_LOW();
    myCAM.set_fifo_burst();
    
    #if !(defined (ARDUCAM_SHIELD_V2) && defined (OV2640_CAM))
    SPI.transfer(0xFF);
    #endif
    if (!client.connected()) break;
    
    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n";
    response += "Content-Length: " + String(len) + "\r\n\r\n";
    server.sendContent(response);
    
    static const size_t bufferSize = 2048;
    static uint8_t buffer[bufferSize] = {0xFF};
    
    while (len) {
      size_t will_copy = (len < bufferSize) ? len : bufferSize;
      SPI.transferBytes(&buffer[0], &buffer[0], will_copy);
      if (!client.connected()) break;
      client.write(&buffer[0], will_copy);
      len -= will_copy;
    }
    
    myCAM.CS_HIGH();
    if (!client.connected()) break;
  }
}

void setup() {
  uint8_t vid, pid;
  uint8_t temp;

  Wire.begin();
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  
  SPI.begin();
  SPI.setFrequency(4000000); //4MHz

  myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
  temp = myCAM.read_reg(ARDUCHIP_TEST1);
  if (temp != 0x55) {
    Serial.println("SPI1 interface Error!");
    while(1);
  }

  myCAM.wrSensorReg8_8(0xff, 0x01);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
  myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
  if ((vid != 0x26 ) && (( pid != 0x41 ) || ( pid != 0x42 )))
    Serial.println("Can't find OV2640 module!");

  myCAM.set_format(RAW);
  myCAM.InitCAM();
  myCAM.OV2640_set_JPEG_size(OV2640_320x240);
  myCAM.clear_fifo_flag();

  String ssid = "eyepiece_";
  byte mac[6];
  WiFi.macAddress(mac);
  for(int i = 0; i < 6; i++)
    ssid += String(mac[i], HEX);
    
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str());
  
  server.on("/stream", HTTP_GET, serverStream);
  server.begin();
}

void loop() {
  server.handleClient();
}

