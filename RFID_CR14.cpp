// ST Microelectronics CR14 Arduino library
// copyright Alexandre Iooss, 2017
// this code is public domain, enjoy!

#include "Arduino.h"
#include "RFID_CR14.h"
#include <Wire.h>

RFID::RFID(byte addr) {
  _addr = addr;
}

void RFID::begin() {
  // Reset
  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_PARAM);  // Move to register
  Wire.write(CMD_OFF);  // Write command
  Wire.endTransmission();

  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_PARAM);  // Move to register
  Wire.write(CMD_ON);  // Write command
  Wire.endTransmission();

  // Wait
  delay(50);
}

bool RFID::detect() {
  // Write initialisation sequence
  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_FRAME);  // Move to register
  Wire.write(cmdInitiate, 3);  // Write command
  Wire.endTransmission();
  delay(10);

  // Read state
  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_FRAME);
  Wire.endTransmission();
  Wire.requestFrom(_addr, 1);
  byte status = Wire.read();
  if (status) {
    return true;
  } else {
    return false;
  }
}

void RFID::read(byte *buffer) {
  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_SLOT);
  Wire.endTransmission();
  delay(50);

  Wire.beginTransmission(_addr);
  Wire.write(REGISTER_FRAME);
  Wire.endTransmission();
  byte tableChip[32];
  int i = 0;
  Wire.requestFrom(_addr, 32);
  while(Wire.available()) { 
    tableChip[i] = Wire.read();
    i++;
  }

  if (((tableChip[2] << 8) + tableChip[1]) > 0) {      
    byte wordBitIdx = (tableChip[2]<<8) + tableChip[1];

    for (int idxTmp=0; idxTmp<16; idxTmp++) {
      if (wordBitIdx & 0x0001) {
        // Select chip
        byte cmdSelectTag[3] = {0x02, 0x0E, 0x00};
        cmdSelectTag[2] = tableChip[idxTmp+3];
        Wire.beginTransmission(_addr);
        Wire.write(REGISTER_FRAME);
        Wire.write(cmdSelectTag, 3);
        Wire.endTransmission();
        delay(50);

        // Get uid mode
        Wire.beginTransmission(_addr);
        Wire.write(REGISTER_FRAME);
        Wire.write(cmdGetTagUid, 2);
        Wire.endTransmission();
        delay(50);

        // Read uid
        Wire.beginTransmission(_addr);
        Wire.write(REGISTER_FRAME);
        Wire.endTransmission();
        byte uid[32];
        int i = 0;
        Wire.requestFrom(_addr, 32);
        while(Wire.available()) { 
          uid[i] = Wire.read();
          i++;
        }

        for (int i=0; i<8; i++) {
          buffer[i] = uid[8-i];
        }
        
        return;  // Restrict to one tag only
      }
      wordBitIdx >>= 1;
    }
  }
}


