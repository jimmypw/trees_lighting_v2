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

void sparkle_varicol_fast(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int dice = random(20);
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

void sparkle_varicol_slow(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int dice = random(150);
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
  const uint8_t colour = iTime*64+128;
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

void solid_white(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int brightness = map(pattern_setting, 0, 1023, 0, 255);
  *thisLed = CHSV(0, 0, brightness);
}

void scroll_rgb(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  int selecter = ((int)(iTime*2.0))%3;
  switch(selecter) {
    case 0:
      *thisLed = CRGB::Red;
      break;
    case 1:
      *thisLed = CRGB::Green;
      break;
    case 2:
      *thisLed = CRGB::Blue;
      break;
  }
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


/*
 * The showcase pattern
 * 
 * Here be the 'main event' of the project. Using a combination 
 * of the created patterns, mixing / interpolation and automated 
 * pattern changing. I want to create a routine that lasts about
 * 60 seconds and repeats on a loop.
 * 
 * 
 */
 // in seconds
 #define SHOWCASE_LENGTH 5

 void pattern_showcase(const double iTime) {
  /* 
   *  iTime is useful for the patterns but is not useful here.
   *  I need to work out the posision of the showreel and I need
   *  millisecond accuracy spanning multiple seconds to calculate
   *  transitions. 
   *  I'll generate these values again as accuracy is lost with iTime.
   *  This should not be too much of an overhead
   *  
   *  second of cycle - contains the number of seconds we are in to the
   *  showreel, this is useful for selecting what patterns or transitions 
   *  are to be shown 
   *  
   *  msofcycle - like seconds but in ms. Used in the
   *  interpolate_over_time function to allow for smooth transitions
   *  between effects.
   */

  // first, store the value of millis() so that it doesn't change while calculating the showreel.
  const unsigned long currentms = millis();

  // Then, generate the other values we require
  const unsigned long secondofcycle = (currentms / 1000L) % SHOWCASE_LENGTH;
  const unsigned long msofcycle = currentms % (SHOWCASE_LENGTH * 1000L);

  #ifdef DEBUG
  //Serial.print("Currentms: ");
  //Serial.println(currentms);
  //Serial.print("secondofcycle: ");
  //Serial.println(secondofcycle);
  //Serial.print("msofcycle: ");
  //Serial.println(msofcycle);
  #endif
  
  // The length of this switch must equal SHOWCASE_LENGTH
  switch(secondofcycle) {
    case 0:
      do_pattern(sparkle_white, iTime, 150);
      break;
    case 1:
      mix_pattern(sparkle_rainbowphase, 150,
                  sparkle_white, 150,
                  0.50, 
                  iTime);
    case 2:
      do_pattern(sparkle_rainbowphase, iTime, 150);
      break;
    case 3:
      mix_pattern(sparkle_rainbowphase, 150,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 4:
      mix_pattern(sparkle_white, 150,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
  }
 }


void saw_coloursaturationstep(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const uint8_t colour = colour_secondstep(iTime*0.10);
  const uint8_t saturation = saw_time(iTime*0.10);
  *thisLed = CHSV(colour, saturation, 255);
}

void rainbow(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int speed = map(pattern_setting, 0, 1023, 1, 100);
  *thisLed = CHSV((index *8) + (iTime*speed), 255, 255);
}

void rainbow_variablecompress(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  const int compression = map(pattern_setting, 0, 1023, 1, 32);
  *thisLed = CHSV((compression * index) + (iTime*100), 255, 255);
}

void rainbow_startup(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  *thisLed = CHSV(index * 16, 255, 255);
}
