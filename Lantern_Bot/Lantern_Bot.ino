#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>

// TODO: Change Async library
#include <ESPAsyncWebSrv.h>
#include <FastLED.h>

#include "index.h"

const char* ssid = "SSID_GOES_HERE";
const char* password = "PASSWORD_GOES_HERE";

// Params for GET request
const char* STATE_PARAM = "state";
const char* COLOR_PARAM = "color";
const char* LED_PARAM = "led";

AsyncWebServer server(80);

#define NUM_LEDS 24
#define DATA_PIN 23
CRGB leds[NUM_LEDS];

void setup(){

  Serial.begin(115200);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  WiFi.mode(WIFI_STA);
  WiFi.setHostname("esp32");
  WiFi.begin(ssid, password);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/power", HTTP_GET, [](AsyncWebServerRequest *request) {

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");

    String state;

    if (request->hasParam(STATE_PARAM)) {

      state = request->getParam(STATE_PARAM)->value();

      if(state == "1") {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::White;
        }
        FastLED.show();
      } else if(state == "0") {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Black;
        }
        FastLED.show();
      }
    }
    else {
      state = "null";
    }

    Serial.print("POWER: ");
    Serial.println(state);

    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);

  });

  server.on("/color", HTTP_GET, [](AsyncWebServerRequest *request) {

    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");

    String state;

    if (request->hasParam(COLOR_PARAM)) {

      state = request->getParam(COLOR_PARAM)->value();

      if (state == "red") {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Red;
        }
        FastLED.show();
      } else if (state == "green") {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Green;
        }
        FastLED.show();
      } else if (state == "blue") {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::Blue;
        }
        FastLED.show();
      } else {
        state = "null";
      }

    }

    Serial.print("COLOR: ");
    Serial.println(state);

    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);

  });

  // Start server
  server.begin();
}

void loop() {
}
