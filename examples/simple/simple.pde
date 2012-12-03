/*----------------------------------------------------------------------*
 * Example sketch for Arduino ds18b20 Library by Jack Christensen       *
 *                                                                      *
 * A simple example, just reading the sensor and displaying the         *
 * individual readings and the moving average.                          *
 * Connect the DS18B20's data (DQ) pin to Arduino pin 2.                *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include <ds18b20.h>              //https://github.com/JChristensen/ds18b20
#include <OneWire.h>              //http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <movingAvg.h>            //https://github.com/JChristensen/movingAvg
#include <Streaming.h>            //http://arduiniana.org/libraries/streaming/

#define DS_PIN 2                  //connect DS18B20 to this pin

DS18B20 ds(DS_PIN);               //declare the DS18B20
int minutes, seconds;             //approx time since sketch started

void setup(void)
{
    Serial.begin(115200);
}

void loop(void)
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
