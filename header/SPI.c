//MIGHT NEED THIS #include <avr/interrupt.h>
#include "bit.h"
void SPI_MasterInit(void){
	//SET DDRB to have MOSI, SCK, and SS as output and MISO as input
	//SS:PB4 MOSI: PB5 MISO: PB6 SCK: PB7
	DDRB = 0xBF; PORTB = 0x00;
	//Enable SPI, master set clock rate fck/16
	SPCR = (1<< SPE) | (1<<MSTR) | (1<< SPR0);
}

void SPI_MasterTransmit(unsigned char cData, unsigned char portSelect, unsigned int slaveSelectPin){
	//data in SPDR will be transmitted, e.g. SPDR = cData;
	SPDR = cData;
	//set SS low
	SetBit(portSelect,slaveSelectPin,0);
	while(!(SPSR & (1<<SPIF))){//wait for transmission to complete
		;
	}
	//set SS high
	SetBit(portSelect,slaveSelectPin,1);
}

void SPI_ServantInit(void){
	//set DDR to have MISO line as output and MOSI, SCK, and SS as input
	DDRB = 0x40; PORTB = 0x00;
	//set SPCR register to enable SPI and enable SPI interrupt (pg. 168)
	SPCR = (1<<SPE);
	//Enable global interrupts are enabled on SREG register (pg.9)
	sei();
}

ISR(SPI_STC_vect){
	//this is enabled in init with the SCPR register's "SPI Interrupt Enable"
	//SPDR contains the received data, e.g. unsigned char receivedData = SPDR;
	unsigned char receivedData = SPDR;
	return receivedData;
}