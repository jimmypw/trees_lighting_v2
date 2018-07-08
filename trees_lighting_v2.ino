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

// Uncomment this to enable debug information to be sent over serial.
// Caution: This will kill the performance.
//#define DEBUG

#define NUM_LEDS 150

// Which pin is connected to the neopixel
#define PIN_LEDSTRIP 3

// Total number of defined patterns
#define MAX_PATTERNS 15

// Which pin is assigned to pattern selector pot
#define PIN_PATTERNSELECT A0

// Which pin is assigned to pattern vaiable pot
#define PIN_PATTERNSETTING A1

// Which pin will provide high power hack
#define PIN_HIGHPOWERHACK 6

// Rate limit the fastled library
#define FRAMES_PER_SECOND 60

// Data structure containing LED information.
CRGB leds[NUM_LEDS];

void high_power_hack(){
  /* 
   *  This function will relax the fastled power function for
   *  brighter LED output. While the buck converter is rated
   *  for 5A im restricting it to 4A just to contain power 
   *  usage a bit.
   *  
   *  I test with the internal pullup resistor so that the
   *  cable does not need to be connected to anything
   *  (to prevent any happy accidents) and high power mode
   *  will be enabled ONLY if the pin is connected to ground.
   *  
   *  I then set the pin mode to output and the state to low
   *  effectively connecting ground to ground if the cable is 
   *  connected and ground to nothing if the cable is not
   *  connected effectively removing all potential current draw.
   *  
   *  I should probably test this with a multimeter though.
   *  
   *  PIN_HIGHPOWERHACK must be connected to 
   *  ground (enable high power output)
   */
  pinMode(PIN_HIGHPOWERHACK, INPUT_PULLUP);
  if(digitalRead(PIN_HIGHPOWERHACK) == LOW){
    // Pin is connected to ground
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 4000);
  }else{
    // Pin is not connected,
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  }
  pinMode(PIN_HIGHPOWERHACK, OUTPUT);
  digitalWrite(PIN_HIGHPOWERHACK, LOW);
}

void startup() {
  do_pattern(rainbow_startup, 10.00, 1023);
  FastLED.show();
}

void setup() {
  FastLED.addLeds<WS2812B, PIN_LEDSTRIP, GRB>(leds, NUM_LEDS);
  high_power_hack();
  FastLED.delay(1000/FRAMES_PER_SECOND);
  FastLED.clear(true);
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  startup();
  delay(2000);
}

void loop() {
  const double iTime = seconds_with_ms();
  const int pattern_setting = analogRead(PIN_PATTERNSETTING);
  const int pattern = normalise_pattern_selector(analogRead(PIN_PATTERNSELECT));

  #ifdef DEBUG
  //Serial.print("iTime: ");
  //Serial.println(iTime);
  //Serial.print("pattern: ");
  //Serial.println(pattern);
  //Serial.print("pattern_setting: ");
  //Serial.println(pattern_setting);
  #endif
  
  switch (pattern) {
    case 1:
      do_pattern(solid_white, iTime, pattern_setting);
      break;
    case 2:
      do_pattern(solid_colour, iTime, pattern_setting);
      break;
    case 3:
      do_pattern(solid_rainbow_slow, iTime, pattern_setting);
      break;
    case 4:
      do_pattern(solid_rainbow_fast, iTime, pattern_setting);
      break;
    case 5:
      do_pattern(rainbow, iTime, pattern_setting);
      break;
    case 6:
      do_pattern(rainbow_variablecompress, iTime, pattern_setting);
      break;
    case 7:
      do_pattern(sparkle_white, iTime, pattern_setting);
      break;
    case 8:
      do_pattern(sparkle_varicol, iTime, pattern_setting);
      break;
    case 9:
      do_pattern(sparkle_rainbowphase, iTime, pattern_setting);
      break;
    case 10:
      do_pattern(solid_timestep, iTime, pattern_setting);
      break;
    case 11:
      do_pattern(saw_coloursaturationstep, iTime, pattern_setting);
      break;
    case 12:
      mix_pattern(sparkle_rainbowphase, 84, rainbow_variablecompress, 512,  0.0478, iTime);
      break;
    case 13:
      mix_pattern(rainbow_variablecompress, 1024, rainbow_variablecompress, 512,  0.50, iTime);
      break;
    case 14:
      mix_pattern(sparkle_rainbowphase, 84, sparkle_white, 1024,  0.50, iTime);
      break;
    case 15:
      pattern_showcase(iTime);
      break;
  }

  FastLED.show();
}

