#include"spi.h"
#include"gpio.h"
#include<avr/io.h>
#include"common_macros.h"
void SPI_initMaster(void){
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);
	/*SETUP SPI REGISTER*/
	SPCR=(1<<SPE)|(1<<MSTR);
	SPSR &= ~(1<<SPI2X);
}
void SPI_initSlave(void){
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_INPUT);
	/*SETUP SPI REGISTER*/
	SPCR=(1<<SPE);
	SPSR &= ~(1<<SPI2X);
}
uint8 SPI_sendReceiveByte(uint8 byte){
	SPDR=byte;
	while(BIT_IS_CLEAR(SPSR,SPIF));
	return SPDR;

}
void SPI_sendString(uint8* string){
	uint8 i;
	for(i = 0 ;string[i] != '\0'; i++)
	{
		SPI_sendReceiveByte(string[i]);
	}
	SPI_sendReceiveByte('#');
}
void SPI_receiveString(uint8* string){
	uint8 i ;
	for (i = 0 ;string[i] != '#'; i++){
		string[i] = SPI_sendReceiveByte(NULL_MSG);
	}
	string[i] = '\0';
}
