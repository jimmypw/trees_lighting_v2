void saw_coloursaturationstep(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const uint8_t colour = colour_secondstep(iTime*0.10);
  const uint8_t saturation = saw_time(iTime*0.10);
  *thisLed = CHSV(colour, saturation, 255);
}
