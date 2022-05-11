#include "Debug.h"
#include "FileHandler.h"
#include "Cipher.h"

Cipher * cipher = new Cipher();

void SendFile(fs::FS &fs, String path) 
{
  unsigned char FileByte;
  debugf("Reading file: %s\r\n", path);

  cipher->setKey(CIPHER_KEY);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    debugln("- failed to open file for reading");
    return;
  }

  debugln("- read from file:");
  while (file.available()) {
    FileByte = file.read();
    cipher->decrypt(&FileByte,CIPHER_KEY,&FileByte);
    Serial.write(FileByte);
  }
  file.close(); 
}

String Read_FileName(void)
{
  char inChar;
  String inputString = "";
  bool stringComplete = false;
  while (!stringComplete) {
    if(Serial.available())
    {
      inChar = (char)Serial.read();   //Reading character from serial
      if (inChar == '#')                   //Checking for stop bit '#'
      {
        stringComplete = true;             //Setting flag to indicate recieving of string
      }
      if(!stringComplete)
      inputString += inChar;            //Concatenating string until reaching full message
    }
  }
  if(stringComplete == true)
  {
    stringComplete=false;
    return inputString;
  }
}

