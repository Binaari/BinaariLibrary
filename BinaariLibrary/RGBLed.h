/*

Title: 					BiaariLibrary - RGBLed
Original creator: 		Jussi Wallin
Original release URL: 	https://github.com/Binaari/BinaariLibrary
Original release date:	12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include <Arduino.h>
#include <util/delay.h>

#ifndef RGBLed_h
#define RGBLed_h

class RGBLed {

    private:

    byte 
        _g,
        _r,
        _b;
    int _pin;

    void sendByte(byte b) {
        byte i = 8; // one byte is 8 bits
            do{
                if ((b & 0x80) == 0) { //bit is equal to 0
                    __asm__(                    // clocks   Pseudocode
                        "sbi %[port], 0x2\n\t"  // 1        set A2 high
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t"               // 1        delay 62,5ns
                        "cbi %[port], 0x2\n\t"  // 1        set A2 low
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        :   
                        :   [port] "I" (_SFR_IO_ADDR(PORTC)) // port C address
                    );
                } else { //bit is equal to 1
                    __asm__(                    // clocks   Pseudocode
                        "sbi %[port], 0x2\n\t"  // 1        set A2 high
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t"               // 1        delay 62,5ns
                        "cbi %[port], 0x2\n\t"  // 1        set A2 low
                        
                        :   
                        :   [port] "I" (_SFR_IO_ADDR(PORTC)) // port C address
                    );
                }
                b=b<<1; // shift bits left
                i--;    // increment loop
                __asm__ __volatile__(           // clocks   Pseudocode
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                        "nop\n\t""nop\n\t"      // 2        delay 2*62,5ns
                );
            } while (i!=0); // loop until all bits sent

    };

    public:

    void initialize(int pin = A2) {
        _pin = pin;
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, LOW);
    }

    void setColor(byte col[]) {
        noInterrupts();
        _g = col[0];
        _r = col[1];
        _b = col[2];
        interrupts();
    };

    // col is meant to be used  as array of GRB colors
    void sendBytes() {
        sendByte(_g);
        sendByte(_r);
        sendByte(_b);
        delayMicroseconds(50);
    }

};

#endif