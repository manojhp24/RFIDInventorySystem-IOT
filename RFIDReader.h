#include "Arduino.h"
#include "WString.h"
#ifndef RFIDREADER_H
#define RFIDREADER_H

#include <SPI.h>
#include <MFRC522.h>

class RFIDReader {
  MFRC522 rfid;

public:
  RFIDReader(byte ssPin, byte rstPin)
    : rfid(ssPin, rstPin) {}

  void begin() {
    SPI.begin(18, 19, 23, 5);
    rfid.PCD_Init();
  }

  bool isCardDetected() {
    if (!rfid.PICC_IsNewCardPresent()) return false;
    if (!rfid.PICC_ReadCardSerial()) return false;

    return true;
  }

  void printUID() {
    Serial.print("UID:");
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      Serial.print("");
    }
    Serial.println();
  }

  void halt(){
    rfid.PICC_HaltA();
  }

  String getUID(){
    String uid = "";
    for(byte i = 0; i < rfid.uid.size;i++){
      uid += String(rfid.uid.uidByte[i],HEX);
    }
    uid.toUpperCase();
    return uid;
  }
};

#endif