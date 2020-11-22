#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

#include <UniversalTelegramBot.h>
#include <Wire.h>

#define NUM_LEDS 300

#define DATA_PIN 2




byte modik = 1;
int bri = 50;

char ssid[] = "GandalfBigBrother";
char password[] = "92640314759262248292";

#define BOTtoken "1378114996:AAFoWYr6AQf6-QVuDcaHYAZ4c5QQEY3nk2c"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 300;
unsigned long lastTimeBotRan;

void setup() {
  Wire.begin();
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
  Serial.println("lenta OK");
}



void loop() {
  for (;;) {
    if (millis() > lastTimeBotRan + botRequestDelay)  {
      mast();
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      Serial.println(numNewMessages);
      while (numNewMessages) {
        Serial.println("got response");
        for (int i = 0; i < numNewMessages; i++) {
          bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");

          if (bot.messages[i].text == "Включить") {
            modik = 0;

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

  }
}
void mast() {
  Wire.beginTransmission(57);
  Wire.write(modik);
  Wire.endTransmission();
  delay(10);
}
