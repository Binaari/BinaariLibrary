/*

Title:                  lux sensor serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include "SparkFunTSL2561.h"
unsigned int integrationTime = 2;
unsigned int Channel1Data = 0;
unsigned int Channel2Data = 0;
double luxValue = 0.0;
SFE_TSL2561 lux;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Connection success");

  while(!lux.begin(0x29)) {
    Serial.print("lux begin I2C error: ");
    Serial.println(lux.getError());
  }

  unsigned char ID;
  
  if (lux.getID(ID))
  {
    Serial.print("Got factory ID: 0X");
    Serial.print(ID,HEX);
    Serial.println(", should be 0X5X");
  }

  while(!lux.setTiming(0, 0, integrationTime)) {
    Serial.print("timing set I2C error: ");
    Serial.println(lux.getError());
  }

  lux.setPowerUp();

  Serial.println("TSL2561 initialized");
}

void loop() {
    lux.getData(Channel1Data, Channel2Data);
    unsigned int error = lux.getError();
    if(error > 0) {
        Serial.print("Error :");
        Serial.println(error);
        return;
    }
    lux.getLux(0, integrationTime, Channel1Data, Channel2Data, luxValue);
    error = lux.getError();
    if(error > 0) {
        Serial.print("Error :");
        Serial.println(error);
        return;
    }
    Serial.print("Lux value: ");
    Serial.println(luxValue);
    delay(1000);
}
