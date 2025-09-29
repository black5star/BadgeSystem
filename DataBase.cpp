
#include "BadgeSystem.hpp"

bool initDataBase() {
  dbSize = 0;
  DataBase = (CardInfo*) malloc(sizeof(CardInfo));
  if (DataBase != nullptr) {
    byte defaultUID[4] = {0xB3, 0x1B, 0x80, 0x1B};
    memcpy(DataBase[0].uid, defaultUID, 4);
    DataBase[0].masterCard = true;
    dbSize = 1;
    return true;
  }
  return false;
}

int findMember() {
  for (int i = 0; i < dbSize; i++) {
    bool match = true;
    for (int j = 0; j < rfid.uid.size; j++) {
      if (rfid.uid.uidByte[j] != DataBase[i].uid[j]) {
        match = false;
        break;
      }
    }
    if (match) return i;
  }
  return -1;
}

bool InsertMember() {  
  rfid.PICC_HaltA();       
  rfid.PCD_StopCrypto1();
  while (!rfid.PICC_IsNewCardPresent()) {
    bool black = digitalRead(BLACK_BUTTON);
    bool yellow = digitalRead(YELLOW_BUTTON);
    bool blue = digitalRead(BLUE_BUTTON);
    if(black == HIGH && yellow == LOW && blue == LOW){
      Serial.println("Black ");
      return 0;
    }
    delay(100);
  }
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Failed to read card.");
    return false;
  }
  if (findMember() != -1) {
    Serial.println("Already exist");
    return false;
  }
  CardInfo* temp = (CardInfo *) realloc(DataBase, sizeof(CardInfo) * (dbSize + 1));
  if (temp == nullptr) {
    Serial.println("Failed to allocate memory!");
    return false;
  }
  DataBase = temp;
  for (int i = 0; i < 4; i++) {
    DataBase[dbSize].uid[i] = rfid.uid.uidByte[i];
  }
  DataBase[dbSize].masterCard = false;

  dbSize++;
  MemberInserted();
  Serial.println("Member inserted.");
  return true;
}

bool  RemoveMember() {
  rfid.PICC_HaltA();       
  rfid.PCD_StopCrypto1();
  while (!rfid.PICC_IsNewCardPresent()) {
    bool black = digitalRead(BLACK_BUTTON);
    bool yellow = digitalRead(YELLOW_BUTTON);
    bool blue = digitalRead(BLUE_BUTTON);
    if(black == HIGH && yellow == LOW && blue == LOW){
      Serial.println("Black ");
      return 0;
    }
    delay(100);
  }
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Failed to read card.");
    return false;
  }
  int indx = findMember();
  if (indx == -1) {
    Serial.println("Card not found, cannot remove.");
    return false;
  }
  if (DataBase[indx].masterCard == true) {
    Serial.println("It's masterCard, cannot remove.");
    return false;
  }
  for (int i = indx; i < dbSize - 1; i++) {
    DataBase[i] = DataBase[i + 1];
  }
  CardInfo* temp = (CardInfo*) realloc(DataBase, (dbSize - 1) * sizeof(CardInfo));
  if (temp == nullptr && dbSize - 1 > 0) {
    Serial.println("Failed to shrink memory, but removal proceeded.");
    dbSize--;
    MemberRemoved();
    Serial.println("Member removed.");
    return true;
  }
  DataBase = temp;
  dbSize--;
  MemberRemoved();
  Serial.println("Member removed.");
  return true;
}

int manageDataBase() {
  while (true) {
    bool black = digitalRead(BLACK_BUTTON);
    bool yellow = digitalRead(YELLOW_BUTTON);
    bool blue = digitalRead(BLUE_BUTTON);
    
    if(black == HIGH && yellow == LOW && blue == LOW){
      Serial.println("Black ");
      return 0;
    }
    if (black == LOW && yellow == HIGH && blue == LOW){
      Serial.println("Yellow ");
      InsertMember();
      return 1;
    }
    if (black == LOW && yellow == LOW && blue == HIGH) {
      Serial.println("Blue ");
      RemoveMember();
      return 2;
    } 
    delay(100);
  }
  return 3;
}
