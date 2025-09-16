
#include "BadgeSystem.hpp"

int CheckPermission() {
  for (int i = 0; i < NUM_CARDS; i++) {
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
