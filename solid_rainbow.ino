void solidrainbowslow(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime, 255, brightness);
}

void solidrainbowfast(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int brightness = map(pattern_setting, 0, 1023, 1, 255);
  *thisLed = CHSV(iTime*4, 255, brightness);
}
