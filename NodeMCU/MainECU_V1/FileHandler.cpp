#include "Debug.h"
#include "FileHandler.h"
#include "HardwareSerial.h"
char ackn = 'A';

void SendFile(fs::FS &fs)
{
  char FileByte;
  debugf("Reading file: %s\r\n", "/TestStorage.hex");
  File file = fs.open("/TestStorage.hex");
  
  if (!file || file.isDirectory()) {
    debugln("- failed to open file for reading");
    return;
  }
  debugln("- read from file:");
  while (file.available()) {
    do {
      debugln("Waiting for ackn: ");
      if (ackn == 'A')
      {
        debugln("ackn recieved = ");
        debugln(ackn);

        do {
          FileByte = file.read();
          Serial2.write(FileByte);
          ackn = 'B';
        } while (FileByte != '\n');

      }
      else
      {
        debugln("ackn not recieved = ");
        debugln(ackn);
        
      }
      ackn = Serial2.read();

    } while (ackn == 'A');

  }
  file.close();
}

String Read_FileName(void)
{
  char inChar;
  String inputString = "";
  bool stringComplete = false;
  while (!stringComplete) {
    if (Serial.available())
    {
      inChar = (char)Serial.read();   //Reading character from serial
      if (inChar == '#')                   //Checking for stop bit '#'
      {
        stringComplete = true;             //Setting flag to indicate recieving of string
      }
      if (!stringComplete)
        inputString += inChar;            //Concatenating string until reaching full message
    }
  }
  if (stringComplete == true)
  {
    stringComplete = false;
    return inputString;
  }
}
