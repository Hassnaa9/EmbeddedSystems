


#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "Registers.h"
#include "BIT_MATH.h"
#define F_CPU 16000000 
#include <util/delay.h>

#define invalid_char 0xff

void keypad_init(void);
unsigned char keypad_get_value(void);

#endif /* KEYPAD_H_ */