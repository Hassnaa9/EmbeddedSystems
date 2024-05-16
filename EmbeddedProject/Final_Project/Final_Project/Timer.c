#include "Timer.h"
#include "Registers.h"
#include "BIT_MATH.h"
//#include "std_types.h"
#include <avr/interrupt.h>
#define I_BIT 7

void (*g_callBackPtr)(void) = ((void*)0);

//Timer0 Interrupt service Routine
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != ((void*)0))
	{
		(*g_callBackPtr)();
	}
}

void timer0_init(void)
{
	TCNT0 = 0;   // timer initial value
	SET_BIT(TIMSK, TOIE0);  // enable overflow interrupt
		
	TCCR0 = (1 << FOC0) | (1 << CS02) | (1 << CS00);
	SET_BIT(SREG, I_BIT); //enable global interrupt
}

void timer0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
} 