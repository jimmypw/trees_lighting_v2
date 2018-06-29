void rainbow(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int speed = map(pattern_setting, 0, 1023, 1, 100);
  *thisLed = CHSV(index + (iTime*speed), 255, 255);
}
