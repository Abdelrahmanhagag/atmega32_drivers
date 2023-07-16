#ifndef TIMER0_H_
#define TIMER0_H_
#include "std_types.h"
#define TIMER0_CONTROL_REG       TCCR0
#define TIMER0_INTIAL_REG        TCNT0
#define TIMER0_CONTROL_COMPARE_REG       OCR0
#define TIMER0_INTERUPT_REG      TIMSK
#define GlobalInterruptEnable()  SET_BIT(SREG,7)
#define GlobalInterruptDisable() CLEAR_BIT(SREG,7)
typedef enum
{
	NORMAL_MODE   ,
	PHASE_CORRECT ,
	COMPARE_MODE  ,
	FAST_PWM_MODE
}TIMER0_MODE;

typedef enum
{
	NO_CLK , CLK_1,CLK_8,CLK_64,CLK_256,CLK_1024,EX_CLK_FALLING,EX_CLK_RISING
}TIMER0_PRECALER;
typedef enum
{
	INTERUPT_DISABLE            ,
	ENABLE_INTERUPT_NORMAL_MODE ,
	ENABLE_INTERUPT_COMPARE_MODE
}TIMER0_INTERUPT;
typedef enum
{
	NORMAL_PIN        ,
	TOGGLE_PIN        ,
	NON_INVERTING_PIN ,
	INVERTING_PIN
}COMPARE_MATCH_MODE ;

typedef struct {
	TIMER0_MODE         mode ;
	TIMER0_PRECALER     prescaler;
	TIMER0_INTERUPT     interupt_state;
	COMPARE_MATCH_MODE  oc0_mode;
}Timer0_config;

void TIMER0_init(Timer0_config* config);
void TIMER0_setControlReg(uint8 value);
void TIMER0_setIntialReg(uint8 value);
void TIMER0_configOcPin(void);
void TIMER0_setCallBack(void(*a_ptr)(void));
void TIMER0_Deinit(void);
uint8 TIMER0_getTCCVALUE(void);

#endif /* TIMER0_H_ */
