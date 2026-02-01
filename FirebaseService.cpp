#include "FirebaseService.h"

FirebaseService::FirebaseService(
  const char* apiKey,
  const char* dbURL,
  const char* email,
  const char* password 
  )
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

bool FirebaseService::ready(){
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