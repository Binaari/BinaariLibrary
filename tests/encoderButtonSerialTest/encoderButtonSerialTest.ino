/*

Title:                  encoder button serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

int encButton = 4;
String encButtonResponse = "Encoder Button is pressed";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Connection success");


  pinMode(encButton, INPUT);
  Serial.println("Pin 4 input");
}

void loop() {
    if (digitalRead(encButton) == HIGH)
        Serial.println(encButtonResponse);
  delay(1000);
}
