/*

Title:                  env sensor serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include "BME280_MOD-1022.h"
#include "Wire.h"


void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    }
    Serial.println("Connection success");

    Wire.begin();


    unsigned int chipID = BME280.readChipId();

    Serial.print("ChipID = 0x");
    Serial.println(chipID, HEX);


    BME280.readCompensationParams();

    BME280.writeOversamplingPressure(os1x);
    BME280.writeOversamplingHumidity(os1x);
    BME280.writeOversamplingTemperature(os1x);

    BME280.writeStandbyTime(tsb_0p5ms);
    BME280.writeFilterCoefficient(fc_16);

    BME280.writeMode(smNormal);


    Serial.println("Environmental sensor initialized");
}

void loop() {
    while(BME280.isMeasuring()) {

    }

    BME280.readMeasurements();

    Serial.print("Temp=");
    Serial.println(BME280.getTemperature());  // must get temp first
    Serial.print("Humidity=");
    Serial.println(BME280.getHumidity());
    Serial.print("Pressure=");
    Serial.println(BME280.getPressure());
    Serial.print("PressureMoreAccurate=");
    Serial.println(BME280.getPressureMoreAccurate());  // use int64 calculcations
    Serial.print("TempMostAccurate=");
    Serial.println(BME280.getTemperatureMostAccurate());  // use double calculations
    Serial.print("HumidityMostAccurate=");
    Serial.println(BME280.getHumidityMostAccurate()); // use double calculations
    Serial.print("PressureMostAccurate=");
    Serial.println(BME280.getPressureMostAccurate()); // use double calculations
  
    delay(5000);
}
