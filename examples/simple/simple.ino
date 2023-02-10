// Arduino ds18b20 Library
// https://github.com/JChristensen/ds18b20
// Copyright (C) 2010-2023 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// A simple example, just reading the sensor and displaying the
// individual readings and the moving average.
// Connect the DS18B20's data (DQ) pin to Arduino pin 2.

#include <ds18b20.h>            // https://github.com/JChristensen/ds18b20
#include <OneWire.h>            // https://www.pjrc.com/teensy/td_libs_OneWire.html
#include <movingAvg.h>          // https://github.com/JChristensen/movingAvg
#include <Streaming.h>          // https://github.com/janelia-arduino/Streaming

constexpr uint8_t DS_PIN {2};   // connect DS18B20 to this pin

DS18B20 ds(DS_PIN);             // define the DS18B20
int minutes, seconds;           // approx time since sketch started

void setup()
{
    Serial.begin(115200);
    ds.begin();
}

void loop()
{
    displayTime();
    if ( ds.readSensor(seconds) ) {
        if ( ds.dataValid ) {
            Serial << "Reading=" << _FLOAT(ds.tF10 / 10., 1);
            Serial << " Average=" << _FLOAT(ds.avgTF10 / 10., 1);
        }
        else {
            Serial << "... waiting for first reading";
        }
    }
    else {
        Serial << "CRC ERROR!" << endl;
    }
    Serial << endl;

    if (++seconds >= 60) {        //increment the time
        ++minutes;
        seconds = 0;
    }
    delay(1000);
}

void displayTime(void)
{
    if (minutes < 10) Serial << '0';
    Serial << _DEC(minutes) << ':';
    if (seconds < 10) Serial << '0';
    Serial << _DEC(seconds) << ' ';
}
