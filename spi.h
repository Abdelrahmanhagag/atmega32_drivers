

#ifndef SPI_H_
#define SPI_H_
#include "std_types.h"
#define NULL_MSG     0XFF

void SPI_initMaster(void);
void SPI_initSlave(void);
uint8 SPI_sendReceiveByte(uint8 byte);
void SPI_sendString(uint8* string);
void SPI_receiveString(uint8* string);
#endif /* SPI_H_ */
