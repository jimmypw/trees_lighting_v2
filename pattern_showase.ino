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
  int second = (int)iTime % SHOWCASE_LENGTH;
  double ms  = iTime - (int)iTime;
  

  switch(second) {
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
      do_transition(sparkle_rainbowphase, 86, rainbow_variablecompress, 512, 0.0478, iTime);
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
      do_pattern(rainbow_variablecompress, 512, 0.0478, iTime);
      break;
  }
 }

