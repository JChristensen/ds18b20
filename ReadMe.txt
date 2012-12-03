ReadMe file for Arduino DS18B20 Library v1.0
https://github.com/JChristensen/DS18B20
Jack Christensen Dec 2012

This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License. To view a copy of this license, visit
http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to Creative
Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

================================================================================
Arduino library to support the Maxim Integrated DS18B20 temperature sensor.
This library is intended for use with the Arduino OneWire.h library,
http://www.pjrc.com/teensy/td_libs_OneWire.html
and my Moving Average library,
https://github.com/JChristensen/movingAvg

This library is somewhat minimal and reflects the way I like to do things,
namely reading the temperature sensor on a regular basis, and using a
moving average to smooth readings. So it may not fit someone else's
requirements. The main motivation for the library was to hide the details
of the OneWire and movingAvg libraries, and provide a set of straightforward
methods and properties for dealing with the DS18B20.

--------------------------------------------------------------------------------
To use the library:
(1) Go to https://github.com/JChristensen/ds18b20/downloads and download the
file in the compressed format of your choice (zip or tar.gz) to a convenient
location on your PC.
(2) Uncompress the downloaded file. This will result in a folder containing all
the files for the library, that has a name similar to "JChristensen-
ds18b20-42e98a7".
(3) Rename the folder to just "ds18b20".
(4) Copy the renamed folder to the Arduino sketchbook\libraries folder.

--------------------------------------------------------------------------------
The following example sketch are included with the ds18b20 library:

simple: A simple example that just reads the sensor and displays the
        individual readings and the moving average.

--------------------------------------------------------------------------------
To use the ds18b20 library, the OneWire and movingAvg libraries must also be
included. For brevity, these includes are not repeated in the examples below:
#include <ds18b20.h>          //https://github.com/JChristensen/ds18b20
#include <OneWire.h>          //http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <movingAvg.h>        //https://github.com/JChristensen/movingAvg

================================================================================
DECLARING A DS18B20 OBJECT

To declare a DS18B20 object, simply pass it the pin the sensor is connected to:

#define DS_PIN 2
DS18B20 ds(DS_PIN);

================================================================================
READING THE SENSOR

To read the sensor, call the readSensor(int seconds) method, passing it the
seconds from the current time. readSensor will initiate the temperature
conversion on seconds = 05, 15, 25, etc., and will read the temperature value
on seconds = 06, 16, 26, etc. It simply returns for other values of seconds.
(I usually call readSensor once per second.)

readSensor() returns false if a CRC error was encountered when reading the
temperature value, else it returns true.

Example:

#define DS_PIN 2
DS18B20 ds(DS_PIN);
int seconds;

if ( !ds.readSensor(seconds) ) {
    //CRC ERROR
}
else {
    //do whatever
}

================================================================================
TEMPERATURE AND RELATED PROPERTIES

The dataValid property is false until the first time a temperature is read,
and true thereafter:

if ( ds.dataValid ) {
    //process the temperature reading
}
else {
    //wait for a while
}

--------------------------------------------------------------------------------
The tF10 property represents the last temperature read, as an integer, in
degrees Fahrenheit times 10:

int myTempF;
float myFloatTemp;
myTempF = ds.tF10;
myFloatTemp = myTempF / 10.0;

--------------------------------------------------------------------------------
The tC16 property is used similarly to the tF10 property, except it
represents the last temperature read, as an integer, in degrees
Celsius times 16:

int myTempC;
float myFloatTemp;
myTempCF = ds.tC16;
myFloatTemp = myTempC / 16.0;

--------------------------------------------------------------------------------
The avgTF10 property is used exactly like the tF10 property, except it
represents the moving average of the last six tF10 readings, as an integer, in
degrees Fahrenheit times 10.

--------------------------------------------------------------------------------
