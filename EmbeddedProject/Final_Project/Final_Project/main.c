#define F_CPU 16000000 
#include <util/delay.h>
#include "KeyPad.h"
#include "Seven_Segment.h"
#include "Timer.h"
#include "LCD.h"
#include "Registers.h"
#include "BIT_MATH.h"
//int g_tick = 0, numbers[100], pos = 0;
void bubbleSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int main(void)
{
	SEVEN_SEG_INIT();
	keypad_init();
	LCD_init();
	int index = 0, numbers[100];
    unsigned char str[4];  // Array Of Characters For The 4-Digit Numbers, Every Index Contains A Digit.
	int i = 0; // Index Used To Point On The Next Empty Place In "str".
	
	///////////////////////////////////// Getting The Input Via The KeyPad. /////////////////////////////////////
	
	LCD_string("ENTER NUMBER: ");
	
	while (1)
	{
		
		unsigned char value = keypad_get_value(); // Receiving A Character Via The KeyPad.
		
		if(value != invalid_char) // Checks If The Input Character Is Valid.
		{
			
			if(value == '=') { // If The Input Character Is '=' Then Stop Accepting Input And Go For Sorting And Displaying After break Statement.
				
				////// Just Confirming To Receive The Number On LCD  Before Breaking If The User Did Not Press C. //////
				
				if( i > 0) { // If The User Willed To Terminate The Input Process And The LCD Have Some Digits Still Not Confirmed, 
							 // This Condition Will Make Sure Confirming It.. So If The "i" Variable Has Some But Zero This Means There Is Characters 
							 // On The LCD.
							 
					if(i < 4) str[i] = '\0'; // Making Sure That The Null Terminator After the Last Digit.. 
											 // This Made To Avoid The Converting From Array Of Characters To Integer value Problems.
											 
					numbers[index ++] = atoi(str); // Convert From Array Of Characters To Integer Value And Store The Integer Value Into The Proper Place.  
 				}
				///////////////////////////////////////////////////// End Of Confirming. //////////////////////////////
				LCD_clear(); // Clearing The LCD To Be Ready To Show The New Number.
				
				break; // End Of Entering Numbers.
			}
			else if(value == 'C' /*|| i == 4*/) {// If The Input Character Is 'C', Then Confirm The Number And Make The LCD Ready To Receive New values.
				
				if(i < 4) 
					str[i] = '\0';
			
				numbers[index ++] = atoi(str);
				i = 0;  // You Know Why.
				
				LCD_clear();
				LCD_string("ENTER NUMBER: ");
			}
			else {
				str[i] = value; i ++; // Receiving The New Numbers' Digits.
				
				LCD_writeChar(value); // Write The Digit On The LCD.
			}
		}
	}
	/////////////////////// If You Reached Here, That Means You Stopped Entering Numbers And Ready To See Them In Sorted Manner... ///////////////////////
	
	
	bubbleSort(numbers, index); // Sorting...
	
	LCD_string("In SORTED Manner: ");
	_delay_ms(500);
	LCD_clear();
	////////////////////////////// Show The Sorted Array  On LCD. //////////////////////////////
	for (int i = 0; i < index; i ++) {
		unsigned char s[4];  //Array Of Characters To Store The Converted Number Into String Into. 
		itoa(numbers[i], s, 10); // Function Take Integer Value And Array Of Characters And Numbering Base 
								 // And Some How Return The Number As Array Of Characters.
		LCD_string(s); // Showing The Number On The LCD.
		
		if(i != index - 1)
			LCD_string(", ");
		if(i == index - 1)
			LCD_writeChar('.');
		_delay_ms(300);
	}
	
	
	// Displaying The Numbers On 7SEG.
	for (int i = 0; i < index; i ++)
	{
		display_number(numbers[i]);
		CLEAR_SEV_SEG();
	}
}
