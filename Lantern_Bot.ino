/*
  Lantern Bot ESP32
  Justin C Kirk

  Makerinchief 
  www.makerinchief.com
  info@makerinchief.com

  Please read README.md for details
*/

#include <FastLED.h>
#include "colors.h"

//PWM Pin to control LEDs
const int LED_PIN = 9;

//Number of leds in each segment
const int LEDS_PER_SEGMENT = 6;

//Number of segments in lantern
const int SEGMENT_COUNT = 8;

//Number of leds for lantern
const int LED_COUNT = SEGMENT_COUNT * LEDS_PER_SEGMENT;

//Then all the leds can be represented by a grid of numbers
int lantern_segments[SEGMENT_COUNT][LEDS_PER_SEGMENT] = {0};

CRGB leds[LED_COUNT];
byte leds_brightness = 100;

void lantern_init_grid() {

  int led_num = 0;

  for (int i = 0; i < SEGMENT_COUNT; i++) {
    for (int j = 0; j < LEDS_PER_SEGMENT; j ++ ) {
      lantern_segments[i][j] = led_num;
      led_num += 1;
    }
  }
}

void lantern_init() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(50);
  lantern_init_grid();
}

void lantern_update() {
  FastLED.show();
}

void set_led_color(int led_num, CRGB led_color) {
  leds[led_num] = led_color;
}

void set_color(CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
}

void set_brightness(byte value) {
  FastLED.setBrightness(value);
}

void set_segment_color(int segment, CRGB color) {
  for (int i = 0; i < LEDS_PER_SEGMENT; i++) {    
    int led_num = lantern_segments[segment][i];    
    set_led_color(led_num, color);
  }
  Serial.println();
}

// ACTIONS/SCRIPTS

//Turns each led on, one at a time.
void single_file(int delay_time, CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    set_led_color(i, color);
    delay(delay_time);
  }
}


void setup() {
  Serial.begin(115200);
  
  lantern_init();

  set_segment_color(0, red);
  set_segment_color(1, green);
  set_segment_color(2, blue);
  set_segment_color(3, magenta);
  set_segment_color(4, yellow);
  set_segment_color(5, cyan);
  set_segment_color(6, orange);
  set_segment_color(7, light_blue);
  
  lantern_update();
  
}

void loop() {
}
