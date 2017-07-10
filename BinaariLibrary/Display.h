/***********************************************************
 * Display.h
 * 
 * Binääri library for controlling
 * the display and the led array.
 * 
 * Note that pre and postconditions mentioned
 * before each function must be met.
 * 
 * 
 * Author:        Tuukka Panula
 * 
 * Release date:  7/3/2017 (dd/mm/yyyy)
 * 
 * Release site:  https://github.com/Binaari/BinaariLibrary
 * 
 * 
 * This code is released under the MIT License
 * (http://opensource.org/licenses/MIT).
 * 
 * No warranty is given.
 ***********************************************************/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Arduino.h"

//define the I/O pins
#define LATCH_PIN   7
#define CLOCK_PIN   A1
#define DATA_PIN    8
#define BJT_PIN_1   12
#define BJT_PIN_2   13
#define BJT_PIN_3   10

//choose which digit to enter to the shift reg and   
class Display
{
  public:
    Display();
    void sevenSegment(String value);
    void sevenSegment(int value1, int value2);
    void ledArray(int value);

  private:
    //shift register control pins
    const int _latch = LATCH_PIN;
    const int _clock = CLOCK_PIN;
    const int _data = DATA_PIN;

    //transistor pins
    const int _transistors[3]={BJT_PIN_1, BJT_PIN_2, BJT_PIN_3};
    
    //seven-segment display digit matrix
    int _digits[20]={
        
        B01110111, // 0  ABCDEF-
        B00010100, // 1  -BC----
        B10110011, // 2  AB-DE-G
        B10110110, // 3  ABCD--G
        B11010100, // 4  -BC--FG
        B11100110, // 5  A-CD-EF
        B11100111, // 6  A-BCDEF
        B00110100, // 7  ABC----
        B11110111, // 8  ABCDEFG
        B11110110, // 9  ABCD-FG
  
        B11110101, // A  ABCDEF-
        B11000111, // B  --CDEFG
        B10000011, // C  ---DEF-
        B10010111, // D  -BCDE-G
        B11100011, // E  A--DEFG
        B11100001, // F  A---EFG
  
        B10000000, // _           ---D---
        B00000010, // -           ------G
        B11110000, // deg         AB---FG
        B00000000, // empty char  -------

/*
                    A
                 #######
                ##     ##
              F ##  G  ## B
                 #######
                ##     ##
              E ##     ## C  ###
                 #######    ## ##
                    D        ### DP
*/


    };

};

#endif