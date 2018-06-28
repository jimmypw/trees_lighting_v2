/*
 * The 2000 Trees lighting system v2
 * 
 * Design Goals:
 * Look Impressive
 * Low power (Needs to be run off a battery for many hours)
 * 
 * Inputs:
 * - Analogue input for switching the pattern
 * - Analogue input for adjusting a variable where available.
 * 
 * Outputs:
 * - 1x data connection for ws2812b led strip.
 * 
 */

#include "FastLED.h"

#define DEBUG true

#define NUM_LEDS 150

// Which pin is connected to the neopixel
#define PIN_LEDSTRIP 3

// Total number of defined patterns
#define MAX_PATTERNS 8

// Which pin is assigned to pattern selector pot
#define PIN_PATTERNSELECT A0

// Which pin is assigned to pattern vaiable pot
#define PIN_PATTERNSETTING A1

#define FRAMES_PER_SECOND 60

// Data structure containing LED information.
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, PIN_LEDSTRIP, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.delay(1000/FRAMES_PER_SECOND);
  FastLED.clear(true);
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
}

void loop() {
  double iTime = seconds_with_ms();
  #ifdef DEBUG
  //Serial.println(iTime);
  #endif
  int pattern_setting = analogRead(PIN_PATTERNSETTING);
  int pattern = normalise_pattern_selector(analogRead(PIN_PATTERNSELECT));
  
  switch (pattern) {
    case 1:
      do_pattern(solidwhite, iTime, pattern_setting);
      break;
    case 2:
      do_pattern(rainbow, iTime, pattern_setting);
      break;
    case 3:
      do_pattern(solidrainbowslow, iTime, pattern_setting);
      break;
    case 4:
      do_pattern(solidrainbowfast, iTime, pattern_setting);
      break;
    case 5:
      do_pattern(solidcolour, iTime, pattern_setting);
      break;
    case 6:
      //do_pattern(&rainbow, iTime);
      break;
    case 7:
      //do_pattern(&rainbow, iTime);
      break;
    case 8:
      //do_pattern(&rainbow, iTime);
      break;
  }

  FastLED.show();
}

