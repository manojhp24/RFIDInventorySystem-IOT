<<<<<<< HEAD
#include "Systemcontroller.h"
=======
#include "Feedback.h"
#include "RFIDReader.h"
#include "WIFIManager.h"
#include "FirebaseService.h"

#define SS_PIN 5
#define RST_PIN 22
#define LED_PIN 2
#define BUZZER_PIN 25

// WIFI Credentials
#define WIFI_SSID "Galaxy F04 98df"
#define WIFI_PASSWORD "mhp961972"

// DB Credentials
#define API_KEY "your_api_key"
#define DATABASE_URL "your_real_time_db_url"
#define USER_EMAIL "manojhp584@gmail.com"
#define USER_PASSWORD "Rfid_iot_project"


void initSystem();


RFIDReader rfidReader(SS_PIN, RST_PIN);
Feedback feedback(LED_PIN, BUZZER_PIN);
WiFiManager wifi(WIFI_SSID, WIFI_PASSWORD);
FirebaseService firebase(API_KEY, DATABASE_URL, USER_EMAIL, USER_PASSWORD);

>>>>>>> 59374475c3b16ef80cf40b4b17a9f41ec6eaed6d


void setup() {
	systemSetup();
}


void loop() {
	systemLoop();	
}






