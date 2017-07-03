// RGB LED Arduino library
// copyright Alexandre Iooss, 2017
// this code is public domain, enjoy!

#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED {
  public:
    LED(int pin_r, int pin_g, int pin_b);
    void begin();
    void set(int r, int g, int b);
  private:
    int _pin_r;
    int _pin_g;
    int _pin_b;
};

#endif

