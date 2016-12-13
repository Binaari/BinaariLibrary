/*

Title:                  encoder rotation serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

int encA = 3;
int encB = 2;
String encCWResponse = "Encoder turned CW";
String encCCWResponse = "Encoder turned CCW";
volatile unsigned int encoderPos = 0;
unsigned int lastReportedPos = 1;
volatile boolean turn = false;

boolean Aset = false;
boolean Bset = false;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Connection success");


  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encA), doInterruptA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encB), doInterruptB, CHANGE);
  Serial.println("Pins 2, 3 input + interrupts");
}

void loop() {
  turn = true;

  if (lastReportedPos != encoderPos) {
    Serial.print("encoder pos: ");
    Serial.println(encoderPos);
    lastReportedPos = encoderPos;
  }

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
