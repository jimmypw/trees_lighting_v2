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

void do_transition(void (*Func1)(int, CRGB*, double, int), int pattern_setting1, void (*Func2)(int, CRGB*, double, int), int pattern_setting2, float balance, double iTime) {
  for (int i = 0; i < NUM_LEDS; i++) {
    // create two new placeholders holding the dereferenced value of the current led 
    CRGB led_pattern1;
    CRGB led_pattern2;
    CRGB output;

    #ifdef DEBUG
    //Serial.print("balance: ");
    //Serial.println(balance);
    #endif

    // copy the contents of the struct - there may be a simpler way to do this
    //memcpy(&led_pattern1, &leds[i], sizeof(CRGB));
    //memcpy(&led_pattern2, &leds[i], sizeof(CRGB));
    // perhaps like this:
    led_pattern1 = leds[i];
    led_pattern2 = leds[i];
    

    // Generate both effects
    (*Func1)(i, &led_pattern1, iTime, pattern_setting1);
    (*Func2)(i, &led_pattern2, iTime, pattern_setting2);

    // interpolate between the effects
    output = interpolate(led_pattern1, led_pattern2, balance);

    // write the effect back to the array
    leds[i] = output;
  }
}

int interpolate(int x1, int x2, float t){
  return x1 + ((x2 - x1) * t);
}

CRGB interpolate(CRGB x1, CRGB x2, float t){
  CRGB output;
  output.r = interpolate(x1.r, x2.r, t);
  output.g = interpolate(x1.g, x2.g, t);
  output.b = interpolate(x1.b, x2.b, t);
  return output;
}

