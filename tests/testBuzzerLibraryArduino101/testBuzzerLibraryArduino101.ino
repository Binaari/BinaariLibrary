/*

Title:                  buzzer library test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binaari/BinaariLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include "BinaariLibrary.h"

BinaariLibrary binaari;

void setup() {
    binaari.initialize();
}

void loop() {
    playZelda();
}

void playZelda() {
    
    
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// this song is the property of Nintendo, and is here for demonstration purposes only
  binaari.buzzer.beep(NOTE_D5, 100);
  delay(80);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_D6, 200); 
  delay(250);
  
  binaari.buzzer.beep(NOTE_D5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_D6, 200);
  delay(250);
  
  binaari.buzzer.beep(NOTE_E6, 200); 
  delay(200);
  binaari.buzzer.beep(NOTE_F6, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_E6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_F6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_E6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_C6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_A5, 100); 
  delay(300);
  
  binaari.buzzer.beep(NOTE_A5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_D5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_G5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_A5, 100); 
  delay(500);
  
  binaari.buzzer.beep(NOTE_A5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_D5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_G5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_E5, 100); 
  delay(500);
  
  
  
  binaari.buzzer.beep(NOTE_D5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_D6, 200); 
  delay(250);
  
  binaari.buzzer.beep(NOTE_D5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_D6, 200);
  delay(250);
  
  binaari.buzzer.beep(NOTE_E6, 200); 
  delay(200);
  binaari.buzzer.beep(NOTE_F6, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_E6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_F6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_E6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_C6, 100); 
  delay(80);
  binaari.buzzer.beep(NOTE_A5, 100); 
  delay(300);
  
  binaari.buzzer.beep(NOTE_A5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_D5, 200); 
  delay(100);
  binaari.buzzer.beep(NOTE_F5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_G5, 100); 
  delay(100);
  binaari.buzzer.beep(NOTE_A5, 300);
  delay(100);
  binaari.buzzer.beep(NOTE_A5, 200);
  delay(100);
  binaari.buzzer.beep(NOTE_D5, 300);
  delay(2000);
}