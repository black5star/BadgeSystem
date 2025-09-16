#pragma once

#include <WiFi.h>
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 22
#define RST_PIN 2
#define SCK 18
#define MISO 19
#define MOSI 23

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

int CheckPermission();
