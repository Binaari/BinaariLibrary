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

    int getPinA() {
        return a;
    }
    
    int getPinB() {
        return b;
    }
    
    int getPinButton() {
        return button;
    }

    unsigned int getEncoderPos() {
        return encoderPos;
    }

    void setTurn(boolean b) {
        turn = b;
    }

    void initialize(int A = 3, int B = 2, int btn = 4) {
        a = A;
        b = B;
        button = btn;

        pinMode(A, INPUT_PULLUP);
        pinMode(B, INPUT_PULLUP);
        pinMode(button, INPUT_PULLUP);

        attach(A,B);
    }

    private:
        
    int a;
    int b;
    int button;

    volatile unsigned int encoderPos;
    volatile boolean turn = false;

    boolean Aset = false;
    boolean Bset = false;

    void doInterruptA() {
        if (turn) // if encoder has started turning delay execution of interrupt
            delay(1);
        if (digitalRead(a) != Aset) {
            Aset = !Aset;

            if (Aset && !Bset)
                encoderPos++;

            turn = false;
        }
    }

    void doInterruptB() {
        if (turn) // if encoder has started turning delay execution of interrupt
            delay(1);
        if (digitalRead(b) != Bset) {
            Bset = !Bset;

            if (!Aset && Bset)
            encoderPos--;

            turn = false;
        }
    }
    
};

void attachInterrupts(int a, int b) {
    
        attachInterrupt(digitalPinToInterrupt(a), InterruptA(), CHANGE);
        attachInterrupt(digitalPinToInterrupt(b), InterruptB(), CHANGE);
}

void interruptA() {
    RotationalEncoder.doInterruptA();
}

void interruptB() {
    RotationalEncoder.doInterruptB();
}

#endif