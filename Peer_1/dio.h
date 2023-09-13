/*
 * module name:			DIO (Digital Input Output)
 * file name:			dio.h
 * file description:	this file contains the prototypes of the module functions
 * version:				v01
 * date:				17/8/2023
 * author:				Ahmed Rezk
 */

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"

/* register definition */
#define PORTA	(*(volatile u8*)0x3B)	/* */
#define DDRA	(*(volatile u8*)0x3A)
#define PINA	(*(volatile u8*)0x39)

#define PORTB	(*(volatile u8*)0x38)
#define DDRB	(*(volatile u8*)0x37)
#define PINB	(*(volatile u8*)0x36)

#define PORTC	(*(volatile u8*)0x35)
#define DDRC	(*(volatile u8*)0x34)
#define PINC	(*(volatile u8*)0x33)

#define PORTD	(*(volatile u8*)0x32)
#define DDRD	(*(volatile u8*)0x31)
#define PIND	(*(volatile u8*)0x30)


#define OUTPUT (u8)1
#define INPUT (u8)0
#define INPULL (u8)11

#define PORT_A	(u8)'A'
#define PORT_B	(u8)'B'
#define PORT_C	(u8)'C'
#define PORT_D	(u8)'D'

#define LOW		(u8)0
#define HIGH	(u8)1




void MDIO_vidSetPinDirection(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8 cpy_u8PinDirection);
void MDIO_vidSetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8 cpy_u8PinValue);
void MDIO_vidGetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8* buf_u8PinValue);

/*
 * set port direction
 * set port value
 * get port value
 * */
void MDIO_vidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8PortDirection);
void MDIO_vidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8PortValue);
void MDIO_vidGetPortValue(u8 cpy_u8PortNumber, u8* buf_u8PortValue);

#endif /* DIO_H_ */
