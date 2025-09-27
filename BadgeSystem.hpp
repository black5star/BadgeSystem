#pragma once

//#include <WiFi.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//RFID READER PINS
#define SS_PIN    5
#define RST_PIN   2
#define SCK      18
#define MISO     19
#define MOSI     23

//RGB LIGHT PINS
#define PIN_RED    33 // green
#define PIN_GREEN  25 // red
#define PIN_BLUE   32 // blue

//BOTTON PINS
#define BLACK_BUTTON  36
#define BLUE_BUTTON   35
#define YELLOW_BUTTON 34 

//OLED PINS
#define OLED_SDA        21
#define OLED_SCL        22
#define SCREEN_HEIGHT   64
#define SCREEN_WIDTH   128
#define OLED_RESET      -1

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
  bool masterCard;
};


//extern const char* ssid;
//extern const char* password;
extern CardInfo *DataBase;
extern const int NUM_CARDS;
extern int dbSize;

// DataBase
bool initDataBase();
int findMember();
int manageDataBase();

// Display
void  AccessAllowed();
void  AccessBlocked();
void  AccessDenied();
void  ClearDisplay();
