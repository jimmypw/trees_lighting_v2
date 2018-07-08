void solid_white(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int brightness = map(pattern_setting, 0, 1023, 0, 255);
  *thisLed = CHSV(0, 0, brightness);
}

void solid_colour(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int colour = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(colour, 255, 255);
}

void solid_timestep(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const uint8_t colour = colour_secondstep(iTime*0.10);
  const int saturation = map(pattern_setting, 0, 1023, 0, 255);
  *thisLed = CHSV(colour, saturation, 255);
}


/* I do not think we need both of the following effects */

void solid_rainbow_slow(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime, 255, brightness);
}

void solid_rainbow_fast(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime*64, 255, brightness);
}
