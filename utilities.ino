int normalise_pattern_selector(int input) {
  return constrain(map(input, 0, 1023, 1, (MAX_PATTERNS + 1)), 0, MAX_PATTERNS);
}

double seconds_with_ms() {
  return (double)millis()/1000;
}

double normalise_index(int index){
  return index / NUM_LEDS;
}

void decay(CRGB *led, double amount) {
  led->r = floor(led->r * amount);
  led->g = floor(led->g * amount);
  led->b = floor(led->b * amount);
}

void do_pattern(void (*Func)(int, CRGB*, double, int), double iTime, int pattern_setting) {
  for (int i = 0; i < NUM_LEDS; i++) {
    (*Func)(i, &leds[i], iTime, pattern_setting);
  }
}

uint8_t saw_time(double iTime) {
  return (iTime - (uint8_t)iTime) * 255;
}

uint8_t colour_secondstep(double iTime) {
  randomSeed(floor(iTime)+1);
  return random(0, 255);
}


// WORK IN PROGRESS BELOW

void do_transition(void (*Func1)(int, CRGB*, double, int), void (*Func2)(int, CRGB*, double, int), uint8_t balance, double iTime, int pattern_setting) {
  for (int i = 0; i < NUM_LEDS; i++) {
    // create two new placeholders holding the dereferenced value of the current led 
    CRGB led_pattern1;
    CRGB led_pattern2;
    CRGB output;

    // copy the contents of the struct - there may be a simpler way to do this
    memcpy(&led_pattern1, &leds[i], sizeof(CRGB));
    memcpy(&led_pattern2, &leds[i], sizeof(CRGB));
    // perhaps like this:
    /*
     * led_pattern1 = leds[i];
     * led_pattern2 = leds[i];
     */

    // Generate both effects
    (*Func1)(i, &led_pattern1, iTime, pattern_setting);
    (*Func2)(i, &led_pattern2, iTime, pattern_setting);

    // interpolate between the effects
    output = interpolate(led_pattern1, led_pattern2, balance);

    // write the effect back to the array
    leds[i] = output;
  }
}

CRGB interpolate(CRGB pattern1, CRGB pattern2, uint8_t balance){
  CRGB output;
  /* First pass, i forgot to include balance.
  output.r = pattern1.r + (pattern2.r - pattern1.r);
  output.g = pattern1.g + (pattern2.g - pattern1.g);
  output.b = pattern1.b + (pattern2.b - pattern1.b);
  */ 


  /*
   * balance = 0.5
   * pat 1 r = 64
   * pat 2 r = 182
   * find the higher value
   * difference = pat (high) r - pat (low) r = pat 2 r - pat 1 r = 118
   * balance modifier = (difference) * (balance) = 118 * 0.5 = 59
   * output r = pat (low) + (balance modifier)
   * 
   * repeat for g and b channels
   * return output
   */
  return output;
}


