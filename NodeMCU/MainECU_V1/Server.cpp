#include "Debug.h"
#include "Server.h"

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

int Global_App1ServerVersion;
int Global_App1CarVersion;
int Global_App2ServerVersion;
int Global_App2CarVersion;
int Last_Notification;

bool taskCompleted = false;
unsigned long sendDataPrevMillis = 0;
int Version_int;
bool signupOK = false;

void Wifi_Connect(void)
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  debug("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    debug(".");
    delay(300);
  }
  debugln();
  debug("Connected with IP: ");
  debugln(WiFi.localIP());
  debugln();
}

void Server_Connect(void)
{
  debugf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  if (Firebase.signUp(&config, &auth, "", ""))
  {
    // Serial.println("ok");
    signupOK = true;
  }

  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  #if defined(ESP8266)
  //required for large file data, increase Rx size as needed.
  fbdo.setBSSLBufferSize(1024 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
  #endif

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void Server_Download(String file)
{
  char test;
  if (Firebase.ready() && !taskCompleted)
  {
    taskCompleted = true;
    test =  Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, file /* path of remote file stored in the bucket */, "/TestStorage.hex" /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */);
    if (test == 0)
    {
      debugln("******************");
      debugln("Download Complete");
      debugln("******************");
    }
  }
}

int Version_Recieve(void)
{
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/zPPO6sJUEU5WrqeEnB2N9g==/Feedback"))
    {
      if (fbdo.dataType() == "int")
      {
        Version_int = fbdo.intData();
        Serial.print("Function Version = ");
        Serial.println(Version_int);
        return Version_int;
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }

}

void UpdateCheck(void)
{
  if (Global_App1CarVersion == Global_App1ServerVersion)
	{
		Global_App1ServerVersion = Version_Recieve();             
	}
	else if (Global_App1ServerVersion > Global_App1CarVersion)
	{
		if (Last_Notification < Global_App1ServerVersion)
		{
			Serial2.write(UPDATE_NOTIFICATION);
			Serial2.write(UPDATE_NOTIFICATION);
			Last_Notification = Global_App1ServerVersion;          
		}
		if (Last_Notification == Global_App1ServerVersion)
		{
			Global_App1ServerVersion = Version_Recieve();
		}                
	}

  if (Global_App2CarVersion == Global_App2ServerVersion)
	{
		Global_App2ServerVersion = Version_Recieve();             
	}
	else if (Global_App2ServerVersion > Global_App2CarVersion)
	{
		if (Last_Notification < Global_App2ServerVersion)
		{
			Serial2.write(UPDATE_NOTIFICATION);
			Serial2.write(UPDATE_NOTIFICATION);
			Last_Notification = Global_App2ServerVersion;          
		}
		if (Last_Notification == Global_App2ServerVersion)
		{
			Global_App2ServerVersion = Version_Recieve();
		}                
	}
}

void WriteDiagnostics(int data)
{  
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "/zPPO6sJUEU5WrqeEnB2N9g==/Feedback", data)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    }
    else
    {
      Serial.println("Firebase not ready");
    }

}
