// ST Microelectronics CR14 Arduino library
// copyright Alexandre Iooss, 2017
// this code is public domain, enjoy!

// This library is based on the ST Microelectronics CR14 datasheet
// and inspired by https://github.com/ccarlo64/nabaztag_raspberry/blob/master/test_rfid.py

#ifndef RFID_CR14_h
#define RFID_CR14_h

#include "Arduino.h"

#define REGISTER_PARAM byte(0x00)  // Parameter Register
#define REGISTER_FRAME byte(0x01)  // Input/Output frame Register
#define REGISTER_AUTH byte(0x02)   // Authenticate Register
#define REGISTER_SLOT byte(0x03)   // Slot marker Register
#define CMD_ON byte(0x10)
#define CMD_OFF byte(0x00)

const byte cmdInitiate[3]  =  {0x02, 0x06, 0x00};
const byte cmdGetTagUid[2] = {0x01, 0x0B};

class RFID {
  public:
    RFID(byte addr);
    void begin();  // Turn off and on to reset the device
    bool detect();  // Detect if a tag is nearby
    void read(byte *buffer);  // Try to read the tag
  private:
    byte _addr;
};

#endif

