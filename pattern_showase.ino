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

  //unsigned long secondofcycle = 23;
  
  // The length of this switch must equal SHOWCASE_LENGTH
  switch(secondofcycle) {
    case 0:
      do_pattern(sparkle_rainbowphase, iTime, 86);
      break;
    case 1:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 2:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 3:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 4:
      do_pattern(solid_colour, iTime, 64);
      break;
    case 5:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 6:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 7:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 8:
      do_pattern(solid_colour, iTime, 676);
      break;
    case 9:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 10:
      do_pattern(rainbow_variablecompress, iTime, 64);
      break;
    case 11:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 12:
      mix_pattern(sparkle_white, 512,
                    rainbow_variablecompress, 86,
                    0.50,
                    iTime);
      break;
    case 13:
      mix_pattern(sparkle_white, 512,
                    solid_rainbow_slow, 1024,
                    0.50,
                    iTime);
      break;
    case 14:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 15:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 16:
      do_pattern(solid_colour, iTime, 332);
      break;
    case 17:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 18:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 19:
      do_pattern(sparkle_rainbowphase, iTime, 86);
      break;
    case 20:
      mix_pattern(sparkle_white, 512,
                    rainbow_variablecompress, 86,
                    0.50,
                    iTime);
      break;
    case 21:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 22:
      do_pattern(solid_colour, iTime, 810);
      break;
    case 23:
      mix_pattern(sparkle_rainbowphase, 1024,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 24:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 25:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 26:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 27:
      do_pattern(solid_colour, iTime, 150);
      break;
    case 28:
      mix_pattern(sparkle_white, 512,
                    rainbow_variablecompress, 86,
                    0.50,
                    iTime);
      break;
    case 29:
      mix_pattern(sparkle_rainbowphase, 86, rainbow_variablecompress, 512, 0.0478, iTime);
      break;
    case 30:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 31:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 32:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 33:
      mix_pattern(sparkle_rainbowphase, 512,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 34:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 35:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 36:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 37:
      do_pattern(solid_colour, iTime, 99);
      break;
    case 38:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 39:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 40:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 41:
      mix_pattern(sparkle_rainbowphase, 512,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 42:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 43:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 44:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 45:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 46:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 47:
      mix_pattern(sparkle_white, 512,
                    rainbow_variablecompress, 86,
                    0.50,
                    iTime);
      break;
    case 48:
      mix_pattern(sparkle_rainbowphase, 512,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 49:
      mix_pattern(sparkle_white, 86, solid_timestep, 512, 0.0478, iTime);
      break;
    case 50:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 51:
      do_pattern(sparkle_white, iTime, 86);
      break;
    case 52:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 53:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 54:
      do_pattern(solid_colour, iTime, 1000);
      break;
    case 55:
      mix_pattern(sparkle_rainbowphase, 512,
                    rainbow_variablecompress, 512,
                    0.05,
                    iTime);
      break;
    case 56:
      do_pattern(sparkle_rainbowphase, iTime, 512);
      break;
    case 57:
      do_pattern(solid_timestep, iTime, 512);
      break;
    case 58:
      do_pattern(rainbow_variablecompress, iTime, 512);
      break;
    case 59:
      do_pattern(saw_coloursaturationstep, iTime, 0);
      break;
  }
 }

