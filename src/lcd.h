


void lcd_en_write(void);

void lcd_writeNibble(char);

void lcd_writeByte(char);

void lcd_writeCommand(char);

void lcd_writeData(char);

void lcd_init(void);

int lcd_putChar(char c, FILE *p);

void lcd_clear(void);

void lcd_locate(uint8_t, uint8_t);
