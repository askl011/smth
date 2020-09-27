#include <FastLED.h>

#define NUM_LEDS 8

#define DATA_PIN 11

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}
void loop() {
  for (int i = 0; i <= 6;i++) {
    for (int lid = 0; lid <= 7; lid++) {
      leds[lid] = CRGB(220, 20, 60);
    }
    for (int lid = 0+i; lid <= 2+i; lid++) {
      leds[lid] = CRGB(255, 170, 0);
    }
    FastLED.show();
    delay(500);

  }
}
