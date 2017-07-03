// ST Microelectronics CR14 Arduino library
// copyright Alexandre Iooss, 2017
// this code is public domain, enjoy!

#include "Arduino.h"
#include "led.h"

LED::LED(int pin_r, int pin_g, int pin_b) {
  _pin_r = pin_r;
  _pin_g = pin_g;
  _pin_b = pin_b;
}

void LED::begin() {
  pinMode(_pin_r, OUTPUT);
  pinMode(_pin_g, OUTPUT);
  pinMode(_pin_b, OUTPUT);  

  // Turn off
  analogWrite(_pin_r, 255);
  analogWrite(_pin_g, 255);
  analogWrite(_pin_b, 255);
}

void LED::set(int r, int g, int b) {
  analogWrite(_pin_r, 255-r%256);
  analogWrite(_pin_g, 255-g%256);
  analogWrite(_pin_b, 255-b%256);
}

