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
#include <../header/timer.h>
#include <../header/bit.h>
#include <../header/io.c>
#include <../header/keypad.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempA = 0x00;
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xF0; PORTA = 0x0F;
	DDRC = 0xFF; PORTC = 0x00; //OUTPUTS
	DDRD = 0xFF; PORTD = 0x00; //OUTPUTS;
    /* Insert your solution below */
   
	LCD_init();
	LCD_ClearScreen();
	LCD_DisplayString(1,"Test");
	TimerOn();
	TimerSet(100);
    	while (1) {
		tempA = PINA;
		//LCD_Cursor(1);
		//LCD_WriteData(GetKeypadKey());
		while(!TimerFlag);
		TimerFlag = 0;
	
    	}
    	return 1;
}
