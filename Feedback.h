#include "esp32-hal-gpio.h"
#ifndef FEEDBACK_H
#define FEEDBACK_H

class Feedback {
  int ledPin;
  int buzzerPin;

public:
  Feedback(int led, int buzzer) {
    ledPin = led;
    buzzerPin = buzzer;
  }

  void begin() {
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    off();
  }

  void success() {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    off();
  }

  void off(){
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin,LOW);
  
  }
};

#endif