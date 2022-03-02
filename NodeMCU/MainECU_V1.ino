
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include <addons/TokenHelper.h>
/* 1. Define the WiFi credentials */
#define WIFI_SSID "magdy"
#define WIFI_PASSWORD "ahwa1234"
/* 2. Define the API Key */
#define API_KEY "AIzaSyBRrnJB5r0m9v9YsBj-em7ZefzYT4LVkp4"
/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "magdy1salah@gmail.com"
#define USER_PASSWORD "magdyhero1"
/* 4. Define the Firebase storage bucket ID e.g bucket-name.appspot.com */
#define STORAGE_BUCKET_ID "fota-project-new.appspot.com"
//Define Firebase Data object

#include "FS.h"
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
bool test;
bool taskCompleted = false;
String fileName = "";
char parsedata;

void SendFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  while (file.available()) {
    temp = file.read();
    Serial.write(temp);
  }
  file.close(); 
}

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once
  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

#if defined(ESP8266)
  //required for large file data, increase Rx size as needed.
  fbdo.setBSSLBufferSize(1024 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
#endif

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.ready() && !taskCompleted)
  {
    taskCompleted = true;
    test =  Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, "TestStorage.c" /* path of remote file stored in the bucket */, "/TestStorage.c" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */);
    if (test == 0)
    {
      Serial.println("******************");
      Serial.println("Download Complete");
      Serial.println("******************");
    }
  }
  SendFile(SPIFFS,"/TestStorage.c");
}
