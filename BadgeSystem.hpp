#pragma once

#include <WiFi.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SS_PIN 5
#define RST_PIN 2
#define SCK 18
#define MISO 19
#define MOSI 23

#define OLED_SDA 21
#define OLED_SCL 22
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define OLED_RESET     -1

//#define BLACK  0x000000
//#define WHITE  0xFFFFFF
//#define GREEN  0x40FF00
//#define RED    0xFF0000
//#define ORANGE 0xF57538

extern Adafruit_SSD1306 display;

extern MFRC522 rfid;
extern MFRC522::MIFARE_Key key;

struct CardInfo {
  byte uid[4];
  const char* name;
  const char* role;
  bool  activate;
};

extern const char* ssid;
extern const char* password;
extern CardInfo DataBase[];
extern const int NUM_CARDS;


// DataBase
int CheckPermission();

// Display
void  AccessAllowed();
void  AccessBlocked();
void  AccessDenied();
