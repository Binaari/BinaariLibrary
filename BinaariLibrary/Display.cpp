/***********************************************************
 * Display.cpp
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

//See Display.h for declarations and function prototypes
#include "Display.h"

/*
 * Constructor
 */
Display::Display()
{
  pinMode(_latch, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_data, OUTPUT);
  
  //transistor pins
  for (int i=0;i<3;i++){
    pinMode(_transistors[i],OUTPUT);
  }
}



//****************************************************************************//
//
//  Function for displaying digits on the 7-segment display
//
//****************************************************************************//

void Display::sevenSegment(String value)
{
    
 //set pointer to point to the beginning of the byte array
 int *p;
 p = _digits;
 
 for(int i=0;i<value.length();i++){

     
    char currentDigit = value.charAt(i);
    
    int selectDigit = 0;
        
    int dotMask = 0b00000000;
    
    //choose which character to display
    switch (currentDigit) {
        case '0': 
            selectDigit = 0;
            break;
        case '1':  
            selectDigit = 1;
            break;
        case '2':  
            selectDigit = 2;
            break;
        case '3':  
            selectDigit = 3;
            break;
        case '4':  
            selectDigit = 4;
            break;
        case '5':  
            selectDigit = 5;
            break;
        case '6':  
            selectDigit = 6;
            break;
        case '7':  
            selectDigit = 7;
            break;
        case '8':  
            selectDigit = 8;
            break;
        case '9':  
            selectDigit = 9;
            break;
        ///////////////////////
        case 'a': 
            selectDigit = 10;
            break;
        case 'b':  
            selectDigit = 11;
            break;
        case 'c':  
            selectDigit = 12;
            break;
        case 'd':  
            selectDigit = 13;
            break;
        case 'e':  
            selectDigit = 14;
            break;
        case 'f':  
            selectDigit = 15;
            break;
        ///////////////////////
        case '_':  
            selectDigit = 16;
            break;
        case '-':  
            selectDigit = 17;
            break;
        case '*':  
            selectDigit = 18;
            break;
        case '$':  
            selectDigit = 19;
            break;
        default:
            selectDigit = 19;
            break;

            
    }
    //Check if the next character is a dot
        if (i < value.length()-1){
            if (value.charAt(i+1) == '.'){
                // If true then mask the digit so that the dot is displayed
                dotMask = 0b00001000;
            }
        }
    
   //switch each transistor to off-state for initialization
   for (int j=3;j>=0;j--){
    digitalWrite(_transistors[j],LOW);
   }
   
   delayMicroseconds(500);
   digitalWrite(_latch,LOW);   

   //choose which digit to enter to the shift reg and
   //switch the corresponding transistor on
   shiftOut(_data,_clock,MSBFIRST, *(p + selectDigit) | dotMask);
   //shiftOut(_data,_clock,MSBFIRST,0b11111111);
   digitalWrite(_latch,HIGH);
   delayMicroseconds(500);
   if (i == 0){
       digitalWrite(_transistors[0],HIGH);

   } else {
        digitalWrite(_transistors[1],HIGH);

   }
   //wait so that the refresh time for the leds will be adequate
   delayMicroseconds(2000);

  
 }
}


//****************************************************************************//
//
//  An overridden function for displaying digits on the 7-segment display
//  using primitive boolean values.
//
//****************************************************************************//

void Display::sevenSegment(int value1, int value2)
{

   //switch each transistor to off-state for initialization
   for (int j=3;j>=0;j--){
    digitalWrite(_transistors[j],LOW);
   }
   
   delayMicroseconds(500);
   digitalWrite(_latch,LOW);

   //choose which digit to enter to the shift reg and
   //switch the corresponding transistor on
   shiftOut(_data,_clock,MSBFIRST,value1);
   digitalWrite(_latch,HIGH);
   delayMicroseconds(500);
   digitalWrite(_transistors[0],HIGH);

   //wait so that the refresh time for the leds will be adequate
   delayMicroseconds(2000);

   for (int j=3;j>=0;j--){
    digitalWrite(_transistors[j],LOW);
   }
   
   delayMicroseconds(500);
   digitalWrite(_latch,LOW);

   shiftOut(_data,_clock,MSBFIRST,value2);
   digitalWrite(_latch,HIGH);
   delayMicroseconds(500);
   digitalWrite(_transistors[1],HIGH);

   delayMicroseconds(2000);

   
}

//****************************************************************************//
//
//  A function for displaying digits on the row of leds
//
//****************************************************************************//

void Display::ledArray(int value)
{
   int currentDigit = value;

   //switch each transistor to off-state for initialization
   for (int j=3;j>=0;j--){
    digitalWrite(_transistors[j],LOW);
   }
   
   delayMicroseconds(500);
   digitalWrite(_latch,LOW);

   shiftOut(_data,_clock,MSBFIRST,currentDigit);
   digitalWrite(_latch,HIGH);
   delayMicroseconds(500);
   digitalWrite(_transistors[2],HIGH);

   //wait so that the refresh time for the leds will be adequate
   delayMicroseconds(2000);

}
