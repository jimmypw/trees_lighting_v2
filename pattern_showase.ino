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
 #define SHOWCASE_LENGTH 60

 void pattern_showcase(double iTime) {
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
  unsigned long currentms = millis();

  // Then, generate the other values we require
  unsigned long secondofcycle = (currentms / 1000L) % SHOWCASE_LENGTH;
  unsigned long msofcycle = currentms % (SHOWCASE_LENGTH * 1000L);

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
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 10:
    case 11:
    case 12:
      mix_pattern(sparkle_white, 86,
                    sparkle_rainbowphase, 86,
                    interpolate_over_time(10000, 13000, msofcycle),
                    iTime);
      break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      do_pattern(sparkle_rainbowphase, iTime, 86);
      break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
      mix_pattern(sparkle_rainbowphase, 86, rainbow_variablecompress, 512, 0.0478, iTime);
      break;
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
      do_pattern(solid_rainbow_fast, iTime, 512);
      break;
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
      do_pattern(solid_timestep, iTime, 1024);
      break;
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
      do_pattern(saw_coloursaturationstep, iTime, 0);
      break;
  }
 }

