#include <Wire.h>
#include "MFRC522_I2C.h"
#include <M5Stack.h>
MFRC522 mfrc522(0x28);
void setup() {
  M5.begin();
  Wire.begin();
  M5.Lcd.setCursor(140, 0, 4);
  M5.Lcd.println("RFID");
  mfrc522.PCD_Init(); 
  M5.Lcd.setCursor(0, 30, 2);
  M5.Lcd.println("scan PICC to see UID");

}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  {
    delay(50);
    return;
  }
  M5.Lcd.setCursor(0, 100, 4);
  String ID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    ID += String(mfrc522.uid.uidByte[i], HEX);
  }
  M5.Lcd.printf("UID: %s ", ID);
  M5.Speaker.tone(500);
  delay(250);
  M5.Speaker.mute();
}
