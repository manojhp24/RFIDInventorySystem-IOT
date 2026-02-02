#include "esp32-hal.h"
#include "HardwareSerial.h"
#include "WString.h"
#include "Systemcontroller.h"

#include "Feedback.h"
#include "RFIDReader.h"
#include "WIFIManager.h"
#include "FirebaseService.h"
#include "secrets.h"
#include "pins.h"

// =========== Forward controllers ============

static void initSystem();
static void handleRFIDScan();
static bool waitForFirebaseReady();


// ============= Global objects ================

RFIDReader rfidReader(RFID_SS_PIN, RFID_RST_PIN);
Feedback feedback(LED_PIN, BUZZER_PIN);
WiFiManager wifi(WIFI_SSID, WIFI_PASSWORD);
FirebaseService firebase(API_KEY, DATABASE_URL, USER_EMAIL, USER_PASSWORD);


void systemSetup(){
  initSystem();
}

void systemLoop(){
  firebase.loop();

	if (!waitForFirebaseReady())
		return;

	handleRFIDScan();
}



// ===== Internal functions =====

static void initSystem() {
	Serial.begin(9600);

	wifi.connect();
	firebase.begin();

	rfidReader.begin();
	feedback.begin();

	Serial.println("System Ready. Scan RFID...");
}



// ===== RFID scan handler =====
static void handleRFIDScan() {
	if (!rfidReader.isCardDetected()) return;

	String uid = rfidReader.getUID();
	feedback.success();

  Serial.print("Scanned UID: ");
  Serial.print(uid);

  firebase.checkHandlerAuthorization(uid);

	rfidReader.halt();
}


static bool waitForFirebaseReady() {
	static bool lastState = false;
	bool currentState = firebase.ready();

	if (currentState != lastState) {
		Serial.println(
		  currentState ? "Firebase ready" : "Waiting for Firebase auth...");
		lastState = currentState;
	}

	return currentState;
}

