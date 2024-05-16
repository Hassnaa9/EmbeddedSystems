

#ifndef LCD_H_
#define LCD_H_
// 
// #define F_CPU 8000000 
 #define F_CPU 16000000
#include <util/delay.h>
#include "Registers.h"
#include "BIT_MATH.h"


#define  LCD_Data_DDR DDRB
#define  LCD_Command_DDR DDRA

#define  LCD_Data_PORT PORTB
#define  LCD_Command_PORT PORTA

#define RS 3
#define E  2


void LCD_init(void);

void LCD_command(unsigned char cmd);

void LCD_writeChar(unsigned char chr);

void LCD_string(unsigned char* str);

void LCD_clear(void);




#endif /* LCD_H_ */