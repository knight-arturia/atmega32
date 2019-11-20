

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include <inttypes.h>
#include "timer2.h"
#include "stdio.h"

void lcd_en_write(void);

void lcd_writeNibble(char c);

void lcd_writeByte(char c);

void lcd_writeCommand(char command);

void lcd_writeData(char data);

void lcd_init(void);

int lcd_putChar(char c, FILE *p);

void lcd_clear(void);
