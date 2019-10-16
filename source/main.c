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

unsigned char* patternSelect(unsigned char keypadInput){
 	keypadInput = GetKeypadKey();
	if(keypadInput == 'A'){
		return "Ptrn: 1";
	}
	else if(keypadInput == 'B'){
		return "Ptrn: 2";
	}
	else if(keypadInput == 'C'){
		return "Ptrn: 3";
	}
	else if(keypadInput == 'D'){
		return "Ptrn: 4";
	}
	else{
		return "Ptrn: 0";
	}
}

unsigned char* speedSelect(unsigned char keypadInput){
	if(keypadInput == '1'){
		return "Spd: 1";
	}
	else if(keypadInput == '2'){
		return "Spd: 2";
	}
	else if(keypadInput == '3'){
		return "Spd: 3";
	}
	else if (keypadInput == '4'){
		return "Spd: 4";
	}
	else{
		return "Spd: 0";
	}
}

unsigned char* slaveSelect(unsigned char keypadInput){
	if(keypadInput == '7'){
		return "uC: 1";
	}
	else if(keypadInput == '8'){
		return "uC: 2";
	}
	else if(keypadInput == '9'){
		return "uC: 3";
	}
	else{
		return "uC: 0";
	}
}

void CustomLCD_DisplayString( unsigned char column, const unsigned char* string) {//No Clear Screen                       
   unsigned char c = column;                                                                          
   while(*string) {
      LCD_Cursor(c++);
      LCD_WriteData(*string++);                                                                       
   }                                                                                                  
}   
unsigned char tempA = 0x00;
unsigned char* currentPattern = "Ptrn: 0";
unsigned char* currentSpeed = "Spd: 0";
unsigned char* currentSlave = "uC: 0";
unsigned char keypadInput = 0x00;
unsigned char cData = 0x00;
unsigned int slave = 0;
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xF0; PORTA = 0x0F;
	DDRC = 0xFF; PORTC = 0x00; //OUTPUTS
	DDRD = 0xFF; PORTD = 0x00; //OUTPUTS;
    /* Insert your solution below */
   
	LCD_init();
	LCD_ClearScreen();
	SPI_MasterInit();
	TimerOn();
	TimerSet(100);
	CustomLCD_DisplayString(1,currentPattern);
	CustomLCD_DisplayString(10,currentSpeed);
	CustomLCD_DisplayString(17,currentSlave);
    	while (1) {
		
		tempA = PINA;
		keypadInput = GetKeypadKey();
		if(keypadInput != '\0'){
			//update screen and send signal
			if(keypadInput == 'A' || keypadInput == 'B' || keypadInput  == 'C' || keypadInput == 'D'){
				currentPattern = patternSelect(keypadInput);
				CustomLCD_DisplayString(1,currentPattern);
				if(slave != 0){
					LCD_DisplayString(1,"Transmitting");
					SPI_MasterTransmit(0xFF);
					LCD_DisplayString(1,"Done");			
				}
			}
			else if(keypadInput == '1' || keypadInput == '2' || keypadInput == '3' || keypadInput == '4'){
				currentSpeed = speedSelect(keypadInput);
				CustomLCD_DisplayString(10,currentSpeed);
				if(slave != 0){
					SPI_MasterTransmit(0xFF);
				}
			}
			else if(keypadInput == '7' || keypadInput == '8' || keypadInput == '9'){
				currentSlave = slaveSelect(keypadInput);
				CustomLCD_DisplayString(17,currentSlave);
				if(keypadInput == '7'){
					slave = 1;
				}
				if(keypadInput == '8'){
					slave = 2;
				}
				if(keypadInput == '9'){
					slave = 3;
				}
			}
			else{//invalid key don't update screen
				break;
			}
		}
		//LCD_Cursor(1);
		//LCD_WriteData(GetKeypadKey());
		while(!TimerFlag);
		TimerFlag = 0;
	
    	}
    	return 1;
}
