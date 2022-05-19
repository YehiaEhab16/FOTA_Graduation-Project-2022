//Include server and file hanlder libraries
#include "Debug.h"
#include "Server.h"
#include "FileHandler.h"

void setup() {
  //Connect to wifi with given SSID and Password
  Wifi_Connect();
 

  //Establish Connection with server
  Server_Connect();
}

void loop() {
  if (Serial2.available())
    if (Serial2.read() == DOWNLOAD_PERMISSION)
    {
      Serial.write("Downlaod Enabled");
      String file = "Hello_ARM.hex";

      Server_Download(file);

      //file = "/" + file;
      debugln(file);
      //Send file to STM32
      SendFile(SPIFFS);
    }
}
