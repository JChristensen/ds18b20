/*----------------------------------------------------------------------*
 * Arduino ds18b20 Library v1.0                                         *
 * Jack Christensen Dec 2010                                            *
 *                                                                      *
 * A basic library for the Maxim Integrated DS18B20 temperature sensor  *
 * that inherits the OneWire class and also uses my movingAvg library   *
 * to hide the associated details from the user and provide             *
 * straightforward methods and properties for the sensor.               *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include <movingAvg.h>            //https://github.com/JChristensen/movingAvg
#include <OneWire.h>              //http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <Arduino.h>

class DS18B20 : public OneWire
{
    public:
        DS18B20(uint8_t pin);
        void begin();
        bool readSensor(int seconds);
        bool dataValid;
        int tF10;        //last reading, 10 times the temp in deg F
        int avgTF10;     //moving average of tF10 readings
        int tC16;        //last reading, 16 times the temperature in deg C (DS18B20 resolution is 1/16 °C)

    private:
        int toFahrenheit(byte tempMSB, byte tempLSB);
        bool m_canRead;
        uint8_t m_dsData[12];
        movingAvg m_avg{6};
};
