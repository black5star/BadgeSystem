
#include "BadgeSystem.hpp"

void  AccessAllowed() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(28, 17);
  display.println("ACCESS");
  display.setCursor(23, 40);
  display.println("ALLOWED");
  display.display();

  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 255);
  analogWrite(PIN_BLUE,  0);
}

void  AccessBlocked() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(28, 17);
  display.println("ACCESS");
  display.setCursor(23, 40);
  display.println("BLOCKED");
  display.display();
  
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  255);
}

void  AccessDenied() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(28, 17);
  display.println("ACCESS");
  display.setCursor(28, 40);
  display.println("DENIED");
  display.display();
  
  analogWrite(PIN_RED,   255);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  0);
}

void  ClearDisplay() {
  display.clearDisplay();

  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  0);
}
