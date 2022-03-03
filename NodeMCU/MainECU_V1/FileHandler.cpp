#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>                           //Provide the token generation process info.
#include "FS.h"
#include "SPIFFS.h"


void SendFile(fs::FS &fs, const char * path)
{
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("Read from file:");
  while (file.available()) {
    temp = file.read();
    Serial.write(temp);
  }
  file.close();
}

