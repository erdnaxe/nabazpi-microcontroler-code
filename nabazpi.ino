#include <Pushbutton.h>
#include <Wire.h>
#include "RFID_CR14.h"

#define PIN_HEAD_BTN 2  // must support interrupt
#define PIN_VOL_WHEEL A7

Pushbutton headButton(PIN_HEAD_BTN);
RFID rfid(0x50);

unsigned int volumeSensorOldValue = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rfid.begin();
}

void loop() {
  // Volume control wheel
  unsigned int volumeSensorValue = analogRead(PIN_VOL_WHEEL);
  if (abs(volumeSensorValue-volumeSensorOldValue) > 5) {
    volumeSensorOldValue = volumeSensorValue;
    Serial.print("[VOL] Volume wheel value : ");
    Serial.println(volumeSensorValue);
  }

  // Head button
  if (headButton.getSingleDebouncedPress()) {
    Serial.println("[BTN] Button pushed");
  }

  // RFID reader
  if (rfid.detect()) {
    byte tag[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    rfid.read(tag);

    if (tag[0] == 0) {
      Serial.println("[RFID] read error !");
    } else {
      Serial.print("[RFID] your tag is : ");
      for (int i=0; i<8; i++) {
        String hexa = String(tag[i], HEX);
        if (hexa.length() < 2) {
          Serial.print("0");
        }
        Serial.print(hexa);
        Serial.print(" ");
      }
      Serial.println("");
    }
  }

  delay(50);
}


