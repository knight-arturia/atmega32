
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>

#include "avr_base.h"
#include "encoder.h"
#include "timer2.h"
#include "lcd.h"
#include "led.h"
#include "rfm69c.h"

void transceiver_init(void);

void transceiver_entryMode(void);

void transceiver_run(uint8_t);

void transceiver_receiveMsg(void);

void transceiver_sendMsg(uint8_t);

void transceiver_sendFinish(void);

void switch_to_receiveMode(void);

_Bool transceiver_get_flag(void);

_Bool transceiver_input_msg(void);

void transceiver_clear(void);

void clear_flag(void);

char* transceiver_get_msg(void);
