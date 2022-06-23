#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int ledpin = 13;
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0); //ต่อกับขา inerrupt 0 => ในที่นี้คือขา #2
}
void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    if (value == 10) {
      digitalWrite(ledpin, HIGH);
      Serial.println(mySwitch.getReceivedValue());
    }
    else {
      digitalWrite(ledpin, LOW);
      Serial.println( mySwitch.getReceivedValue() );
    }
    mySwitch.resetAvailable();
  }
}
