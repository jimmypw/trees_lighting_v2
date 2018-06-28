void rainbow(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int speed = map(pattern_setting, 0, 1023, 1, 100);
  *thisLed = CHSV(index + (iTime*speed), 255, 255);
}

/*
void rainbow(double iTime, uint8_t pattern_setting) {
  for (int i = 0; i < NUM_LEDS; i++) {
    rainbow_led(i, leds[i], iTime, pattern_setting);
  }
  
}

void rainbow_led(int index, CRGB thisLed, double iTime, uint8_t pattern_setting){
  double index_normal = normalise_x(index);
  
}
*/
