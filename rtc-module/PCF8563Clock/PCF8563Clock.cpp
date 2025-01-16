#include "PCF8563Clock.h"

PCF8563Clock::PCF8563Clock(uint8_t address) {
  _address = address;
}

void PCF8563Clock::begin() {
  Wire.begin();
}

byte PCF8563Clock::bcdToDec(byte value) {
  return ((value / 16) * 10 + value % 16);
}

byte PCF8563Clock::decToBcd(byte value) {
  return (value / 10 * 16 + value % 10);
}

void PCF8563Clock::setTime(byte second, byte minute, byte hour, byte dayOfMonth, byte dayOfWeek, byte month, byte year) {
  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

void PCF8563Clock::getTime(byte &second, byte &minute, byte &hour, byte &dayOfMonth, byte &dayOfWeek, byte &month, byte &year) {
  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.endTransmission();

  Wire.requestFrom(_address, (uint8_t)7);
  second = bcdToDec(Wire.read() & B01111111);
  minute = bcdToDec(Wire.read() & B01111111);
  hour = bcdToDec(Wire.read() & B00111111);
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek = bcdToDec(Wire.read() & B00000111);
  month = bcdToDec(Wire.read() & B00011111);
  year = bcdToDec(Wire.read());
}

String PCF8563Clock::getFormattedTime() {
  byte second, minute, hour, dayOfMonth, dayOfWeek, month, year;
  getTime(second, minute, hour, dayOfMonth, dayOfWeek, month, year);

  char buffer[9]; // Format HH:MM:SS
  snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, minute, second);
  return String(buffer);
}

String PCF8563Clock::getFormattedDate() {
  byte second, minute, hour, dayOfMonth, dayOfWeek, month, year;
  getTime(second, minute, hour, dayOfMonth, dayOfWeek, month, year);

  char buffer[11]; // Format YYYY/MM/DD
  snprintf(buffer, sizeof(buffer), "20%02d/%02d/%02d", year, month, dayOfMonth);
  return String(buffer);
}
