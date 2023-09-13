/*
 * UART_private.h
 *
 *  Created on: Aug 30, 2023
 *      Author: TEAM
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR       *((volatile u8*)0x2C)
#define UCSRA     *((volatile u8*)0x2B)
#define UCSRB     *((volatile u8*)0x2A)
#define UCSRC     *((volatile u8*)0x40)
#define UBRRL     *((volatile u8*)0x29)

#define MPCM    0
#define U2X     1
#define PE      2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSZ0   1
#define UCSZ1   2
#define UCSZL   7

#define RXEN    4
#define TXEN    3

#define URSEL   7

#endif /* UART_PRIVATE_H_ */
