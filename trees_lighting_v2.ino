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
#define MAX_PATTERNS 50

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

// settings struct contains current configuration
struct {
  int patterncount;
  void (*patterns[MAX_PATTERNS])(const int, CRGB*, const double, const int);
} settings;

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

void addPattern(void (*func)) {
  settings.patterns[settings.patterncount] = func;
  settings.patterncount++;
}

void setup() {
  FastLED.addLeds<WS2812B, PIN_LEDSTRIP, GRB>(leds, NUM_LEDS);
  high_power_hack();
  FastLED.delay(1000/FRAMES_PER_SECOND);
  FastLED.clear(true);
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  
  

  // init the pattern count;
  settings.patterncount = 0;
  // init the patterns array
  for ( int i = 0; i < MAX_PATTERNS; i++ ) {
    settings.patterns[i] = NULL;
  }

  addPattern(rainbow_startup);
  addPattern(solid_white);
  addPattern(scroll_rgb);
  addPattern(solid_colour);
  addPattern(sparkle_white);
  addPattern(sparkle_varicol_fast);
  addPattern(sparkle_varicol_slow);
  addPattern(sparkle_rainbowphase);
  addPattern(solid_white);
  addPattern(scroll_rgb);
  addPattern(solid_colour);
  addPattern(solid_timestep);
  addPattern(solid_rainbow_slow);
  addPattern(solid_rainbow_fast);
  addPattern(saw_coloursaturationstep);
  addPattern(rainbow);
  addPattern(rainbow_variablecompress);
  addPattern(tricolor);
  addPattern(cascadeout);
  addPattern(cascadeout_rainbow );
  addPattern(knightrider);
  addPattern(knightrider_rainbow);
  

  // run pattern 0 for 2 seconds
  do_pattern(0, 10.00, 1023);
  FastLED.show();
  delay(500);
}

void loop() {
  const double iTime = seconds_with_ms();
  const int pattern_setting = analogRead(PIN_PATTERNSETTING);
  const int pattern = map(analogRead(PIN_PATTERNSELECT), 0, 1023, 0, settings.patterncount - 1);

  #ifdef DEBUG
  Serial.print("iTime: ");
  Serial.println(iTime);
  Serial.print("pattern: ");
  Serial.println(pattern);
  Serial.print("pattern_setting: ");
  Serial.println(pattern_setting);
  #endif
  
  do_pattern(pattern, iTime, pattern_setting);

  FastLED.show();
}
