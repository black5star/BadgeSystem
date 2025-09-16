
#include "BadgeSystem.hpp"

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; 

const char* ssid = "MAKERS_IOT";
const char* password = "1337@IOT";
  
CardInfo DataBase[] = {
  {{0xB3, 0x1B, 0x80, 0x1B}, "BlackStar", "Admin", true},
  {{0x57, 0x39, 0x23, 0x03}, "Paper", "Owner", false},
};
const int NUM_CARDS = sizeof(DataBase) / sizeof(CardInfo);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(500);
  
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 25);
  display.println("Connected");
  display.display();
  
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  SPI.begin(SCK, MISO, MOSI, SS_PIN);

  rfid.PCD_Init();
  delay(100);

  byte version = rfid.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.print("RFID Reader Firmware Version: 0x");
  Serial.println(version, HEX);
  if (version == 0x00 || version == 0xFF) {
    Serial.println("ERROR: RFID reader not connected or not working.");
    while (true);
  }

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println("Ready to scan RFID cards...");
}


void loop() {

  if (!rfid.PICC_IsNewCardPresent()) {
    delay(100);
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Failed to read card.");
    return;
  }
  int indx = CheckPermission();
  if (indx == -1){
    AccessDenied();
    Serial.println("ID NOT FOUND.");
  } else if (DataBase[indx].activate == false) {
    AccessBlocked();
    Serial.println("ACCESS DENIED.");
  } else {
    AccessAllowed();
    Serial.println("ACCESS ALLOWED.");
  }
  
//  Serial.print("Card UID: ");
//  for (byte i = 0; i < rfid.uid.size; i++) {
//    if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
//    Serial.print(rfid.uid.uidByte[i], HEX);
//    Serial.print(" ");
//  }
//  Serial.println();

  rfid.PICC_HaltA();       
  rfid.PCD_StopCrypto1();

  delay(3000);
  ClearDisplay();
  
}
