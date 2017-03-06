/*

Title:                  Test Environmental Sensor Library
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include "BinaariLibrary.h"

BinaariLibrary binaari;

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    }
    Serial.println("Connection success");

    binaari.initialize();

    Serial.println(binaari.env.readByte(REG_CHIPID));
    Serial.println("Environmental sensor initialized");
}

void loop() {

    Serial.println(binaari.env.read24Bits(REG_TEMPDATA));
    Serial.print("Temp=");
    Serial.println(binaari.env.readTemperature());  // must get temp first
    // Serial.print("Humidity=");
    // Serial.println(BME280.getHumidity());
    // Serial.print("Pressure=");
    // Serial.println(BME280.getPressure());
    // Serial.print("PressureMoreAccurate=");
    // Serial.println(BME280.getPressureMoreAccurate());  // use int64 calculcations
    // Serial.print("TempMostAccurate=");
    // Serial.println(BME280.getTemperatureMostAccurate());  // use double calculations
    // Serial.print("HumidityMostAccurate=");
    // Serial.println(BME280.getHumidityMostAccurate()); // use double calculations
    // Serial.print("PressureMostAccurate=");
    // Serial.println(BME280.getPressureMostAccurate()); // use double calculations
  
    delay(5000);
}
