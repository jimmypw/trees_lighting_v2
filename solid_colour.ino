void solidwhite(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 0, 255);
  *thisLed = CHSV(0, 0, brightness);
}

void solidcolour(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int colour = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(colour, 255, 255);
}
