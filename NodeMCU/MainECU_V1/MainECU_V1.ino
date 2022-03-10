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
  if(Serial.available())
    if(Serial.read()==DOWNLOAD_PERMISSION)
    {
      debugln("Downlaod Enabled");
      String file = Read_FileName();
      debugln("Recieved file name");
      debugln(file);
      //Download file from server
      Server_Download(file);

      file = "/" + file;
      debugln(file);
      //Send file to STM32
      SendFile(SPIFFS, file);
    }
}
