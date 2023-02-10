// Arduino ds18b20 Library
// https://github.com/JChristensen/ds18b20
// Copyright (C) 2010-2023 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "ds18b20.h"

// constructor
DS18B20::DS18B20(uint8_t pin) : OneWire(pin), m_avg(6)
{
    m_canRead = false;
    dataValid = false;
}

// initialization
void DS18B20::begin()
{
    m_avg.begin();
}

// call readSensor() periodically, e.g. once per second.
// "seconds" parameter is the seconds derived from the current time.
// starts the temperature conversion on seconds = 05, 15, 25, etc.
// reads the temperature value on seconds = 06, 16, 26, etc.
// returns true if successful, false for CRC error.
//
bool DS18B20::readSensor(int seconds)
{
    switch (seconds % 10) {

    case 5:                     //start temperature conversion
        reset();
        skip();
        write(0x44);
        m_canRead = true;       //ok to read now
        break;

    case 6:                     //read temperature
        if (m_canRead) {        //don't attempt to read if a conversion hasn't been started
            reset();
            skip();
            write(0xBE);        //read scratchpad

            for ( int i=0; i<9; i++) {    //read 9 bytes
                m_dsData[i] = read();
            }
            if (OneWire::crc8(m_dsData, 8) == m_dsData[8]) {
                dataValid = true;
                avgTF10 = m_avg.reading( toFahrenheit(m_dsData[1], m_dsData[0]) );
            }
            else {
                return false;    //CRC error
            }
        }
        break;
    }
    return true;
}

// Convert 12-bit °C temp from DS18B20 to an integer which is °F * 10
int DS18B20::toFahrenheit(byte tempMSB, byte tempLSB)
{
    tC16 = (tempMSB << 8) + tempLSB;
    long tF160 = (long)tC16 * 18L;      //160 times the temp in deg F (but without the 32 deg offset)
    tF10 = tF160 / 16L;
    if (tF160 % 16 >= 8) tF10++;        //round up to the next tenth if needed
    tF10 = tF10 + 320;                  //add in the offset (*10)
    return tF10;
}
