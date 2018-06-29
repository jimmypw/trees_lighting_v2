void solid_white(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 0, 255);
  *thisLed = CHSV(0, 0, brightness);
}

void solid_colour(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int colour = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(colour, 255, 255);
}


/* I do not think we need both of the following effects */

void solid_rainbow_slow(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime, 255, brightness);
}

void solid_rainbow_fast(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime*4, 255, brightness);
}
