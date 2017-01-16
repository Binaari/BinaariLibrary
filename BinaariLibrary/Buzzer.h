/*

Title: 					BiaariLibrary - Buzzer
Original creator: 		Jussi Wallin
Original release URL: 	https://github.com/Binaari/BinaariLibrary
Original release date:	12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/



#ifndef BinaariBuzzer_h
#define BinaariBuzzer_h

#include "Arduino.h"

class Buzzer {

    public:
    void initialize(int buzzerPIN = 9) {
        buzzer = buzzerPIN;
        pinMode(buzzer, OUTPUT);
        return;
    }

    void beep(int frequency, int durationM) {
        tone(buzzer, frequency, durationM);
        delay(durationM);
        return;
    }

    private:
    int buzzer;
};

#endif