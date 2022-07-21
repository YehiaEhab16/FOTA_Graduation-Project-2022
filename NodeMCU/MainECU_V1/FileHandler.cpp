#include "Debug.h"
#include "FileHandler.h"
#include "HardwareSerial.h"
#include "Cipher.h"
#include "Base64.h"
#include "mbedtls/aes.h"

char ackn = 'A';
Cipher *cipher = new Cipher();

String getFile(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  String output = "";
  
  for(int j = 0; j < file.size(); j++) {
    output += (char)file.read();
  }

  Serial2.write(APP1_DOWNLOADED);
  Serial.write(APP1_DOWNLOADED);
  Serial2.println(file.size());
  Serial.println(file.size()); 

  return output;
}

void DecryptFile(fs::FS &fs)
{
  char  FileByte;
  String decoded_line = "";
  String line; 
  String decrypted_line;
  int decoded_length;

  File downloaded_file = SPIFFS.open("/TestStorage.hex");
  File storage = SPIFFS.open("/decrypted.hex", FILE_WRITE);
 
  while (downloaded_file.available()) 
  {  
    decoded_line = "";
    line = downloaded_file.readStringUntil('\n');
    
    decoded_length = Base64.decodedLength(const_cast<char*>(line.c_str()) , line.length());

    char decodedString[decoded_length];
    Base64.decode(decodedString, const_cast<char*>(line.c_str()), line.length());

    for (int i=0; i<=decoded_length; i++)
    {
      decoded_line += decodedString[i];
    }
    
    decrypted_line = cipher->decryptString(decoded_line);

    decrypted_line.remove(decrypted_line.indexOf('\n'));

    if ((decrypted_line.length())%16 == 0)
    {
      decrypted_line.remove(decrypted_line.length()-16);
    }
    storage.print(decrypted_line + "\n");
  }

  // Serial.print("\nDecrypted file:\n");
  // Serial.println(getFile(SPIFFS, "/decrypted.hex"));
  
  downloaded_file.close();
  // Serial2.write(FILE_DOWNLOADED);
  // Serial.write(FILE_DOWNLOADED);
  // Serial2.println(storage.size());
  // Serial.println(storage.size()); 
  storage.close();

}

void SendFile(fs::FS &fs)
{
  char FileByte;
  char FileBytes[8];
  int i;
  debugf("Reading file: %s\r\n", "/decrypted.hex");

  File file = SPIFFS.open("/decrypted.hex");
  if (!file || file.isDirectory()) {
    debugln("- failed to open file for reading");
    return;
  }
  
    
  debugln("- read from file:");
  while (file.available()) 
  {  
      i=0;
      ackn = '0' ;
      
      do
      {
        FileByte = file.read();
        Serial2.write(FileByte);
        Serial.write(FileByte);
      }while (FileByte != '\n');
      
      while (!(Serial2.available()));
      ackn = Serial2.read();
    //   debugln("waiting for ackn: ");
      if(ackn == 'a')
      {
        //debugln("ackn recieved..");
        continue;
      }
      else break;
  }   
  file.close();
}


