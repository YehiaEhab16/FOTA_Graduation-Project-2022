#include "Credentials.h>

//Creating Instance from firebse classes
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//Global variables for reading file and parsing data
bool test;
bool taskCompleted = false;
String fileName = "";
char parsedata;

void setup() {
  Serial.begin(9600);  
  //Connect to Wi-Fi
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

  //Connect to firebase server
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
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
