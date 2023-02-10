// Arduino ds18b20 Library
// https://github.com/JChristensen/ds18b20
// Copyright (C) 2010-2023 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

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
