#include <M5Stack.h>
#include <FastLED.h>

#define LED_PIN     15 // Matrix Signal
#define NUM_LEDS    64 // number of all LEDs in Matrix
#define BRIGHTNESS 10 // Brightness level 0-255
#define LED_TYPE    WS2811 //type
#define COLOR_ORDER GRB // Color
CRGB leds[NUM_LEDS];
#define daleytime 500 // delay time in milliseconds


void setup() {
  M5.begin();
  M5.Lcd.setCursor(120, 110, 4);
  M5.Lcd.println("Matrix");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );// set Matrix LEDs
  FastLED.setBrightness(BRIGHTNESS);// set Brightness
}
void loop() {
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB(255, 0, 0);
    leds[i + 16] = CRGB(0, 0, 0);
    leds[i + 32] = CRGB(0, 0, 0);
    leds[i + 48] = CRGB(0, 0, 0);
  } // first 2 lines is all red.
  FastLED.show(); // Turn on LEDs
  delay(daleytime);
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB(0, 0, 0);
    leds[i + 16] = CRGB(0, 255, 0);
    leds[i + 32] = CRGB(0, 0, 0);
    leds[i + 48] = CRGB(0, 0, 0);
  } //Next 2 lines is all Green.
  FastLED.show(); // Turn on LEDs
  delay(daleytime);
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB(0, 0, 0);
    leds[i + 16] = CRGB(0, 0, 0);
    leds[i + 32] = CRGB(0, 0, 255);
    leds[i + 48] = CRGB(0, 0, 0);
  } //Next 2 lines is all Blue.
  FastLED.show(); // Turn on LEDs
  delay(daleytime);
  for (int i = 0; i < 16; i++) {
    leds[i] = CRGB(0, 0, 0);
    leds[i + 16] = CRGB(0, 0, 0);
    leds[i + 32] = CRGB(0, 0, 0);
    leds[i + 48] = CRGB(128, 128, 0);
  } //Last 2 lines is all Yellow.
  FastLED.show(); // Turn on LEDs
  delay(daleytime);
}
