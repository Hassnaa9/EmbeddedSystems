#include "Seven_Segment.h"
#define F_CPU 16000000 
#include <util/delay.h>
#include "Registers.h"
#include "BIT_MATH.h"
/*#include "std_types.h"*/

void SEVEN_SEG_INIT(void)
{
	SET_BIT(DDRA,2); //enable the second seven segment 

    SET_BIT(DDRA,3);
   // SET_BIT(PORTA,3);	
	SET_BIT(DDRB,5);
	SET_BIT(DDRB,6);
	PORTB &= 0b11101000;
	
	SET_BIT(DDRB,0);
	SET_BIT(DDRB,1);
	SET_BIT(DDRB,2);
	SET_BIT(DDRB,4);
	
	
	
}

void SEVEN_SEG_Display(int num)
{
	PORTB&= 0b11101000;
	PORTB = (((num & 0b00001000) << 1) | (num & 0b00000111));
}

void display_number(int number)
{
	int digit4 = ( number / 1000) % 10;//100    =0
	int digit3 = ( number / 100) % 10;//100
	int digit2 = ( number / 10) % 10;
	int digit1 =  (number/ 1 ) % 10;

	// Display the digits on the four-digit seven-segment display
	unsigned int start_time = 0;
	while (start_time < 500) // Delay for 1 seconds
	{

		SEVEN_SEG_Display(digit4);
		_delay_ms(2);
		TOGGLE_BIT(PORTB,6);
		SEVEN_SEG_Display(digit3);
		_delay_ms(2);
		TOGGLE_BIT(PORTB,5);
		SEVEN_SEG_Display(digit2);
		_delay_ms(2);
		TOGGLE_BIT(PORTA,2);
		SEVEN_SEG_Display(digit1);
		_delay_ms(2);
		TOGGLE_BIT(PORTA,3);

		start_time += 5;


	}
}
void CLEAR_SEV_SEG()
{
	SET_BIT(PORTB,6);
	SET_BIT(PORTB,5);
	SET_BIT(PORTA,2);
	SET_BIT(PORTA,3);

}
