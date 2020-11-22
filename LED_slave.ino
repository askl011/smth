#include <Wire.h>

#include <FastLED.h>

#define NUM_LEDS 300

#define DATA_PIN 6

CRGB leds[NUM_LEDS];

byte modik=1;

void setup() {
  Wire.begin(57);
  Wire.onReceive(risik);
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void loop() {
  Serial.println(modik);
  switch (modik) {
           case (1):
             blackoff();
             FastLED.show();
             break;
           case (2):
             orange();
             FastLED.show();
             break;
           case (3):
             green();
             FastLED.show();
             break;

           case (5):
             Serial.println("zm");
             zmeika();
             break;
         }
  delay(100);
}

void risik() {
  modik = Wire.read();
  Serial.println(modik);
}

void blackoff() {
  for (int lid = 0; lid < NUM_LEDS; lid++) {
    leds[lid] = CRGB(0, 0, 0);
  }
}
void orange() {
  for (int lid = 0; lid < NUM_LEDS; lid++) {
    leds[lid] = CRGB(240, 170, 0);
  }
}
void zmeika() {
  for (int i = 0; i <= NUM_LEDS; i++) {
    for (int lid = 0; lid <= NUM_LEDS; lid++) {
      leds[lid] = CRGB(178, 34, 34);
    }
    for (int lid = 0 + i; lid <= 10 + i; lid++) {
      leds[lid] = CRGB(0, 255, 255);
    }
    delay(50);
    FastLED.show();
    if(modik!=5){break;}
  }
}
void green() {
  for (int lid = 0; lid < NUM_LEDS; lid++) {
    leds[lid] = CRGB(0, 255, 0);
  }
}
