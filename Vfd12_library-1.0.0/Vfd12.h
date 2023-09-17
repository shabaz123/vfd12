// Vfd12.h
// rev 1 - Sep 2023 - shabaz

#ifndef VFD12_H
#define VFD12_H

#include "Arduino.h"

// defines


// class definition
class Vfd12
{
    public:
        // Vfd12 object requres 4 pins for use as digital outputs
        Vfd12(byte din_pin, byte clk_pin, byte cs_pin, byte en_pin);
        // init() will enable the display, set 12 character mode, and set brightness
        void init();
        // show() might not be needed by the user, but is used by the library
        void show();
        // custprog() will program a custom character into the controller
        void custprog(unsigned char idx, const char *str);
        // printchar() will print a single character to the display, idx is the position (0-11)
        void printchar(unsigned char x, unsigned char chr);
        // print() will print a string to the display, idx is the position (0-11)
        void print(unsigned char idx, const char *str);
    private:
        // write() will write a byte to the controller chip
        void write(uint8_t data);
        // cmd() will write a command byte to the controller chip
        void cmd(uint8_t command);
        // member variables
        byte _din_pin;
        byte _clk_pin;
        byte _cs_pin;
        byte _en_pin;
};

#endif // VFD12_H
