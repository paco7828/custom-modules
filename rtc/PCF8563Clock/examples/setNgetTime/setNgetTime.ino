#include <PCF8563Clock.h>

PCF8563Clock rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin();

  // Set the time: second, minute, hour, dayOfMonth, dayOfWeek, month, year
  rtc.setTime(2, 4, 10, 16, 4, 1, 25); // 2025/01/16 10:04:02
  Serial.println("Time set!");
}

void loop() {
  // Print the formatted time and date
  Serial.println("Time: " + rtc.getFormattedTime());
  Serial.println("Date: " + rtc.getFormattedDate());
  delay(1000);
}
