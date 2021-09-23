int normalise_pattern_selector(const int input) {
  return constrain(map(input, 0, 1023, 1, (MAX_PATTERNS + 1)), 0, MAX_PATTERNS);
}

double seconds_with_ms() {
  return (double)millis()/1000;
}

double normalise_index(const int index){
  return index / NUM_LEDS;
}

void decay(CRGB *led, const double amount) {
  led->r = floor(led->r * amount);
  led->g = floor(led->g * amount);
  led->b = floor(led->b * amount);
}

void do_pattern(void (*Func)(const int, CRGB*, const double, const int), const double iTime, const int pattern_setting) {
  for (int i = 0; i < NUM_LEDS; i++) {
    (*Func)(i, &leds[i], iTime, pattern_setting);
  }
}

uint8_t saw_time(const double iTime) {
  return (iTime - (uint8_t)iTime) * 255;
}

uint8_t colour_secondstep(const double iTime) {
  randomSeed(floor(iTime)+1);
  return random(0, 255);
}

void mix_pattern(const void (*Func1)(const int, CRGB*, const double, const int), const int pattern_setting1, const void (*Func2)(const int, CRGB*, const double, const int), const int pattern_setting2, const float balance, const double iTime) {
  #ifdef DEBUG
  //Serial.print("balance: ");
  //Serial.println(balance);
  #endif
  
  for (int i = 0; i < NUM_LEDS; i++) {
    // create two new placeholders holding the dereferenced value of the current led 
    CRGB led_pattern1 = leds[i];
    CRGB led_pattern2 = leds[i];
    
    // Generate both effects
    (*Func1)(i, &led_pattern1, iTime, pattern_setting1);
    (*Func2)(i, &led_pattern2, iTime, pattern_setting2);

    // interpolate between the effects and write new value back to array
    leds[i] = interpolate(led_pattern1, led_pattern2, balance);
  }
}

int interpolate(const int x1, const int x2, const float t){
  return x1 + ((x2 - x1) * t);
}

CRGB interpolate(const CRGB x1, const CRGB x2, float t){
  CRGB output;
  output.r = interpolate(x1.r, x2.r, t);
  output.g = interpolate(x1.g, x2.g, t);
  output.b = interpolate(x1.b, x2.b, t);
  return output;
}
