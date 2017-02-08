/*

Title:                  RotationalEncoder library test using USB serial interface
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
*/

#include "RotationalEncoder.h"

RotationalEncoder rotEnc;
unsigned int lastReportedPos;
unsigned int encoderPos;

int lastButtonState;
int buttonState;

void setup() {
    Serial.begin(9600);
    While(!Serial) {
        ;
    }

    Serial.println("Connection success");

    rotEnc.initialize();

    Serial.println("Encoder initialized");



}

void loop() {
    
    // read the pushbutton input pin:
    buttonState = digitalRead(rotEnc.getPinButton());

    if (buttonState != lastButtonState) {
        if (buttonState == HIGH)
        Serial.println("Encoder button pressed");
    }
    rotEnc.setTurn(true);

    encoderPos = rotEnc.getEncoderPos();

    if(lastReportedPos != encoderPos) {
        Serial.print("Encoder position: ");
        Serial.println(encoderPos);
        lastReportedPos = encoderPos;
    }

    lastButtonState = buttonState;

}

void interruptA() {
    rotEnc.doInterruptA();
}

void interruptB() {
    rotEnc.doInterruptB();
}