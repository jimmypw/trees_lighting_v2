void saw_white(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  uint8_t brightness = saw_time(iTime*0.10);
  *thisLed = CHSV(0, 0, brightness);
}

void saw_colourstep(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  uint8_t colour = colour_secondstep(iTime*0.10);
  uint8_t brightness = saw_time(iTime*0.10);
  *thisLed = CHSV(colour, 255, brightness);
}

void saw_coloursaturationstep(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  uint8_t colour = colour_secondstep(iTime*0.10);
  uint8_t saturation = saw_time(iTime*0.10);
  *thisLed = CHSV(colour, saturation, 255);
}
