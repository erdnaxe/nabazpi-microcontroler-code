# Makefile for an Arduino project (needs arduino-mk)
# Normal use : "make upload monitor" (open a screen)
# See "make help"

# Board parameters
BOARD_TAG   = nano
BOARD_SUB   = atmega168
MONITOR_PORT = /dev/ttyUSB0
MONITOR_BAUDRATE = 9600

# OS Specific
ARDMK_VENDOR = archlinux-arduino
ARDUINO_DIR = /usr/share/arduino

# Libraries
ARDUINO_LIBS = Wire Pushbutton

include /usr/share/arduino/Arduino.mk

