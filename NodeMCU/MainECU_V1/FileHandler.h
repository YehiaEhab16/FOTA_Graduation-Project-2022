#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <Arduino.h>

//Define Firebase Data object
#include "FS.h"
#include "SPIFFS.h"

#define DOWNLOAD_PERMISSION     '1'

void SendFile(fs::FS &fs, String path);

String Read_FileName(void);


#endif
