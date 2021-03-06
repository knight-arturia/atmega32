// Set of the lcd screen

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>
#include <stdio.h>

#include "timer2.h"
#include "lcd.h"

void lcd_en_write(void){
	PORTB |= 1 << PB0;
	timer2_wait(1);
	PORTB &= ~(1 << PB0);
	timer2_wait(1);

}

void lcd_writeNibble(char c){
	timer2_wait(5);
	PORTA &= 0x0f;			// clear the upper 4 bits
	PORTA |= c & 0xf0;		// write the upper 4 bits
	lcd_en_write();
}

void lcd_writeByte(char c){
	timer2_wait(5);
	PORTA &= 0x0f;
	PORTA |= c & 0xf0;		// clear PORTA and write the upper 4 bits of c
	lcd_en_write();			// show  data
	c = c << 4;				// move the lower 4 bits to the upper bits
	PORTA &= 0x0f;
	PORTA |= c & 0xf0;		// clear PORTA and write the lower 4 bits of c
	lcd_en_write();			// show data

}

void lcd_writeCommand(char command){
	timer2_wait(5);
	PORTD &= ~(1 << PD7);	// set RS = 0, command register
	lcd_writeByte(command); // use the function lcd_writeByte to write command into PORTA
}

void lcd_writeData(char data){
	timer2_wait(5);
	PORTD |= 1 << PD7;		// set RS = 1, data register
	lcd_writeByte(data); 	// use the function lcd_writeByte to write data into PORTA
}

void lcd_init(void){
	timer2_wait(50);
	DDRD |= 1 << PD7;		// set RS as output
	DDRB |= (1 << PB1) | (1 << PB0) ;	// set RW and E as output
	DDRA |= ((1 << PA4) | (1 << PA5) | (1 << PA6) | (1 << PA7));
							// set PA4~7 set as output
	PORTD &= ~(1 << PD7);	// set RS = 0, command register
	fdevopen(lcd_putChar, NULL);
	lcd_writeNibble(0x30); 	// write 0x3 to command register, 8-Bit modus schalten
		timer2_wait(5);
	lcd_writeNibble(0x30);
		timer2_wait(5);
	lcd_writeNibble(0x30);
		timer2_wait(5);
	lcd_writeNibble(0x20);	// write 0x2 to command register, 4-Bit modus schalten
		timer2_wait(5);
	lcd_writeCommand(0x28);	// Display choose
		timer2_wait(5);
	lcd_writeCommand(0x0f); // Display active
		timer2_wait(5);
	lcd_clear();	// Clear Display
		timer2_wait(5);
}

int i = 0;	// number of output char

int lcd_putChar(char c, FILE *p){
	if(i < 16){
		lcd_locate(0, i);
		}
	else if(i >= 16 && i < 32)
		lcd_locate(1 , i - 16);
	i++;
	if (i > 32) {
		i = 0;
		lcd_locate(0, i);
	}
	switch(c){
				case 'ä' : lcd_writeData(0xe1);	// write data 0b11100001
				break;
				case 'ö' : lcd_writeData(0xef);	// write data 0b11101111
				break;
				case 'ü' : lcd_writeData(0xf5);	// write data 0b11110101
				break;
				case 'ß' : lcd_writeData(0xe2);	// write data 0b11100010
				break;
				default : lcd_writeData(c);
			}

	return 0;
}

void lcd_locate(uint8_t row, uint8_t col){
	uint8_t address;
	if(row == 0) {
		address = 0x80 + col;	// locate at first row
		i= col;
	}
	else {
		address = 0xc0 + col;	// locate at second row
		i= 16 + col;
	}
	lcd_writeCommand(address);	// write the position to DDRAM
}

void lcd_clear(void){
	i = 0;
	lcd_locate(0,0);
	lcd_writeCommand(0x01);
}
