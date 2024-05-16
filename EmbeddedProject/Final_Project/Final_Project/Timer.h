#ifndef TIMER_H_
#define TIMER_H_

#define Number_Of_Overflows 62

void timer0_init(void);

void timer0_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */