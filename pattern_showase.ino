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

