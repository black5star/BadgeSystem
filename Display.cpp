
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
}
