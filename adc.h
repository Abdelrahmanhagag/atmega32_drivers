

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*--------------------------------------DEFINATIONS--------------------------------------------*/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
/*-------------------------------------DEFINATIONS---------------------------------------------*/
/*THIS ENUM WILL BE PRESENTED AS THE MODES CONFIGURATION FOR ADC ABOUT VOLT MODES */
typedef enum {
	ADC_AREF,ADC_AVCC=0x40,ADC_INTERNAL_2_56_VOLT = 0xC0
}ADC_modes;
/*ENUM TO DETERMINATE THE PRESCALER FOR THE ADC*/
typedef enum {
	DIVISION_FACTOR_1,DIVISION_FACTOR_2,DIVISION_FACTOR_4,DIVISION_FACTOR_8,DIVISION_FACTOR_16,
	DIVISION_FACTOR_32,DIVISION_FACTOR_64,DIVISION_FACTOR_128
}ADC_Prescaler;
/*---------------------------------------STRUCTURES--------------------------------------------*/
typedef struct {
	ADC_modes mode ;
	ADC_Prescaler division_factor;
}ADC_configType;
/*---------------------------------------FUNCTIONS PROTOTYPES----------------------------------*/
uint16 ADC_readChannel(uint8 channel);
void ADC_init(const ADC_configType* config_ptr);


#endif /* ADC_H_ */
