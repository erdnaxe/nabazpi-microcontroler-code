#include <Pushbutton.h>
#include <Wire.h>
#include "RFID.h"

#define PIN_HEAD_BTN 2  // must support interrupt
#define PIN_VOL_WHEEL A7

Pushbutton headButton(PIN_HEAD_BTN);
RFID rfid(0x50);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rfid.begin();
}

void loop() {
  // Volume control wheel
  int volumeSensorValue = analogRead(PIN_VOL_WHEEL);

  // Head button
  if (headButton.getSingleDebouncedPress()) {
    Serial.println(volumeSensorValue);
  }

  if (rfid.detect()) {
    Serial.println("RFID detected !");
    rfid.read();
  }

  delay(50);
}




