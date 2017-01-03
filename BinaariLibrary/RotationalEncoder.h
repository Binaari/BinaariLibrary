/*

Title: 					BiaariLibrary - RotationalEncoder
Original creator: 		Jussi Wallin
Original release URL: 	https://github.com/Binaari/BinaariLibrary
Original release date:	12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/



#ifndef BinaariEncoder_h
#define BinaariEncoder_h

#include "Arduino.h"

class RotationalEncoder {

    public:

    int a;
    int b;
    int button;

    unsigned int getEncoderPos() {
        
    }

    private:
        
    volatile unsigned int encoderPos = 0;
    unsigned int lastReportedPos = 1;
    volatile boolean turn = false;

    boolean Aset = false;
    boolean Bset = false;

    void initiate(int A = 3, int B = 2, int btn = 4) {
        a = A;
        b = B;
        button = btn;

        pinMode(A, INPUT_PULLUP);
        pinMode(B, INPUT_PULLUP);
        pinMode(button, INPUT_PULLUP);

        attachInterrupt(digitalPinToInterrupt(A), doInterruptA, CHANGE);
        attachInterrupt(digitalPinToInterrupt(B), doInterruptB, CHANGE);

    }

    void doInterruptA() {
        if (turn) 
            delay(1);
        if (digitalRead(encA) != Aset) {
            Aset = !Aset;

            if (Aset && !Bset)
                encoderPos++;

            turn = false;
        }
    }

    void doInterruptB() {
        if (turn) 
            delay(1);
        if (digitalRead(encB) != Bset) {
            Bset = !Bset;

            if (!Aset && Bset)
            encoderPos--;

            turn = false;
        }
    }
    
};

#endif