// SPI communication

#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "lcd.h"

void SPI_Initialize(void);

void SPI_Transmission(char *dataBuffer, const uint8_t length);

_Bool SPI_IsEnabled(void);
