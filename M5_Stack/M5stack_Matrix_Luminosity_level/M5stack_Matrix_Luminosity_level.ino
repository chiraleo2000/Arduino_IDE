#include <M5Stack.h>
#include <FastLED.h>
//PINs Setting
const int ana_LDR = 35; // LDR Analog

#define LED_PIN     15 // Matrix Signal
#define NUM_LEDS    64 // number of all LEDs in Matrix
#define LED_TYPE    WS2811 //type
#define COLOR_ORDER GRB // Color
#define BRIGHTNESS 10 // Brightness level 0-255
CRGB leds[NUM_LEDS];
#define daleytime 500 // delay time in milliseconds

void setup() {
  M5.begin();
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );// set Matrix LEDs
  M5.Lcd.setCursor(100, 0, 4);
  M5.Lcd.printf("Luminosity");
  FastLED.setBrightness(BRIGHTNESS);// set Brightness
}
void loop() {
  uint16_t luminosity = analogRead(ana_LDR); // LDR Analog reading
  int num_LED = (luminosity + 1) / 64; //
  M5.Lcd.setCursor(80, 40, 4); 
  M5.Lcd.printf("   Analog: %0d   ", luminosity);
  M5.Lcd.setCursor(20, 80, 4);
  M5.Lcd.printf("   Number of LEDS on: %0d   ", num_LED);
  matrix(num_LED); // Function to set of turn Leds in specific number from Luminosity
  resetting(); // Turn off LEDs for reset everytimes before changing
}
void matrix(int k) {
  for (int i = 0; i < k; i++) {
    if (i > 47) {
      leds[i] = CRGB(255, 0, 0);
    }
    else if (i > 31) {
      leds[i] = CRGB(128, 64, 64);
    }
    else if (i > 15) {
      leds[i] = CRGB(128, 128, 0);
    }
    else {
      leds[i] = CRGB(0, 255, 0);
    }
  }
  FastLED.show();
  delay(daleytime);
}
void resetting() {
  for (int i = 0; i < 64; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}
