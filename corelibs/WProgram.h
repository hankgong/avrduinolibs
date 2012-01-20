#ifndef WProgram_h
#define WProgram_h

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/interrupt.h>

#include "wiring.h"

#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t _pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
const static uint8_t A0 = 54;
const static uint8_t A1 = 55;
const static uint8_t A2 = 56;
const static uint8_t A3 = 57;
const static uint8_t A4 = 58;
const static uint8_t A5 = 59;
const static uint8_t A6 = 60;
const static uint8_t A7 = 61;
const static uint8_t A8 = 62;
const static uint8_t A9 = 63;
const static uint8_t A10 = 64;
const static uint8_t A11 = 65;
const static uint8_t A12 = 66;
const static uint8_t A13 = 67;
const static uint8_t A14 = 68;
const static uint8_t A15 = 69;
#else
const static uint8_t A0 = 14;
const static uint8_t A1 = 15;
const static uint8_t A2 = 16;
const static uint8_t A3 = 17;
const static uint8_t A4 = 18;
const static uint8_t A5 = 19;
const static uint8_t A6 = 20;
const static uint8_t A7 = 21;
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
const static uint8_t PPA0 = 22;
const static uint8_t PPA1 = 23;
const static uint8_t PPA2 = 24;
const static uint8_t PPA3 = 25;
const static uint8_t PPA4 = 26;
const static uint8_t PPA5 = 27;
const static uint8_t PPA6 = 28;
const static uint8_t PPA7 = 29;

const static uint8_t PPB0 = 53;
const static uint8_t PPB1 = 52;
const static uint8_t PPB2 = 51;
const static uint8_t PPB3 = 50;
const static uint8_t PPB4 = 10;
const static uint8_t PPB5 = 11;
const static uint8_t PPB6 = 12;
const static uint8_t PPB7 = 13;

const static uint8_t PPC0 = 37;
const static uint8_t PPC1 = 36;
const static uint8_t PPC2 = 35;
const static uint8_t PPC3 = 34;
const static uint8_t PPC4 = 33;
const static uint8_t PPC5 = 32;
const static uint8_t PPC6 = 31;
const static uint8_t PPC7 = 30;

const static uint8_t PPD0 = 21;
const static uint8_t PPD1 = 20;
const static uint8_t PPD2 = 19;
const static uint8_t PPD3 = 18;
const static uint8_t PPD4 = 70;
const static uint8_t PPD5 = 71;
const static uint8_t PPD6 = 72;
const static uint8_t PPD7 = 38;

const static uint8_t PPE0 = 0;
const static uint8_t PPE1 = 1;
const static uint8_t PPE2 = 73;
const static uint8_t PPE3 = 5;
const static uint8_t PPE4 = 2;
const static uint8_t PPE5 = 3;
const static uint8_t PPE6 = 74;
const static uint8_t PPE7 = 75;

const static uint8_t PPF0 = 54;
const static uint8_t PPF1 = 55;
const static uint8_t PPF2 = 56;
const static uint8_t PPF3 = 57;
const static uint8_t PPF4 = 58;
const static uint8_t PPF5 = 59;
const static uint8_t PPF6 = 60;
const static uint8_t PPF7 = 61;

const static uint8_t PPG0 = 41;
const static uint8_t PPG1 = 40;
const static uint8_t PPG2 = 39;
const static uint8_t PPG3 = 76;
const static uint8_t PPG4 = 77;
const static uint8_t PPG5 = 4;

const static uint8_t PPH0 = 17;
const static uint8_t PPH1 = 16;
const static uint8_t PPH2 = 78;
const static uint8_t PPH3 = 6;
const static uint8_t PPH4 = 7;
const static uint8_t PPH5 = 8;
const static uint8_t PPH6 = 9;
const static uint8_t PPH7 = 79;

const static uint8_t PPJ0 = 15;
const static uint8_t PPJ1 = 14;
const static uint8_t PPJ2 = 80;
const static uint8_t PPJ3 = 81;
const static uint8_t PPJ4 = 82;
const static uint8_t PPJ5 = 83;
const static uint8_t PPJ6 = 84;
const static uint8_t PPJ7 = 85;

const static uint8_t PPK0 = 62;
const static uint8_t PPK1 = 63;
const static uint8_t PPK2 = 64;
const static uint8_t PPK3 = 65;
const static uint8_t PPK4 = 66;
const static uint8_t PPK5 = 67;
const static uint8_t PPK6 = 68;
const static uint8_t PPK7 = 69;

const static uint8_t PPL0 = 49;
const static uint8_t PPL1 = 48;
const static uint8_t PPL2 = 47;
const static uint8_t PPL3 = 46;
const static uint8_t PPL4 = 45;
const static uint8_t PPL5 = 44;
const static uint8_t PPL6 = 43;
const static uint8_t PPL7 = 42;
#else
//const static uint8_t PPC0 = 8;
//const static uint8_t PPC1 = 9;
//const static uint8_t PPC2 = 10;
//const static uint8_t PPC3 = 11;
#endif

#endif //end of define cpplus

#endif
