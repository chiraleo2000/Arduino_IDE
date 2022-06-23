#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
void setup() {
  mySwitch.enableTransmit(10); // Using Pin #10
}
void loop() {
  mySwitch.send(10, 24);
  delay(1000);
  mySwitch.send(20, 24);
  delay(1000);
}
