
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom32.h>

#include "avr_base.h"

void transceiver_initialize(void);

void clear_flag(void);

_Bool trans_get_flag(void);
