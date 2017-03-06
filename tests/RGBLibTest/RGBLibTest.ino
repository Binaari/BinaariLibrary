/*

Title:                  magnetometric sensor serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include <BinaariLibrary.h>

BinaariLibrary binaari;

byte color [] = {0,0,0};
byte brightness = 5;

void setup() {
    binaari.initialize();
}


void loop() {
  byte rgbColour[3];

  // Start off with green.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  

  // Choose the colours to increment and decrement.
  for (byte decColour = 0; decColour < 3; decColour += 1) {
    byte incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      binaari.RGB.setColor(rgbColour);
      binaari.RGB.sendBytes();
      delay(5);
    }
  }
}
