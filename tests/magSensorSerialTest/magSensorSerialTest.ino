/*

Title:                  magnetometric sensor serial test
Original creator:       Jussi Wallin
Original release URL:   https://github.com/Binarieshield/BinarieLibrary
Original release date:  12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#include "Wire.h"
#include <math.h>


void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
    }
    Serial.println("Connection success");

    // Initialise I2C communication as MASTER 
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
    Serial.begin(9600);
  
    // Start I2C Transmission
    Wire.beginTransmission(0x0E);
    // Select control register-1
    Wire.write(0x10);
    // Set active mode enabled
    Wire.write(0x01);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);

    Serial.println("Magnetometer initialized");
}

void loop() {
     unsigned int data[6];
  
    // Start I2C Transmission
    Wire.beginTransmission(0x0E);
    // Select data register
    Wire.write(0x01);
    // Stop I2C Transmission
    Wire.endTransmission();

    // Request 6 bytes of data
    Wire.requestFrom(0x0E, 6);

    // Read 6 bytes of data
    // xMag lsb, xMag msb, yMag lsb, y Mag msb, zMag lsb, zMag msb
    if(Wire.available() == 6)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        data[2] = Wire.read();
        data[3] = Wire.read();
        data[4] = Wire.read();
        data[5] = Wire.read();
    }
  
    // Convert the data
    int xMag = ((data[1] * 256) + data[0]);
    int yMag = ((data[3] * 256) + data[2]);
    int zMag = ((data[5] * 256) + data[4]);
    
    // Output data to serial monitor
    Serial.print("Magnetic field in X Axis : ");
    Serial.println(xMag);
    Serial.print("Magnetic field in Y Axis : ");
    Serial.println(yMag);
    Serial.print("Magnetic field in Z Axis : ");
    Serial.println(zMag);

    // Serial.print("Compass: ");
    // double angle = (atan2(yMag, xMag)) * 180/M_PI;

    // if (yMag < 0) {
    //     if (xMag < 0)
    //         angle -= 90;
    // } else {
    //     if (xMag < 0)
    //         angle += 90;
    // }

    // if (angle < 0)
    //     angle += 360;
    // if (angle > 360)
    //     angle -= 360;

    // if (angle >= 0 && angle < 22.5) {
    //     Serial.println("N");
    // } else if (angle >= 22.5 && angle < 67.5) {
    //     Serial.println("NE");
    // } else if (angle >= 67.5 && angle < 112.5) {
    //     Serial.println("E");
    // } else if (angle >= 112.5 && angle < 157.5) {
    //     Serial.println("SE");
    // } else if (angle >= 157.5 && angle < 202.5) {
    //     Serial.println("S");
    // } else if (angle >= 202.5 && angle < 247.5) {
    //     Serial.println("SW");
    // } else if (angle >= 247.5 && angle < 292.5) {
    //     Serial.println("W");
    // } else if (angle >= 292.5 && angle < 337.5) {
    //     Serial.println("NW");
    // } else if (angle >= 337.5 && angle < 360) {
    //     Serial.println("N");
    // } else {
    //     Serial.print("Error! Heading: ");
    //     Serial.println(angle);
    // }
    
    delay(1000);
}
