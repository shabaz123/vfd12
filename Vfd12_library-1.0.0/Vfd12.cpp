// vfd12.cpp
// rev 1 - Sep 2023 - shabaz
// based on https://github.com/hexesdesu/ESP32VFDClock/blob/master/ESP32VFDClock/ESP32VFDClock.ino
// VFD controller

#include "Vfd12.h"

// *****************************************************
// ************ Vfd12 class implementation *************
// *****************************************************
Vfd12::Vfd12(byte din_pin, byte clk_pin, byte cs_pin, byte en_pin)
: _din_pin(din_pin), _clk_pin(clk_pin), _cs_pin(cs_pin), _en_pin(en_pin)
{
    pinMode(_din_pin, OUTPUT);
    pinMode(_clk_pin, OUTPUT);
    pinMode(_cs_pin, OUTPUT);
    pinMode(_en_pin, OUTPUT);
    digitalWrite(_cs_pin, HIGH);
    digitalWrite(_en_pin, HIGH);
    digitalWrite(_din_pin, LOW);
    digitalWrite(_clk_pin, LOW);
}

void Vfd12::init()
{
    delay(10); // 10msec delay
    digitalWrite(_en_pin, HIGH);
    delay(10);

    digitalWrite(_cs_pin, LOW);
    write(0xe0);
    delayMicroseconds(5);
    write(11); // set to 11 for 12 character display
    delayMicroseconds(5);
    digitalWrite(_cs_pin, HIGH);
    delayMicroseconds(5);
    
    digitalWrite(_cs_pin, LOW);
    write(0xe4);
    delayMicroseconds(5);
    write(0x33); //set brightness
    delayMicroseconds(5);
    digitalWrite(_cs_pin, HIGH);
    delayMicroseconds(5);
}

void Vfd12::write(uint8_t data)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        digitalWrite(_clk_pin, LOW);
        if (data & 0x01)
            digitalWrite(_din_pin, HIGH);
        else
            digitalWrite(_din_pin, LOW);
        data >>= 1;
        digitalWrite(_clk_pin, HIGH);
    }
}

void Vfd12::cmd(uint8_t command)
{
    digitalWrite(_cs_pin, LOW);
    write(command);
    digitalWrite(_cs_pin, HIGH);
    delayMicroseconds(5);
}

void Vfd12::show()
{
    digitalWrite(_cs_pin, LOW);
    write(0xe8);
    digitalWrite(_cs_pin, HIGH);
}

void Vfd12::custprog(unsigned char idx, const char *str)
{
    unsigned char i;
    digitalWrite(_cs_pin, LOW);
    write(0x40 + idx);
    for (i = 0; i < 5; i++)
    {
        write(*str);
        str++;
    }
    digitalWrite(_cs_pin, HIGH);
    show();
}

void Vfd12::printchar(unsigned char x, unsigned char chr)
{
    digitalWrite(_cs_pin, LOW);
    write(0x20 + x);
    write(chr);
    digitalWrite(_cs_pin, HIGH);
    show();
}

void Vfd12::print(unsigned char idx, const char *str)
{
    digitalWrite(_cs_pin, LOW);  // start transfer
    write(0x20 + idx); // address reg start position
    while (*str)
    {
        write(*str); //ascii convert with corresponding character table
        str++;
    }
    digitalWrite(_cs_pin, HIGH); // stop transmission
    show();
}
