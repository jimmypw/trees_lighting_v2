void sparkle_white(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  // 86 is a nice setting.
  const int dice = random(map(pattern_setting, 0, 1023, 0, 200));
  #ifdef DEBUG
  //Serial.print("pattern_setting: ");
  //Serial.println(pattern_setting);
  #endif
  // if dive matched probability set by pattern_setting set led to full white
  if (dice == 0) {
    *thisLed = CRGB::White;
  }
  decay(thisLed, 0.80);
}

void sparkle_varicol(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int dice = random(86);
  const uint8_t colour = map(pattern_setting, 0, 1023, 0, 255);
  #ifdef DEBUG
  //Serial.print("pattern_setting: ");
  //Serial.println(pattern_setting);
  #endif
  if (dice == 0) {
    *thisLed = CHSV(colour, 255,255);
  }
  decay(thisLed, 0.80);
}

void sparkle_rainbowphase(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int dice = random(map(pattern_setting, 0, 1023, 0, 200));
  const uint8_t colour = iTime*64;
  #ifdef DEBUG
  //Serial.println("in sparkle_rainbowphase: ");
  //Serial.print("pattern_setting: ");
  //Serial.println(pattern_setting);
  #endif
  if (dice == 0) {
    *thisLed = CHSV(colour, 255,255);
  }
  decay(thisLed, 0.80);
}
