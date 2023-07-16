#include "adc.h"
#include "Common_Macros.h"
#include<avr/io.h>

void ADC_init(const ADC_configType* config_ptr){
	ADMUX = config_ptr->mode;
	SET_BIT(ADCSRA,ADEN);
	CLEAR_BIT(ADCSRA,ADIE);
	ADCSRA |= config_ptr->division_factor;



}
uint16 ADC_readChannel(uint8 channel){
	ADMUX = (ADMUX & 0XE0) | (channel);
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){

	}
	SET_BIT(ADCSRA,ADIF);
	return ADC;


}


