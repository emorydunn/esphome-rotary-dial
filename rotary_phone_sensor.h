#include "esphome.h"

class RotaryPhoneSensor : public Component, public Sensor {
  // constants won't change. They're used here to set pin numbers:
  const int controlPin = 14;  // Control, white, D5
  const int rotaryPin = 12;   // Rotary, blue, D6
  const int ledPin =  2;      // the number of the LED pin, D4

  // variables will change:
  // int rotaryState = 0;
  int lastRotaryState = 0;
  // int controlState = 0;
  int rotaryCount = 0;
 public:
  // RotaryPhoneSensor() : PollingComponent(1) {}
  void setup() override {
    // Serial.println("Rotary Phone MQTT Relay");
    // put your setup code here, to run once:
    pinMode(controlPin, INPUT_PULLUP);
    pinMode(rotaryPin, INPUT_PULLUP);
  }

  void loop() override {
      int controlState = digitalRead(controlPin);
      int rotaryState = digitalRead(rotaryPin);

      if (controlState == LOW) {
        // Control pin is open, begin counting
         ESP_LOGVV("Control open");

        if (rotaryState == LOW && rotaryState != lastRotaryState) {
          rotaryCount ++;
           ESP_LOGV("Rotary open", "Count: %i", this->rotaryCount);

          digitalWrite(ledPin, HIGH);
        } else {
          digitalWrite(ledPin, LOW);
        }
        // Delay a little bit to avoid bouncing
        delay(1);

      } else {
        if (rotaryCount != 0) {
          ESP_LOGD("Rotary closed", "Count: %i", this->rotaryCount);
          // Publish the count and reset
          publish_state(rotaryCount);
          rotaryCount = 0;

          // Delay, and then publish a default state
          delay(500);
          publish_state(rotaryCount);
        }
      }

      lastRotaryState = rotaryState;
  }
};