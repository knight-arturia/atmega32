// SPI communication

#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "lcd.h"

void SPI_Initialize(void);

void SPI_Transmission(uint8_t *dataBuffer, const uint8_t length);

uint8_t SPI_IsEnabled(void);
