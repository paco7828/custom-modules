#ifndef PCF8563Clock_h
#define PCF8563Clock_h

#include <Arduino.h>
#include <Wire.h>

class PCF8563Clock
{
public:
  PCF8563Clock(uint8_t address = 0x51);
  void begin();
  void setTime(byte second, byte minute, byte hour, byte dayOfMonth, byte dayOfWeek, byte month, byte year);
  void getTime(byte &second, byte &minute, byte &hour, byte &dayOfMonth, byte &dayOfWeek, byte &month, byte &year);

  String getFormattedTime();
  String getFormattedDate();
  String getYear();
  String getMonth();
  String getDayNum();
  String getHour();
  String getMinute();
  String getSecond();

private:
  uint8_t _address;
  byte bcdToDec(byte value);
  byte decToBcd(byte value);
};

#endif