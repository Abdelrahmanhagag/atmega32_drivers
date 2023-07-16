#include "uart_driver.h"
#include "common_macros.h"
#include "avr/io.h"
#include "std_types.h"

void UART_init(void)
{
	uint16 ubr_value ;
	ubr_value = ((uint32)F_CPU/(8*BAUD_RATE))-1;
#if (ubr_value < 0)
#error "this baud rate can not be defined with this system frequency"
#endif
	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN)  | (1<<TXEN);
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRL =  ubr_value;
	UBRRH = (ubr_value>>8);

}
void UART_sendByte(const uint8 data){
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data ;
}
uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;
}
void UART_sendString(uint8* string)
{
	uint8 i = 0;
	for(i = 0; string[i] != '\0';i++){
		UART_sendByte(string[i]);
	}
	UART_sendByte('#');
}
void UART_receiveString(uint8* string)
{
	uint8 i = 0;
	for (i=0;string[i] != '#';i++){
		string[i] = UART_recieveByte();
	}
	string[i] = '\0';
}


