#ifndef TIMER1_H_
#define TIMER1_H_
/*------------------------------------------------INCLUDES--------------------------------------------------------------------------*/
#include "std_types.h"
/*------------------------------------------------DEFINATIONS-----------------------------------------------------------------------*/
#define GlobalInterruptEnable()  SET_BIT(SREG,7)        /*MACRO TO SET I-BIT TO SET ON THE GLOBAL INTERRUPT*/
#define GlobalInterruptDisable() CLEAR_BIT(SREG,7)		/*MACRO TO CLEAR THE I-BIT */
/*------------------------------------------------ENUMS----------------------------------------------------------------------------*/
typedef enum                                         /*THIS ENUM TO CHOOSE THE PRESCALER FOR TIMER1*/
{
	NO_CLK , CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EX_CLK_FALLING,EX_CLK_RISING
}TIMER1_PRECALER;
/*----------------------------------------------------------*/
typedef enum 										/*THIS ENUM TO CHOOSE THE MODE OF TIMER1*/
{
	NORMAL_MODE,PWM_PHASE_8BIT,PWM_PHASE_9BIT,PWM_PHASE_10BIT,
	CTC_OCR1A_TOP,FAST_PWM_8BIT,FAST_PWM_9BIT,FAST_PWM_10BIT,
	PHASE_FREQ_ICR1,PHASE_FREQ_OCR1A,PHASE_CORRECT_ICR1A,PHASE_CORRECT_OCR1A,
	CTC_ICR1, RESERVED, FAST_PWM_ICR1, FAST_PWM_OCR1A
}TIMER1_MODES;
/*----------------------------------------------------------*/
typedef enum 	/*THIS ENUM TO SET THE MODE OF OC1A PIN*/
{
	OC1A_NORMAL,OC1A_TOGGLE,OC1A_NON_INVERTING,OC1A_INVERTING
}OC1A_MODE;
/*----------------------------------------------------------*/
typedef enum 	/*THIS ENUM TO SET THE MODE OF OC1B PIN */
{
	OC1B_NORMAL,OC1B_TOGGLE,OC1B_NON_INVERTING,OC1B_INVERTING
}OC1B_MODE;
/*----------------------------------------------------------*/
typedef enum 	/*ENUM TO SET THE PIN OF EACH INTERRUPT OF TIMER1 IN THE TIMSK REG*/
{
	TIMER1_OVF = 2 , TIMER1_CTC_OCR1B ,  TIMER1_CTC_OCR1A, TIMER1_ICR
}INTERRUPT_ID;
/*----------------------------------------------------------*/
typedef enum 	/*ENUM TO SET STATUS OF INTERRUPT */
{
	DISABLE,ENABLE
}INTERRUPT_STATUS;
/*----------------------------------------------------------*/
typedef enum 	/*ENUM TO SET THE EDGE THAT DETECTED BY ICU*/
{
	FALLING_EDGE,RISING_EDGE
}ICR_EDGE;
/*-------------------------------------------------------STRUCTURES----------------------------------------------------------------*/
typedef struct /*THIS STRUCTURE SET THE INTERRUPT CONFIGURATION WHICH IS THE INTERRUPT NAME AND THE STATUS*/
{
	INTERRUPT_ID id;
	INTERRUPT_STATUS status;
}TIMER1_INTERRUPT_config;
/*----------------------------------------------------------*/
typedef struct /*THIS STRUCTURES SET THE REGISTERS VALUES OF TIMER1*/
{
	uint16 Intial_value ;
	uint16 CompA_value  ;
	uint16 CompB_value  ;
	uint16 icr_value    ;
}TIMER1_REGISTERS;
/*----------------------------------------------------------*/
typedef struct /*THIS STRUCTURE SET THE CONFIGURATION OF TIMER1 LIKE MODE CLOCK AND OC1A,OC1B STATUS*/
{
	TIMER1_MODES    mode ;
	TIMER1_PRECALER clk;
	OC1A_MODE       oc1;
	OC1B_MODE       oc1b;
}TIMER1_config;
/*----------------------------------------------------------FUNCTIONS--------------------------------------------------------------*/
void TIMER1_init(TIMER1_config* config);
void TIMER1_setInterrupt(TIMER1_INTERRUPT_config* int_config);
void TIMER1_setRegisters(TIMER1_REGISTERS* reg_values);
void TIMER1_setIcrEdge(ICR_EDGE edge);
uint16 TIMER1_getIcrReg(void);
void TIMER1_resetIntialValue(void);
void TIMER1_setCallBack(void(*a_ptr)(void),INTERRUPT_ID id);
void TIMER1_DeInitICU(void);
#endif /* TIMER1_H_ */
