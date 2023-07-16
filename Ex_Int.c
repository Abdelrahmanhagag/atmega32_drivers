#include "Ex_Int.h"
#include "common_macros.h"
#include "Gpio_driver.h"
#include <avr/interrupt.h>
static volatile void(*g_ptr0)(void) = NULL_PTR;
static volatile void(*g_ptr1)(void) = NULL_PTR;
static volatile void(*g_ptr2)(void) = NULL_PTR;
ISR(INT0_vect)
{
	if (g_ptr0 != NULL_PTR)
	{
		(*g_ptr0)();
	}
}
ISR(INT1_vect)
{
	if (g_ptr1 != NULL_PTR)
	{
		(*g_ptr1)();
	}
}
ISR(INT2_vect)
{
	if (g_ptr2 != NULL_PTR)
	{
		(*g_ptr2)();
	}
}
void INT_init(INT_Config* config)
{
	switch(config->id)
	{
	case INT_0:
		GPIO_setupPinDirection(PORTD_ID,BIT2_ID,PIN_INPUT);
		SET_BIT(INT_Enable_reg,INT0_Enable_Bit);
		MCUCR = (MCUCR & 0XFC) | (config->edge);
		break;
	case INT_1:
		GPIO_setupPinDirection(PORTD_ID,BIT3_ID,PIN_INPUT);
		SET_BIT(INT_Enable_reg,INT1_Enable_Bit);
		MCUCR = (MCUCR & 0XF3) | ((config->edge)<<2);
		break;
	case INT_2:
		GPIO_setupPinDirection(PORTB_ID,BIT2_ID,PIN_INPUT);
		SET_BIT(INT_Enable_reg,INT1_Enable_Bit);
		if(config->edge == LOW_LEVEL || config->edge == LOGICAL_CHANGE )
		{
			/*DO NOTHING*/
		}
		else if (config->edge == FALLING_EDGE)
		{
			CLEAR_BIT(MCUCSR,ISC2);
		}
		else if (config->edge == RISING_EDGE)
		{
			SET_BIT(MCUCSR,ISC2);
		}
		break;

	}
}
void INT_DeInit(INT_Config* config)
{
	switch(config->id)
	{
	case INT_0:
		CLEAR_BIT(INT_Enable_reg,INT0_Enable_Bit);
		break;
	case INT_1:
		CLEAR_BIT(INT_Enable_reg,INT1_Enable_Bit);
		break;
	case INT_2:
		CLEAR_BIT(INT_Enable_reg,INT2_Enable_Bit);
		break;
	}
}
void INT_setCallBack(void(*a_ptr)(void),INT_Num int_id)
{
	switch(int_id){
	case INT_0:
		g_ptr0 = a_ptr;
		break;
	case INT_1:
		g_ptr1 = a_ptr;
		break;
	case INT_2:
		g_ptr2 = a_ptr;
		break;
	}
}
