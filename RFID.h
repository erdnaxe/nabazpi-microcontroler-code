#ifndef RFID_h
#define RFID_h

#include "Arduino.h"

#define RFID_REGISTER_PARAM byte(0x00)  // Parameter Register
#define RFID_REGISTER_FRAME byte(0x01)  // Input/Output frame Register
#define RFID_REGISTER_AUTH byte(0x02)   // Authenticate Register
#define RFID_REGISTER_SLOT byte(0x03)   // Slot marker Register
#define RFID_CMD_ON byte(0x10)
#define RFID_CMD_OFF byte(0x00)

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

