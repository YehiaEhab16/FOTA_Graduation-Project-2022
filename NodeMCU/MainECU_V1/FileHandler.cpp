#include "Debug.h"
#include "FileHandler.h"

void SendFile(fs::FS &fs, String path) 
{
  char FileByte;
  debugf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    debugln("- failed to open file for reading");
    return;
  }

  debugln("- read from file:");
  while (file.available()) {
    FileByte = file.read();
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

