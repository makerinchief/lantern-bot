/*
  Lantern Bot ESP32
  Justin C Kirk

  Makerinchief 
  www.makerinchief.com
  info@makerinchief.com

  Please read README.md for details

*/

#include <FastLED.h>
#include "colors.hpp"

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
