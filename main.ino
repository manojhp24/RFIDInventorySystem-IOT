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
#define API_KEY "AIzaSyDKXCuL4ln_uyNcJueYGp6y_eheipPQriU"
#define DATABASE_URL "https://rfidinventorysystem-iot-default-rtdb.firebaseio.com/"
#define USER_EMAIL "manojhp584@gmail.com"
#define USER_PASSWORD "Rfid_iot_project"


void initSystem();


RFIDReader rfidReader(SS_PIN, RST_PIN);
Feedback feedback(LED_PIN, BUZZER_PIN);
WiFiManager wifi(WIFI_SSID, WIFI_PASSWORD);
FirebaseService firebase(API_KEY, DATABASE_URL, USER_EMAIL, USER_PASSWORD);



void setup() {
	initSystem();
}


void loop() {

	firebase.loop();

	static bool sent = false;
  if (firebase.ready() && !sent) {
    firebase.writeTestData();
    sent = true;
  }

	if (!rfidReader.isCardDetected()) return;

	rfidReader.printUID();
	feedback.success();
	rfidReader.halt();
	
}



void initSystem() {
	Serial.begin(9600);
	wifi.connect();
	firebase.begin();
	rfidReader.begin();

	feedback.begin();

	Serial.println("Scan RFID Card or Tag.....");
}
