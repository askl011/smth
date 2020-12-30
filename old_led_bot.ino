#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <UniversalTelegramBot.h>
#include <FastLED.h>
// Initialize Wifi connection to the router
char ssid[] = "askl";     // your network SSID (name)
char password[] = "horseeatmybike"; // your network key

// Initialize Telegram BOT
#define BOTtoken "1300941401:AAHn-hM6qvRilJFJXPt1B004NXZx--bCmJs"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//Checks for new messages every 1 second.
int botRequestDelay = 500;
unsigned long lastTimeBotRan;


#define NUM_LEDS 120
#define DATA_PIN 4
CRGB leds[NUM_LEDS];
int led_brightness = 2.55 * 50, warm_temp = 150;
CHSV led_color;
String mainKeyboard = "[[\"цвет\",\"яркость\"],[ \"режим\", \"выключить\"]]";
String colorKeyboard = "[[\"холодный\", \"теплый\", \"холоднее\", \"теплее\"],[\"красный\", \"зеленый\", \"синий\", \"кастом\", \"назад\"]]";
String modeKeyboard = "[[\"нормальный\"],[\"пульсации\", \"волна\", \"назад\"]]";
String brightnessKeyboard = "[[\"+10\",\"+5\",\"+1\",\"-1\",\"-5\", \"-10\"],[\"10%\", \"30%\", \"50%\", \"70%\", \"100%\", \"назад\"]]";
String customKeyboard = "[[\"R+\",\"G+\",\"B+\",\"тык\"],[\"R-\",\"G-\",\"B-\",\"назад\"]]";
void setup() {
  Serial.begin(115200);

  // This is the simplest way of getting this working
  // if you are passing sensitive information, or controlling
  // something important, please either use certStore or at
  // least client.setFingerPrint
  client.setInsecure();

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
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
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  int i = 0;
  do {
    leds[i] = CRGB::Black;
    i++;
  } while (i < NUM_LEDS) ;
  FastLED.show();
  FastLED.setBrightness(led_brightness);
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      for (int i = 0; i < numNewMessages; i++) {
        message_handler(bot.messages[i].text, String(bot.messages[i].chat_id));
        //  bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
        // Serial.println(bot.messages[i].text);
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}
void message_handler(String text, String chat_id) {

  if (text == "/start" || text == "назад") {
    bot.sendMessageWithReplyKeyboard(chat_id, "Главное меню", "", mainKeyboard, true);
  }
  else if (text == "цвет") {
    bot.sendMessageWithReplyKeyboard(chat_id, "Настрока цвета", "", colorKeyboard, true);
  }
  else if (text == "режим") {
    bot.sendMessageWithReplyKeyboard(chat_id, "Выбор режима", "", modeKeyboard, true);
  }
  else if (text == "яркость") {
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, "Текущая яркость:" + String(percent_brightness) + "%", "");
    bot.sendMessageWithReplyKeyboard(chat_id, "Настройка яркости", "", brightnessKeyboard, true);
  }
  else if (text == "кастом") {
    /*int percent_brightness = led_brightness / 2.55;
      bot.sendMessage(chat_id, "Текущая яркость:" + String(percent_brightness) + "%", "");*/
    bot.sendMessageWithReplyKeyboard(chat_id, "Свой цвет", "", customKeyboard, true);
  }
  else if (text == "+10") {
    led_brightness += 10 * 2.55;
    led_brightness > 255 ? led_brightness = 255 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "+5") {
    led_brightness += 5 * 2.55;
    led_brightness > 255 ? led_brightness = 255 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "+1") {
    led_brightness += 1 * 2.55;
    led_brightness > 255 ? led_brightness = 255 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "-10") {
    led_brightness -= 10 * 2.55;
    led_brightness < 1 ? led_brightness = 1 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "-5") {
    led_brightness -= 5 * 2.55;
    led_brightness < 1 ? led_brightness = 1 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "-1") {
    led_brightness -= 1 * 2.55;
    led_brightness < 1 ? led_brightness = 1 : led_brightness * 1;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "10%") {
    led_brightness = 10 * 2.55;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "30%") {
    led_brightness = 30 * 2.55;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "50%") {
    led_brightness = 50 * 2.55;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "70%") {
    led_brightness = 70 * 2.55;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "100%") {
    led_brightness = 100 * 2.55;
    int percent_brightness = led_brightness / 2.55;
    bot.sendMessage(chat_id, String(percent_brightness) + "%", "");
    FastLED.setBrightness(led_brightness);
    FastLED.show();
  }
  else if (text == "холодный") {
    led_color = CHSV(60, 0, 255);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    bot.sendMessage(chat_id, "White_ok", "");
  }
  else if (text == "теплый") {
     warm_temp =150;
    led_color = CHSV(60, warm_temp, 255);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = led_color;
    }
    FastLED.show();
    bot.sendMessage(chat_id, "WarmWhite_ok", "");
  }
  else if (text == "теплее") {
    warm_temp += 10;
    warm_temp > 255 ? warm_temp = 255 : warm_temp * 1;
    //  int percent_warm = warm_temp / 2.55;
    led_color = CHSV(60, warm_temp, 255);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = led_color;
    }
    FastLED.show();
    bot.sendMessage(chat_id, String(warm_temp) + " ", "");
  }
  else if (text == "холоднее") {
    warm_temp -= 10;
    warm_temp < 1 ? warm_temp = 1 : warm_temp * 1;
    // int percent_warm = warm_temp / 2.55;
    led_color = CHSV(60, warm_temp, 255);
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = led_color;
    }
    FastLED.show();
    bot.sendMessage(chat_id, String(warm_temp) + " ", "");
  }
  else if (text == "синий") {
  //  led_color = CRGB::Blue;
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::Blue;
    }
    FastLED.show();
    // delay(500);
    bot.sendMessage(chat_id, "Синий_ok", "");
  }
  else if (text == "красный") {
   // led_color = CRGB::Red;
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
    }
    FastLED.show();
    //  delay(500);
    bot.sendMessage(chat_id, "Красный_ok", "");
  }
  else if (text == "зеленый") {
   // led_color = CRGB::Green;
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
    //  delay(500);
    bot.sendMessage(chat_id, "Зеленый_ok", "");
  }
  else if (text == "выключить") {
    //led_color = CRGB::Black;
    for (int i = 0; i <= NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    //  delay(500);
    bot.sendMessage(chat_id, "Выключено", "");
  }
  else if (text == "тык") {
    bot.sendMessage(chat_id, "Не тыкай", "");
  }


}
