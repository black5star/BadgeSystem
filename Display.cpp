
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
void  WelcomeAdmin() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(23, 17);
  display.println("WELCOME");
  display.setCursor(30, 40);
  display.println("ADMIN");
  display.display();
  
  Serial.println("WELCOME ADMIN.");
  Serial.println("click a botton.");
  
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  255);
}
void  MemberRemoved() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(30, 17);
  display.println("MEMBER");
  display.setCursor(23, 40);
  display.println("REMOVED");
  display.display();
  
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  255);
}
void  MemberInserted() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(30, 17);
  display.println("MEMBER");
  display.setCursor(20, 40);
  display.println("INSERTED");
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
