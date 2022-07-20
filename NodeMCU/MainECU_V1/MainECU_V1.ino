//Include server and file hanlder libraries

#include "Debug.h"
#include "Server.h"
#include "FileHandler.h"
#include "SPIFFS.h"
#include "mbedtls/base64.h"

char ReadSerial;

void setup(){

  //Connect to wifi with given SSID and Password
  Wifi_Connect(); 

  //Establish Connection with server
  Server_Connect();

  Serial2.write(UPDATE_NOTIFICATION);
	Serial2.write(UPDATE_NOTIFICATION); 
}


void loop(){

  if (Serial2.available())
  {
    ReadSerial = Serial2.read();

    if (ReadSerial == 'X')
    {
      char a = Serial2.read();
      WriteDiagnostics((int)a); 
      Serial.write((int)a);
      
    }
    else if (ReadSerial == DOWNLOAD_PERMISSION)
    {
      ReadSerial = 0;
      Serial.write("Downlaod Enabled");
      String file = "APP_ECU_111.hex";

      Server_Download(file);
      DecryptFile(SPIFFS);


      Serial.print("\nDecrypted file:\n");
      Serial.println(getFile(SPIFFS, "/decrypted.hex"));  

      while(Serial2.read() != START_SEND);     
         
      SendFile(SPIFFS);      
    }
  
  }

  // UpdateCheck();
}

