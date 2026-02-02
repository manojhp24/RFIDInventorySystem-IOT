#include "WString.h"
#include "FirebaseService.h"

FirebaseService::FirebaseService(
  const char* apiKey,
  const char* dbURL,
  const char* email,
  const char* password)
  : userAuth(apiKey, email, password),
    asyncClient(sslClient)

{
  database.url(dbURL);
}

void FirebaseService::begin() {
  sslClient.setInsecure();

  initializeApp(
    asyncClient,
    app,
    getAuth(userAuth),
    processData,
    "authTask");

  app.getApp<RealtimeDatabase>(database);
}

void FirebaseService::loop() {
  app.loop();
}

bool FirebaseService::ready() {
  return app.ready();
}

void FirebaseService::writeTestData() {
  if (!app.ready()) return;

  database.set<String>(
    asyncClient,
    "/test/status",
    "ESP32 Connected whoo",
    processData,
    "TEST_WRITE");
}


void FirebaseService::checkHandlerAuthorization(const String& uid) {
  if (!app.ready()) return;

  String path = "/handlers/" + uid + "/status";

  Serial.println("\n----------------------------");
  Serial.println("RFID Scan Detected");
  Serial.print("UID    : ");
  Serial.println(uid);
  Serial.println("Checking authorization...");

  String status = database.get<String>(asyncClient, path);

  if (status.length() == 0) {
    Serial.println("Result : UNAUTHORIZED (Unknown card)");
    Serial.println("----------------------------");
    return;
  }

  if (status == "authorized") {
    Serial.println("Result : AUTHORIZED HANDLER");
  } else {
    Serial.println("Result : UNAUTHORIZED HANDLER");
  }

  Serial.println("----------------------------");
}




void FirebaseService::processData(AsyncResult& aResult) {
  if (!aResult.isResult()) return;

  if (aResult.isError()) {
    Serial.print("Firebase error: ");
    Serial.println(aResult.error().message());
  }

  if (aResult.available()) {
    Serial.print("Firebase response: ");
    Serial.println(aResult.c_str());
  }
}