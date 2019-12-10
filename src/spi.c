// SPI communication

#include "spi.h"

#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define MOSI PB5
#define MISO PB6
#define SCK PB7
#define _SS PB4

uint8_t init_flag = 0;

void SPI_Initialize(void){
	DDR_SPI |= (1 << MOSI) | (1 << _SS) | 1 << SCK;	// set MOSI, SCK and _SS as output
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0) | ( 1 << SPR1);	// set SPI enable, master select, SCK frequency is f/128
	PORT_SPI &= ~(1 << _SS);	// _SS is driven low
	DDR_SPI &= ~(1 << MISO);	// set MISO as input
	init_flag = 1;
}

void SPI_Transmission(uint8_t *dataBuffer, const uint8_t length){
	int i = 0;
	while(i < length){
		SPDR = dataBuffer[i];
		while (! (SPSR & (1 << SPIF)));
		//printf("%c", SPDR);
		dataBuffer[i] = SPDR;
		i++;
	}
}

uint8_t SPI_IsEnabled(void){
	return init_flag;
}

