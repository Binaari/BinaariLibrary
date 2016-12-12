/*

Title:                  button serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

int button1 = 5;
int button2 = 6;
String button1Response = "Button 1 is pressed";
String button2Response = "Button 2 is pressed";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println("Connection success");


  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.println("Pins 5 and 6 set to input");
}

void loop() {
  if (digitalRead(button1))
    Serial.println(button1Response);
  if (digitalRead(button2))
    Serial.println(button2Response);
  delay(1000);
}
