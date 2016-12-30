/*

Title:                  switch serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

int switch1 = A3;
String switchResponseHIGH = "Switch is in position 1";
String switchResponseLOW = "Switch is in position 0";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Connection success");


  pinMode(switch1, INPUT);
  Serial.println("Pin A3 input");
}

void loop() {
  if (digitalRead(switch1) == HIGH) {
    Serial.println(switchResponseHIGH);
  } else {
    Serial.println(switchResponseLOW);
  }
  delay(1000);
}