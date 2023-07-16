#include "timer1.h"
#include "common_macros.h"
#include "gpio.h"
#include "avr/io.h"
#include <avr/interrupt.h>
static volatile void (*g_ptr)(void)  = NULL_PTR;
static volatile void (*g_ptr1)(void) = NULL_PTR;
static volatile void (*g_ptr2)(void) = NULL_PTR;
ISR(TIMER1_OVF_vect){
	if (g_ptr != NULL_PTR){
		(*g_ptr)();
	}
}
ISR(TIMER1_COMPA_vect){
	if (g_ptr != NULL_PTR){
		(*g_ptr)();
	}
}
ISR(TIMER1_COMPB_vect){
	if(g_ptr1 != NULL_PTR){
		(*g_ptr2)();
	}
}
ISR(TIMER1_CAPT_vect){
	if (g_ptr != NULL_PTR){
		(*g_ptr1)();
	}
}

void TIMER1_init(TIMER1_config* config)
{
	TCCR1A = (TCCR1A & 0X3F)  | ((config->oc1)<<6);
	TCCR1A = (TCCR1A & 0XCF)  | ((config->oc1b)<<4);
	TCCR1A = (TCCR1A & 0XFC)  | (config->mode & 0X03);
	TCCR1B = (TCCR1B & 0XE7)  | ((config->mode & 0X0C)<<1);
	TCCR1B = (TCCR1B & 0XF8)  | (config->clk);
	TIMSK = (TIMSK & 0XC3);
	if (config->mode == NORMAL_MODE || config->mode == CTC_ICR1)
	{
		TCCR1A = (TCCR1A & 0XF3)| (0X0C);

	}
	else if (config->mode == CTC_OCR1A_TOP)
	{
		TCCR1A = (TCCR1A & 0XF3)|(0X04);

	}
	else
	{
		TCCR1A = (TCCR1A & 0XF3);
	}


}
void TIMER1_setInterrupt(TIMER1_INTERRUPT_config* int_config)
{
	if (int_config->status == ENABLE){
		TIMSK = (TIMSK & 0XC3);
		SET_BIT(TIMSK,int_config->id);
	}
	else {
		TIMSK = (TIMSK & 0XC3);
		CLEAR_BIT(TIMSK,int_config->id);
	}
}
void TIMER1_setRegisters(TIMER1_REGISTERS* reg_values)
{
	TCNT1 = reg_values->Intial_value;
	OCR1A = reg_values->CompA_value;
	OCR1B = reg_values->CompB_value;
	ICR1  = reg_values->icr_value;
}
void TIMER1_setIcrEdge(const ICR_EDGE edge)
{
	TCCR1B = (TCCR1B & 0XBF) | (edge<<6);
}
uint16 TIMER1_getIcrReg(void)
{
	return ICR1;
}
void TIMER1_resetIntialValue(void)
{
	TCNT1 = 0;
}
void TIMER1_setCallBack(void(*a_ptr)(void),INTERRUPT_ID id)
{
	if (id == TIMER1_OVF ||  id == TIMER1_CTC_OCR1A )
	{
		g_ptr = a_ptr;
	}
	else if (id == TIMER1_ICR )
	{
		g_ptr1 = a_ptr;
	}
	else
	{
		g_ptr2 = a_ptr;
	}
}
void TIMER1_DeInitICU(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}

