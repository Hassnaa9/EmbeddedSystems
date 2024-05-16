#include "LCD.h"



void LCD_init(void)
{
	SET_BIT(LCD_Command_DDR, 3);
	SET_BIT(LCD_Command_DDR, 2);
	
	SET_BIT(LCD_Data_DDR, 0);
	SET_BIT(LCD_Data_DDR, 1);
	SET_BIT(LCD_Data_DDR, 2);
	SET_BIT(LCD_Data_DDR, 4);
	
	_delay_ms(15); 
	LCD_command(0x02);
	LCD_command(0x28);
	
	LCD_command(0x0c); // Dispaly on, cursor off
	LCD_command(0x01); // Clear the display screen
	LCD_command(0x80); //Force the cursor to the beginning of the 1st line
}

void LCD_command(unsigned char cmd)
{
	CLR_BIT(LCD_Command_PORT, RS); // Clearing RS ->  Write to command register
	
	LCD_Data_PORT &= 0b11101000;
	unsigned char high = ((cmd & 0xf0) >> 4);
	unsigned char tmp  = (((high & 0b00001000) << 1) | (high & 0b00000111));
	LCD_Data_PORT |= tmp;
	CLR_BIT(LCD_Command_PORT, E);
	SET_BIT(LCD_Command_PORT, E);
	_delay_ms(1);
	CLR_BIT(LCD_Command_PORT, E);
	
	
	LCD_Data_PORT &= 0b11101000;
	unsigned char low = (cmd & 0x0f);
	unsigned char tmp2  = (((low & 0b00001000) << 1) | (low & 0b00000111));
	LCD_Data_PORT |= tmp2;
	CLR_BIT(LCD_Command_PORT, 2);
	SET_BIT(LCD_Command_PORT, 2);
	_delay_ms(1); 
	CLR_BIT(LCD_Command_PORT, 2);
	
	_delay_ms(5);
}

void LCD_writeChar(unsigned char chr)
{
	SET_BIT(LCD_Command_PORT, 3); // Setting RS ->  Write to Data register
	
	LCD_Data_PORT &= 0b11101000;
	unsigned char high = ((chr & 0xf0) >> 4);
	unsigned char tmp  = (((high & 0b00001000) << 1) | (high & 0b00000111));
	LCD_Data_PORT |= tmp;
	CLR_BIT(LCD_Command_PORT, 2);
	SET_BIT(LCD_Command_PORT, 2);
	_delay_ms(1);
	CLR_BIT(LCD_Command_PORT, 2);
	
	
	LCD_Data_PORT &= 0b11101000;
	unsigned char low = (chr & 0x0f);
	unsigned char tmp2  = (((low & 0b00001000) << 1) | (low & 0b00000111));
	LCD_Data_PORT |= tmp2;
	CLR_BIT(LCD_Command_PORT, 2);
	SET_BIT(LCD_Command_PORT, 2);
	_delay_ms(1);
	CLR_BIT(LCD_Command_PORT, 2);
	
	_delay_ms(5);
}

void LCD_string(unsigned char* str)
{
	for(int i = 0; str[i] != '\0'; i ++) {
		LCD_writeChar(str[i]);
	}
}

void LCD_clear(void)
{
	LCD_command(0x01);
}
