void rainbow(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int speed = map(pattern_setting, 0, 1023, 1, 100);
  *thisLed = CHSV((index *8) + (iTime*speed), 255, 255);
}

void rainbow_variablecompress(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int compression = map(pattern_setting, 0, 1023, 1, 32);
  *thisLed = CHSV((compression * index) + (iTime*100), 255, 255);
}

void rainbow_startup(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  *thisLed = CHSV(index * 16, 255, 255);
}
