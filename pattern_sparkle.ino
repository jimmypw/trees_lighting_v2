void sparkle_white(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int dice = random(map(pattern_setting, 0, 1023, 30, 900));
  #ifdef DEBUG
  Serial.print("pattern_setting: ");
  Serial.println(pattern_setting);
  #endif
  // if dive matched probability set by pattern_setting set led to full white
  if (dice == 0) {
    *thisLed = CRGB::White;
  }
  decay(thisLed, 0.80);
}

void sparkle_varicol(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int dice = random(86);
  uint8_t colour = map(pattern_setting, 0, 1023, 0, 255);
  #ifdef DEBUG
  Serial.print("pattern_setting: ");
  Serial.println(pattern_setting);
  #endif
  if (dice == 0) {
    *thisLed = CHSV(colour, 255,255);
  }
  decay(thisLed, 0.80);
}

void sparkle_rainbowphase(int index, CRGB *thisLed, double iTime, int pattern_setting) {
  int dice = random(86);
  uint8_t colour = iTime*64;
  #ifdef DEBUG
  Serial.print("pattern_setting: ");
  Serial.println(pattern_setting);
  #endif
  if (dice == 0) {
    *thisLed = CHSV(colour, 255,255);
  }
  decay(thisLed, 0.80);
}
