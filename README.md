# trees_lighting_v2

This is a bit of code I wrote for a lighting system for a festival 12v sound system. 

Im pretty pleased with how this turned out, the way the code is structured makes it very east to add new patterns. In the loop function after some values have been determined there is a huge switch statement that selects the current pattern to display. This switch will then call one of two functions, do_pattern or mix_pattern. These functions take the actual pattern function as the first arguement and a few other settings. Both funttions will then iterate over all leds and call the referenced function for each led. The pattern functions are algorithms that are run once for each led on the strip. 

This Model was based on glsl and how it renders each pattern on the screen. I have carried over some of the concepts through. Each pixel is blind (Can not see other led's (not entirely true as other LED's are available through pointer arythmatic)) and each pixel is dumb - aside from what is stored in the display buffer, none of the led's or patterns have any memory of what happened previously.

This model encourages algorithmic drawing of patterns on the strip using things like iTime, pattern_setting, entrpy and noise to animate and vary the pattern but it also makes the sketch 'safe'. Since there is only one global array of a fixed length for holding the led strip's display buffer. Every other variable will eventually fall out of scope preventing any memory leaks 
