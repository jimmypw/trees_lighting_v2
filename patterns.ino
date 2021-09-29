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

// Contributed by Tom Sainthorpe
void tricolor(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {

  *thisLed = CHSV(((index % 3)*80) + (iTime*100),255, 255);
} 

void cascadeout(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  #ifdef DEBUG
  Serial.println("in cascadeout: ");
  Serial.print("iTime: ");
  Serial.println((int)iTime * 10);
  #endif
  int millis = iTime * 100;
  int middle = NUM_LEDS * 0.5;
  
  if (index < middle) {
    *thisLed = CHSV(pattern_setting,255,(int)(index + millis*0.1)%4?0:255);
  } else {
    *thisLed = CHSV(pattern_setting,255,(int)(index - millis*0.1)%4?0:255);
  }
} 


void cascadeout_rainbow(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  #ifdef DEBUG
  Serial.println("in cascadeout: ");
  Serial.print("iTime: ");
  Serial.println((int)iTime * 10);
  #endif
  int millis = iTime * 100;
  int middle = NUM_LEDS * 0.5;
  int col = map_double(sin(iTime*2), -1.0, 1.0, 0.0, 255.0);
  if (index < middle) {
    *thisLed = CHSV(col,255,(int)(index + millis*0.1)%4?0:255);
  } else {
    *thisLed = CHSV(col,255,(int)(index - millis*0.1)%4?0:255);
  }
} 

// Contributed by Tom Sainthorpe
void knightrider(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  double devayval = 0.8;
  int millis = iTime*90;
  int stripLength =40;
  int iter = millis / (NUM_LEDS - stripLength);
  bool reverse = iter % 2 ? true : false;
  if (reverse){
    int stripStart= millis - (iter*(NUM_LEDS - stripLength));
    int stripEnd = stripStart + stripLength;
    if (index >= stripStart && index <= stripEnd) {
      *thisLed = CHSV(0,255,255);
    } else {
      //*thisLed = CHSV(0,255,0);
      decay(thisLed, devayval);
    }
  }
  else
  {
    int stripStart= (NUM_LEDS - stripLength) - (millis - (iter*(NUM_LEDS - stripLength)));
    int stripEnd = stripStart + stripLength;
    if (index >= stripStart && index <= stripEnd) {
      *thisLed = CHSV(0,255,255);
    } else {
      //*thisLed = CHSV(120,255,0);
      decay(thisLed, devayval);
    }
  }
} 

void knightrider_rainbow(const int index, CRGB *thisLed, const double iTime, const int pattern_setting) {
  double devayval = 0.8;
  int millis = iTime*90;
  int stripLength =40;
  int iter = millis / (NUM_LEDS - stripLength);
  int col = map_double(sin(iTime*2), -1.0, 1.0, 0.0, 255.0);
  bool reverse = iter % 2 ? true : false;
  if (reverse){
    int stripStart= millis - (iter*(NUM_LEDS - stripLength));
    int stripEnd = stripStart + stripLength;
    if (index >= stripStart && index <= stripEnd) {
      *thisLed = CHSV(col,255,255);
    } else {
      //*thisLed = CHSV(0,255,0);
      decay(thisLed, devayval);
    }
  }
  else
  {
    int stripStart= (NUM_LEDS - stripLength) - (millis - (iter*(NUM_LEDS - stripLength)));
    int stripEnd = stripStart + stripLength;
    if (index >= stripStart && index <= stripEnd) {
      *thisLed = CHSV(col,255,255);
    } else {
      //*thisLed = CHSV(120,255,0);
      decay(thisLed, devayval);
    }
  }
} 
