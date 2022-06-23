#include <M5Stack.h>
// define state
enum State {start, wait, closing, closed, opening, opened};
enum State myState;

//timing
unsigned long wait_timer = 0;
const long wait_time = 6000;

unsigned long closed_timer = 0;
const long closed_time = 6000;

unsigned long opened_timer = 0;
const long opened_time = 6000;

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  M5.Power.begin();

  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.println("State Machine");
  myState = start;
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.update();
  unsigned long currentMillis = millis();

  switch (myState)
  {
    case start:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      myState = wait;
      wait_timer = currentMillis;

      //clean screen
      M5.Lcd.setTextColor(BLACK);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("start 0");
      break;
    case wait:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("wait");
      if (currentMillis - wait_timer >= wait_time) {
        myState = closing;
        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("wait");
      }
      break;
    case closing:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("closing");
      if (M5.BtnA.wasReleased()) {
        myState = closed;
        closed_timer = currentMillis;

        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("closing");
      }
      if (M5.BtnB.wasReleased()) {
        myState = opening;
        closed_timer = currentMillis;

        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("closing");
      }
      break;
    case closed:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("closed");
      if (currentMillis - closed_timer >= closed_time) {
        myState = opening;
        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("closed");
      }
      break;
    case opening:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("opening");
      if (M5.BtnC.wasReleased()) {
        myState = opened;
        opened_timer = currentMillis;

        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("opening");
      }
      break;
    case opened:
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setCursor(3, 35);
      M5.Lcd.println("opened");
      if (currentMillis - opened_timer >= opened_time) {
        myState = closing;
        //clean screen
        M5.Lcd.setTextColor(BLACK);
        M5.Lcd.setCursor(3, 35);
        M5.Lcd.println("opened");
      }
      break;
    default:
      break;
  }
}
