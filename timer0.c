#include "timer0.h"
#include "common_macros.h"
#include "GPIO_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void (*TIMER0_COMPARE_INTERRUPT_PTR)(void) = NULL_PTR;
ISR(TIMER0_COMP_vect){
	if(TIMER0_COMPARE_INTERRUPT_PTR != NULL_PTR){
		(*TIMER0_COMPARE_INTERRUPT_PTR)();
	}
}
ISR(TIMER0_OVF_vect){
	if(TIMER0_COMPARE_INTERRUPT_PTR != NULL_PTR){
		(*TIMER0_COMPARE_INTERRUPT_PTR)();
	}
}

void TIMER0_init(Timer0_config* config)
{

	switch(config->mode){
	case NORMAL_MODE :
		TIMER0_CONTROL_REG = (TIMER0_CONTROL_REG & 0X37);
		CLEAR_BIT (TIMER0_CONTROL_REG ,3);
		CLEAR_BIT (TIMER0_CONTROL_REG ,6);
		SET_BIT(TIMER0_CONTROL_REG ,7);
		break;
	case PHASE_CORRECT:
		TIMER0_CONTROL_REG = (TIMER0_CONTROL_REG & 0X37);
		CLEAR_BIT(TIMER0_CONTROL_REG ,3);
		SET_BIT(TIMER0_CONTROL_REG ,7);
		SET_BIT(TIMER0_CONTROL_REG ,6);
		break;
	case COMPARE_MODE :
		TIMER0_CONTROL_REG  =  (TIMER0_CONTROL_REG & 0X37);
		CLEAR_BIT (TIMER0_CONTROL_REG ,6);
		SET_BIT(TIMER0_CONTROL_REG ,3);
		SET_BIT(TIMER0_CONTROL_REG ,7);
		break;
	case FAST_PWM_MODE :
		TIMER0_CONTROL_REG = (TIMER0_CONTROL_REG & 0X37);
		SET_BIT(TIMER0_CONTROL_REG ,6);
		SET_BIT(TIMER0_CONTROL_REG ,3);
		CLEAR_BIT(TIMER0_CONTROL_REG ,7);
		break;

	}

	TIMER0_CONTROL_REG   = ((TIMER0_CONTROL_REG & 0XF8)  | (config->prescaler))| ((TIMER0_CONTROL_REG & 0XCF)  | ((config->oc0_mode)<<4));
	TIMER0_INTERUPT_REG   =  (TIMER0_INTERUPT_REG & 0XFC) | (config->interupt_state);
}

void TIMER0_setControlReg(uint8 value)
{
	OCR0 = value ;
}
void TIMER0_setCallBack(void(*a_ptr)(void))
{
	TIMER0_COMPARE_INTERRUPT_PTR = a_ptr;
}
void TIMER0_configOcPin(void)
{
	GPIO_setupPinDirection(PORTB_ID, BIT3_ID, PIN_OUTPUT);
}
void TIMER0_setIntialReg(uint8 value){
	TCNT0 = value ;
}
uint8 TIMER0_getTCCVALUE(void){
	uint8 value = TCCR0;
	return value ;
}
void TIMER0_Deinit(void)
{
	TIMER0_CONTROL_REG  = 0;
	TIMER0_INTIAL_REG   = 0;
	TIMER0_INTERUPT_REG = 0;
	TIMER0_CONTROL_REG  = 0;
}

