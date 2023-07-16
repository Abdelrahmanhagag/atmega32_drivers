
#ifndef EX_INT_H_
#define EX_INT_H_
#include "std_types.h"

#define INT_Enable_reg      GICR
#define INT0_Enable_Bit      6
#define INT1_Enable_Bit      7
#define INT2_Enable_Bit      5
#define Global_Interrupt_Enable() (SET_BIT(SREG,7))
#define Global_Interrupt_Disable() (CLEAR_BIT(SREG,7))




typedef enum{
	LOW_LEVEL,LOGICAL_CHANGE,FALLING_EDGE,RISING_EDGE
}Edge_Detected;
typedef enum {
	INT_0,INT_1,INT_2
}INT_Num;
typedef struct {
	INT_Num  id ;
	Edge_Detected edge;
}INT_Config;


void INT_init(INT_Config* config);
void INT_DeInit(INT_Config* config);
void INT_setCallBack(void (*a_ptr)(void),INT_Num int_id);
#endif /* EX_INT_H_ */
