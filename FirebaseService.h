#ifndef FIREBASESERVICE_H
#define FIREBASESERVICE_H

#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <FirebaseClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

class FirebaseService{
  private:
    UserAuth userAuth;
    FirebaseApp app;
    WiFiClientSecure sslClient;
    AsyncClientClass asyncClient;
    RealtimeDatabase database;

    static void processData(AsyncResult &aResult);

  public:
    FirebaseService(
      const char* apiKey,
      const char* dbUrl,
      const char* email,
      const char* password
    );

    void begin();
    void loop();
    bool ready();
    void writeTestData();
    void checkHandlerAuthorization(const String& uid);
};



#endif