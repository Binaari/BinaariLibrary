/*

Title: 					BiaariLibrary - SevenSegment
Original creator: 		Jussi Wallin
Original release URL: 	https://github.com/Binaari/BinaariLibrary
Original release date:	12/12/2016 (dd/mm/yyyy)
License:
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

*/

#ifndef BinaariSevenSeg_h
#define BinaariSevenSeg_h
#include "Wire.h"
#include "Arduino.h"

#define SENSOR_ADDRESS 0x76

enum
{
    REG_DIG_T1 = 0x88,
    REG_DIG_T2 = 0x8A,
    REG_DIG_T3 = 0x8C,

    REG_DIG_P1 = 0x8E,
    REG_DIG_P2 = 0x90,
    REG_DIG_P3 = 0x92,
    REG_DIG_P4 = 0x94,
    REG_DIG_P5 = 0x96,
    REG_DIG_P6 = 0x98,
    REG_DIG_P7 = 0x9A,
    REG_DIG_P8 = 0x9C,
    REG_DIG_P9 = 0x9E,

    REG_DIG_H1 = 0xA1,
    REG_DIG_H2 = 0xE1,
    REG_DIG_H3 = 0xE3,
    REG_DIG_H4 = 0xE4,
    REG_DIG_H5 = 0xE5,
    REG_DIG_H6 = 0xE7,

    REG_CHIPID = 0xD0,
    REG_VERSION = 0xD1,
    REG_SOFTRESET = 0xE0,

    REG_CAL26 = 0xE1,

    REG_CTRLHUMID = 0xF2,
    REG_STATUS = 0XF3,
    REG_CONTROL = 0xF4,
    REG_CONFIG = 0xF5,
    REG_PRESSDATA = 0xF7,
    REG_TEMPDATA = 0xFA,
    REG_HUMIDDATA = 0xFD
};

/***************************************************************/
//Define sensor parameters

enum sensorOversampling
{
    OS_X0 = 0b000,
    OS_X1 = 0b001,
    OS_X2 = 0b010,
    OS_X4 = 0b011,
    OS_X8 = 0b100,
    OS_X16 = 0b101
};

enum sensorMode
{
    S_SLEEP = 0b00,
    S_FORCED = 0b01,
    S_NORMAL = 0b11
};

enum sensorFilter
{
    SF_X0 = 0b000,
    SF_X2 = 0b001,
    SF_X4 = 0b010,
    SF_X8 = 0b011,
    SF_X16 = 0b100
};

// standby durations in ms
enum standbyDuration
{
    SB_0_5 = 0b000,
    SB_10 = 0b110,
    SB_20 = 0b111,
    SB_62_5 = 0b001,
    SB_125 = 0b010,
    SB_250 = 0b011,
    SB_500 = 0b100,
    SB_1000 = 0b101
};
/***************************************************************/

class EnvironmentSensor
{

    int tempCompCoeff;

    struct
    {
        short dig_T1;
        short dig_T2;
        short dig_T3;

        unsigned short dig_P1;
        short dig_P2;
        short dig_P3;
        short dig_P4;
        short dig_P5;
        short dig_P6;
        short dig_P7;
        short dig_P8;
        short dig_P9;

        unsigned char dig_H1;
        short dig_H2;
        unsigned char dig_H3;
        short dig_H4;
        short dig_H5;
        char dig_H6;
    } calibrationData;

    // The config register
    struct
    {
        //standby time
        unsigned int t_sb : 3;
        //filter level
        unsigned int filter : 3;
        //spi 3 wire enable
        unsigned int spi3w_en : 1;

        unsigned int get()
        {
            return (t_sb << 5) | (filter << 3) | spi3w_en;
        }
    } config;

    // The ctrl_meas register
    struct
    {
        //oversampling temperature
        unsigned int osrs_t : 3;
        //oversampling pressure
        unsigned int osrs_p : 3;
        //measuring mode
        unsigned int mode : 2;

        unsigned int get()
        {
            return (osrs_t << 5) | (osrs_p << 3) | mode;
        }
    } ctrl_meas;

    // The ctrl_hum register
    struct
    {

        // oversampling pressure
        unsigned int osrs_h : 3;

        unsigned int get()
        {
            return (osrs_h);
        }
    } ctrl_hum;

  public:
    void initialize()
    {

        Wire.begin(); //start I2C
        if (readByte(REG_CHIPID) != 0x60)
        {
            return;
        }
        writeByte(REG_SOFTRESET, 0xB6);

        delay(5000);

        if (isCopyingCoeffsFromNVM())
            delay(50);

        readCompCoeffs();

        setParameters();
    }

    /***************************************************************/
    // single byte read and write

    // Write to register on I2C
    void writeByte(byte registerAddress, byte value)
    {
        Wire.beginTransmission(SENSOR_ADDRESS);
        Wire.write(registerAddress);
        Wire.write(value);
        Wire.endTransmission();
    }

    byte readByte(byte registerAddress)
    {
        Wire.beginTransmission(SENSOR_ADDRESS);
        Wire.write(registerAddress);
        Wire.endTransmission();
        Wire.requestFrom(SENSOR_ADDRESS, 1);
        return Wire.read();
    }
    /***************************************************************/

    /***************************************************************/
    // signed and unsigned short read
    unsigned short readUshort(byte registerAddress)
    {

        Wire.beginTransmission(SENSOR_ADDRESS);
        Wire.write(registerAddress);
        Wire.endTransmission();
        Wire.requestFrom(SENSOR_ADDRESS, 2);
        return (Wire.read() << 8) | Wire.read();
    }

    short readShort(byte registerAddress)
    {
        return (short)readUshort(registerAddress);
    }

    /***************************************************************/

    /***************************************************************/
    // signed and unsigned short byte swapped read
    unsigned short readSwappedUshort(byte registerAddress)
    {
        unsigned short tmp = readUshort(registerAddress);
        return (tmp << 8) | (tmp >> 8);
    }

    short readSwappedShort(byte registerAddress)
    {
        return (short)readSwappedUshort(registerAddress);
    }

    /***************************************************************/

    /***************************************************************/
    // read 24-bit values
    unsigned int read24Bits(byte registerAddress)
    {

        unsigned int value;

        Wire.beginTransmission(SENSOR_ADDRESS);
        Wire.write(registerAddress);
        Wire.endTransmission();
        Wire.requestFrom(SENSOR_ADDRESS, 3);

        value = Wire.read();
        value <<= 8;
        value |= Wire.read();
        value <<= 8;
        value |= Wire.read();

        return value;
    }

    /***************************************************************/

    //check if sensor is busy with updating the coefficient image
    bool isCopyingCoeffsFromNVM()
    {
        if ((readByte(REG_STATUS) & 0x01) != 0)
            return false;
        return true;
    }

    void readCompCoeffs()
    {
        //temperature
        calibrationData.dig_T1 = readSwappedUshort(REG_DIG_T1);
        calibrationData.dig_T2 = readSwappedShort(REG_DIG_T2);
        calibrationData.dig_T3 = readSwappedShort(REG_DIG_T3);

        //pressure
        calibrationData.dig_P1 = readSwappedUshort(REG_DIG_P1);
        calibrationData.dig_P2 = readSwappedShort(REG_DIG_P2);
        calibrationData.dig_P3 = readSwappedShort(REG_DIG_P3);
        calibrationData.dig_P4 = readSwappedShort(REG_DIG_P4);
        calibrationData.dig_P5 = readSwappedShort(REG_DIG_P5);
        calibrationData.dig_P6 = readSwappedShort(REG_DIG_P6);
        calibrationData.dig_P7 = readSwappedShort(REG_DIG_P7);
        calibrationData.dig_P8 = readSwappedShort(REG_DIG_P8);
        calibrationData.dig_P9 = readSwappedShort(REG_DIG_P9);

        //Humidity
        calibrationData.dig_H1 = readByte(REG_DIG_H1);
        calibrationData.dig_H2 = readSwappedShort(REG_DIG_H2);
        calibrationData.dig_H3 = readByte(REG_DIG_H3);
    }

    void setParameters(sensorMode mode = S_NORMAL,
                       sensorOversampling tempOS = OS_X16,
                       sensorOversampling pressOS = OS_X16,
                       sensorOversampling humOS = OS_X16,
                       sensorFilter filter = SF_X16,
                       standbyDuration duration = SB_10)
    {
        ctrl_meas.mode = mode;
        ctrl_meas.osrs_t = tempOS;
        ctrl_meas.osrs_p = pressOS;

        ctrl_hum.osrs_h = humOS;
        config.filter = filter;
        config.t_sb = duration;

        writeByte(REG_CONFIG, config.get());
        writeByte(REG_CTRLHUMID, ctrl_hum.get());
        writeByte(REG_CONTROL, ctrl_meas.get());
    }

    float readTemperature()
    {
        int var1, var2;

        int adc_T = read24Bits(REG_TEMPDATA);
        if (adc_T == 0x800000)
            return NAN;

        adc_T >>= 4;

        var1 = ((((adc_T >> 3) - ((int)calibrationData.dig_T1 << 1))) *
                ((int)calibrationData.dig_T2)) >> 11;

        var2 = (((((adc_T >> 4) - ((int)calibrationData.dig_T1)) *
                  ((adc_T >> 4) - ((int)calibrationData.dig_T1))) >> 12) *
                ((int)calibrationData.dig_T3)) >> 14;

        tempCompCoeff = var1 + var2;

        float T = (tempCompCoeff * 5 + 128) >> 8;
        return T/100;
    }
};

#endif