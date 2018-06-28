int normalise_pattern_selector(int input) {
  return map(input, 0, 1023, 1, (MAX_PATTERNS + 1));
}

uint8_t aread16to8(uint8_t pin) {
  return analogRead(pin) / 4;
}

double seconds_with_ms() {
  return (double)millis()/1000;
}

double normalise_index(int index){
  return index / NUM_LEDS;
}

void do_pattern(void (*Func)(int, CRGB*, double, int), double iTime, int pattern_setting) {
  for (int i = 0; i < NUM_LEDS; i++) {
    (*Func)(i, &leds[i], iTime, pattern_setting);
  }
}

void decay(CRGB *led, double amount) {
  led->r = floor(led->r * amount);
  led->g = floor(led->g * amount);
  led->b = floor(led->b * amount);
}

