//Include server and file hanlder libraries

#include "Debug.h"
#include "Server.h"
#include "FileHandler.h"
#include "SPIFFS.h"
#include "mbedtls/base64.h"

//Cipher *cipher = new Cipher();

String getFile(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  String output = "";
  
  for(int j = 0; j < file.size(); j++) {
    output += (char)file.read();
  }

  return output;
}


void setup(){

  //Connect to wifi with given SSID and Password
  Wifi_Connect(); 

  //Establish Connection with server
  Server_Connect();

   
  // Serial.print("\nDecrypted file:\n");
  // Serial.println(getFile(SPIFFS, "/decrypted.hex"));

 
}


void loop(){

  if (Serial2.available())
  {
    if (Serial2.read() == DOWNLOAD_PERMISSION)
    {
      Serial.write("Downlaod Enabled");
      String file = "test.txt";

      Server_Download(file);
      DecryptFile(SPIFFS);
      SendFile(SPIFFS);      
    }
  }
}
