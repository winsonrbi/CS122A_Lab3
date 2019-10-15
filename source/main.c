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
#include <../header/SPI.c>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempA = 0x00;
unsigned char cData = 0x00;
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00; //SLAVE SELECT ON MASTER uC
	DDRC = 0xFF; PORTC = 0x00; //OUTPUTS
	DDRD = 0xFF; PORTD = 0x00; //OUTPUTS;
    /* Insert your solution below */
   
	LCD_init();
	LCD_ClearScreen();
	SPI_ServantInit();
	TimerOn();
	TimerSet(100);
    	while (1) {
		
		if(receivedData == 0x00){
			tempA = 0x00;
		}
		else{
			tempA = 0x01;
		}
		PORTA = tempA;
		while(!TimerFlag);
		TimerFlag = 0;
	
    	}
    	return 1;
}
