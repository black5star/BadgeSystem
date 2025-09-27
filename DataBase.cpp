
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
  while (!rfid.PICC_IsNewCardPresent()) {}
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
  Serial.println("Member inserted.");
  return true;
}

bool  RemoveMember() {
  rfid.PICC_HaltA();       
  rfid.PCD_StopCrypto1();
  while (!rfid.PICC_IsNewCardPresent()) {}
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
    Serial.println("Member removed.");
    return true;
  }
  DataBase = temp;
  dbSize--;
  return true;
}

int manageDataBase() {
  while (true) {
//    if(digitalRead(BLACK_BUTTON) == LOW){
//      return 0;
//    }
//    if (digitalRead(YELLOW_BUTTON) == LOW){
//      InsertMember();
//      return 1;
//    }
//    if (digitalRead(BLUE_BUTTON) == LOW) {
//      RemoveMember();
//      return 2;
//    } 

    Serial.print(digitalRead(BLACK_BUTTON));
    Serial.print(" black. ");
    Serial.print(digitalRead(YELLOW_BUTTON));
    Serial.print(" yellow. ");
    Serial.print(digitalRead(BLUE_BUTTON));
    Serial.println(" blue.");
    delay(1000);
  }
  Serial.println("no wait.");
  return 3;
}
