#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

#include <UniversalTelegramBot.h>

#include <FastLED.h>

#define NUM_LEDS 300

#define DATA_PIN 2

CRGB leds[NUM_LEDS];


int modik = 1;
int bri = 50;

char ssid[] = "GandalfBigBrother";
char password[] = "92640314759262248292";

#define BOTtoken "1378114996:AAFoWYr6AQf6-QVuDcaHYAZ4c5QQEY3nk2c"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 300;
unsigned long lastTimeBotRan;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  client.setInsecure();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(2000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(bri);
  blackoff();
  FastLED.show();
  Serial.println("lenta OK");
}
/*
  void loop() {
  delay(5000);
  for (int lid = 0; lid <= 300; lid++) {
    leds[lid] = CHSV(31, 210, 255);
  }
  FastLED.show();

  delay(5000);
  blackoff();
  FastLED.show();

  }*/


void loop() {
  delay(5000);
  blackoff();
  FastLED.show();

  for (;;) {


    if (millis() > lastTimeBotRan + botRequestDelay)  {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      Serial.println(numNewMessages);
      if (numNewMessages) {
        while (numNewMessages) {
          Serial.println("got response");
          for (int i = 0; i < numNewMessages; i++) {
            bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");

            if (bot.messages[i].text == "Включить") {
              //todo
            }
            if (bot.messages[i].text == "Змейка") {
              modik = 5;
            }
            if (bot.messages[i].text == "Выключить") {
              modik = 1;
            }
            if (bot.messages[i].text == "Оранжевый") {
              modik = 2;
            }
            if (bot.messages[i].text == "Зеленый") {
              modik = 3;
            }


            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
          }

          lastTimeBotRan = millis();
        }
      }
      else {
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

      }
    }

  }
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
  }
}
void green() {
  for (int lid = 0; lid < NUM_LEDS; lid++) {
    leds[lid] = CRGB(0, 255, 0);
  }
}
