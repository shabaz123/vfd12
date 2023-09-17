// VfdTest.ino
// rev 1 - Sep 2023 - shabaz
// this code demonstrates the Vfd12 library

// ********* includes *************
#include "Vfd12.h"

// *********** defines ************
#define DIN_PIN 2
#define CLK_PIN 4
#define CS_PIN 7
#define EN_PIN 8

#define DELAY_MS delay
#define FOREVER 1

// ********* constants *************
// Custom characters array. Up to 8 characters allowed.
// Custom characters are 5 bytes long for 7x5 dot matrix,
// where the most significant bit (bit 7) is always zero.
// Each byte corresponds to one column of pixels,
// where the first byte is the leftmost column.
// The lowest pixel in a column is bit 6,
// and the highest pixel in a column is bit 0 
const char CUST_CHAR[][5] = {
  {0x7f, 0x3e, 0x1c, 0x08, 0x00}, // 0: right-pointing triangle
  {0x00, 0x08, 0x1c, 0x3e, 0x7f}, // 1: left-pointing triangle
  {0x7f, 0x7f, 0x00, 0x7f, 0x7f}, // 2: pause symbol
  {0x01, 0x01, 0x01, 0x01, 0x01}, // 3: overscore 
  {0x07, 0x05, 0x07, 0x00, 0x00}, // 4: degree symbol
  {0x7f, 0x07, 0x04, 0x04, 0x07}, // 5: u (micro) symbol
  {0x5e, 0x61, 0x01, 0x61, 0x5e}, // 6: ohm symbol
  {0x0c, 0x12, 0x7f, 0x12, 0x0c}, // 7: phi character
};

// ******* global variables **********
Vfd12 vfd(DIN_PIN, CLK_PIN, CS_PIN, EN_PIN);

// **************************************
// ************ functions ***************
// **************************************

// ********** setup() function **********
void setup()
{
    int i;
    Serial.begin(115200);
    vfd.init();
    // set up the custom characters
    for (i=0; i<8; i++) {
      vfd.custprog(i, CUST_CHAR[i]);
    }
}

// ********** loop() function ***********
void loop() {
    // put your main code here, to run repeatedly:
    while(FOREVER) {
        vfd.print(0, "Hello World!");
        DELAY_MS(1000);
        vfd.print(0, "Ready       ");
        vfd.printchar(6, 0x00); // print cust char #0 (right-pointing triangle)
        DELAY_MS(1000);
    }
}
