#include "EXT_INT.h"
#include "Registers.h"
#include "BIT_MATH.h"
#include <avr/interrupt.h>

// Global variable to hold the address of the callback function in the application
void (*g_callBackPtr)(void)=((void*)0);

// External ITR1 Interrupt service Routine
ISR(INT1_vect)
{
	if(g_callBackPtr != ((void*)0))
	{
		(*g_callBackPtr)();
	}
}

void INT1_init(void)
{
	CLR_BIT(SREG,7);          // disable global interrupt
	CLR_BIT(DDRD,3);          // configure INT1/PD3 as input pin
	SET_BIT(PORTD,3);         // enable pull up
	SET_BIT(GICR,7);          // enable external interrupt pin INT1
	SET_BIT(MCUCR,3);         //  Trigger INT1 with the falling edge
	CLR_BIT(MCUCR,2);
	SET_BIT(SREG,7);         // enable global interrupt
} 

void INT1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}