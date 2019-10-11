/*	Author: winson
 *  Partner(s) Name: Dylan han
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <../header/bit.h>
#include <../header/io.c>
#include <../header/keypad.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below */
    while (1) {
	PORTA = (GetKeypadKey() -'0');
    }
    return 1;
}
