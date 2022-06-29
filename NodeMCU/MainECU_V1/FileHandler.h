#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include <Arduino.h>

//Define Firebase Data object
#include "FS.h"
#include "SPIFFS.h"
#include "Cipher.h"

#define DOWNLOAD_PERMISSION     '1'
#define ACKN 'a'

void SendFile(fs::FS &fs);

String Read_FileName(void);

void DecryptFile(fs::FS &fs);
void encryptFile(fs::FS &fs);

#endif
