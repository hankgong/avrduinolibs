/*
 * pinterrupt.c
 *
 *  Created on: 2011-10-27
 *      Author: bionik
 *
 *      Interrupt library, which is developed based on PcInt, is extended to support atmega
 *      1280/2560 chips.
 */

#include "pins_arduino.h"

//Both mega168/328 and mega1280/2560 has 24 pcints
volatile uint8_t *port_to_pcmask[] = {
	&PCMSK0,
	&PCMSK1,
	&PCMSK2
};

int PCintMode[24];
static void PCint(uint8_t portindex);

//define the interrupts handling functions
typedef void (*voidFuncPtr)(void);
voidFuncPtr PCintFunc[24] = { NULL };

volatile uint8_t PCintLast[3];

void PCattachInterrupt(uint8_t pin, void (*userFunc)(void), int mode)
{
	uint8_t bit;

	uint8_t port = digitalPinToPort(pin);

	uint8_t slot = digitalPinToPCMask(pin);;
	volatile uint8_t *pcmask;
	//printf("attaching %d\n\r", slot);

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	if(slot/8 !=1)
		bit = digitalPinToBitMask(pin);
	else if(slot/8 == 1){

		if(slot==8)
			bit = _BV(0);
		else {
			bit = digitalPinToBitMask(pin);
			bit <<= 1;
		}
	}
#else
	bit = digitalPinToBitMask(pin);
#endif

	// from the the mask index to pcmask register mapping
	// eg. 16 --> 2
	//map pin to PCIR register
	if (port == NOT_A_PORT) {
		//printf("not a port \n\r");
		return;
	} else {
		pcmask = port_to_pcmask[slot/8];
	}

	// hook the interrupt with mode and handling functions
	PCintMode[slot] = mode;
	PCintFunc[slot] = userFunc;

	// set the mask and enable the interrupt
	//printf("%d testing enabling PCICR %d\n\r", bit, slot/8);
	*pcmask |= bit;
	//printf("pcmask %x\n\r", *pcmask);
	PCICR |= 0x01 << (slot/8);
}


void PCdetachInterrupt(uint8_t pin)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	uint8_t slot;
	volatile uint8_t *pcmask;

	// from the the mask index to pcmask register mapping
	// eg. 16 --> 2
	slot = digitalPinToPCMask(pin);

	//map pin to PCIR register
	if (port == NOT_A_PORT) {
		return;
	} else {
		pcmask = port_to_pcmask[slot/8];
	}

	// disable the mask and interupt int the register
	*pcmask &= ~bit;

	if (*pcmask == 0) {
		PCICR &= ~(0x01 << (slot/8));
	}
}

SIGNAL(PCINT0_vect)
{
	PCint(0);
}

SIGNAL(PCINT1_vect)
{
	PCint(1);
}

SIGNAL(PCINT2_vect)
{
	PCint(2);
}

static void PCint(uint8_t intmaskport)
{
	uint8_t bit;
	uint8_t curr;

	uint8_t mask;
	uint8_t pin;


	//uint8_t portindex;


	//after doing this, maskport range from 0 to 2
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	uint8_t currtemp;

	if(intmaskport ==0)
		curr = *portInputRegister(2);
	else if(intmaskport == 2)
		curr = *portInputRegister(11);
	else if(intmaskport == 1){
		//printf("test portmask %x\n\r", *port_to_pcmask[intmaskport]);
		curr = *portInputRegister(10); 	//PORTJ
		currtemp = *portInputRegister(5);	//PORTE
		curr <<= 1; 					//shift left once to remove the highest bit
		curr &= 0xFE;						//shift right once to add an 0 bit to the highest bit
		currtemp &= 0x1;					//shift left 7 times to make the PE0 highest bit
		curr |= currtemp;				//put the highest bit of PE0 into PJ
		//printf("current pcint %x\n\r", curr);
	}
#else
	curr = *portInputRegister(intmaskport+2);
#endif
	//get the pin states for the indicated port
	mask = curr ^ PCintLast[intmaskport];
	PCintLast[intmaskport] = curr;

	// mask is pins that have changed. sceen out non pcint pins
	if ((mask &= *port_to_pcmask[intmaskport]) == 0) {
		return;
	}


	for (uint8_t i=0; i<8; ++i) {
		bit = 0x01 << i;
		if (bit & mask) {
			pin = intmaskport*8 + i;

			// checking change mode, only the satisfied condition will trigger
			// the handling function
			if ((PCintMode[pin] == CHANGE
					|| ((PCintMode[pin] == RISING) && (curr & bit))
					|| ((PCintMode[pin] == FALLING) && !(curr & bit)))
					&& (PCintFunc[pin] != NULL)) {
				PCintFunc[pin]();
			}
		}
	}
}
