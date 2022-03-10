#ifndef SERVER_H_
#define SERVER_H_

#include <Arduino.h>

//Define the WiFi credentials
#define WIFI_SSID                       "Dr.Ehab"
#define WIFI_PASSWORD                   "0000000009"

//Define the API Key
#define API_KEY                         "AIzaSyBRrnJB5r0m9v9YsBj-em7ZefzYT4LVkp4"

//Define the user Email and password that alreadey registerd or added in your project
#define USER_EMAIL                      "fota.project2022@gmail.com"
#define USER_PASSWORD                   "fota123123"

//Define the Firebase storage bucket ID e.g bucket-name.appspot.com
#define STORAGE_BUCKET_ID               "fota-project-new.appspot.com"

#define BAUD_RATE                       9600

//Function to connect to Wifi
void Wifi_Connect(void);

//Function to establish connection with server
void Server_Connect(void);

//Function to download file from server
void Server_Download(String file);


#endif
