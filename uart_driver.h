

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_
#include "std_types.h"
#define BAUD_RATE      9600
#define F_CPU          16000000
void UART_init(void);
void UART_sendByte(const uint8 data);
uint8 UART_recieveByte(void);
void UART_sendString(uint8* string);
void UART_receiveString(uint8* string);
#endif /* UART_DRIVER_H_ */
