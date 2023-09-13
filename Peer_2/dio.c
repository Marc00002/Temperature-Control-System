/*
 * module name:			DIO (Digital Input Output)
 * file name:			dio.c
 * file description:	this file contains the implementation of the module functions
 * version:				v01
 * date:				17/8/2023
 * author:				TEAM
 */

// standards types
// bit maths
// headers of the lower layers
// my own header file

#include "std_types.h"
#include "bit_maths.h"

#include "dio.h"

void MDIO_vidSetPinDirection(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8 cpy_u8PinDirection)
{
	// DDRs
	switch (cpy_u8PinDirection)
	{
	case	OUTPUT:	// set DDRs
		switch (cpy_u8PortNumber)
		{
			case	PORT_A:	SET_BIT(DDRA, cpy_u8PinNumber);	break;
			case 	PORT_B:	SET_BIT(DDRB, cpy_u8PinNumber);	break;
			case	PORT_C:	SET_BIT(DDRC, cpy_u8PinNumber);	break;
			case	PORT_D:	SET_BIT(DDRD, cpy_u8PinNumber);	break;
			default:	/* wrong port number*/	break;
		}
		break;
	case	INPUT:	// clear
		switch (cpy_u8PortNumber)
		{
			case	PORT_A:	CLR_BIT(DDRA, cpy_u8PinNumber);	break;
			case 	PORT_B:	CLR_BIT(DDRB, cpy_u8PinNumber);	break;
			case	PORT_C:	CLR_BIT(DDRC, cpy_u8PinNumber);	break;
			case	PORT_D:	CLR_BIT(DDRD, cpy_u8PinNumber);	break;
			default:	/* wrong port number*/	break;
		}
		break;
	default:
		/* wrong direction */
		break;
	}
}



void MDIO_vidSetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8 cpy_u8PinValue)
{
	// PORTs registers
	switch (cpy_u8PinValue)
	{
	case	HIGH:	// set
		switch (cpy_u8PortNumber)
		{
		case 	PORT_A:	SET_BIT(PORTA, cpy_u8PinNumber);	break;
		case	PORT_B:	SET_BIT(PORTB, cpy_u8PinNumber);	break;
		case	PORT_C:	SET_BIT(PORTC, cpy_u8PinNumber);	break;
		case	PORT_D:	SET_BIT(PORTD, cpy_u8PinNumber);	break;
		default:	/* wrong port number */	break;
		}
		break;
	case	LOW:	// clear
		switch (cpy_u8PortNumber)
		{
		case 	PORT_A:	CLR_BIT(PORTA, cpy_u8PinNumber);	break;
		case	PORT_B:	CLR_BIT(PORTB, cpy_u8PinNumber);	break;
		case	PORT_C:	CLR_BIT(PORTC, cpy_u8PinNumber);	break;
		case	PORT_D:	CLR_BIT(PORTD, cpy_u8PinNumber);	break;
		default:	/* wrong port number */	break;
		}
		break;
	default:
		/* wrong value */
		break;
	}

}



void MDIO_vidGetPinValue(u8 cpy_u8PortNumber, u8 cpy_u8PinNumber, u8* buf_u8PinValue)
{
	// PINs registers
	switch (cpy_u8PortNumber)	// get bit
	{
	case	PORT_A:	*buf_u8PinValue = GET_BIT(PINA, cpy_u8PinNumber);	break;
	case	PORT_B:	*buf_u8PinValue = GET_BIT(PINB, cpy_u8PinNumber);	break;
	case	PORT_C:	*buf_u8PinValue = GET_BIT(PINC, cpy_u8PinNumber);	break;
	case	PORT_D:	*buf_u8PinValue = GET_BIT(PIND, cpy_u8PinNumber);	break;
	default:	/* wrong port number */	break;
	}
}



void MDIO_vidSetPortDirection(u8 cpy_u8PortNumber, u8 cpy_u8PortDirection)
{
	// DDRs
	switch (cpy_u8PortNumber)
	{
	case 	PORT_A:	DDRA = cpy_u8PortDirection;	break;
	case	PORT_B:	DDRB = cpy_u8PortDirection;	break;
	case	PORT_C:	DDRC = cpy_u8PortDirection;	break;
	case	PORT_D:	DDRD = cpy_u8PortDirection;	break;
	default:/* wrong port number */	break;
	}
}

void MDIO_vidSetPortValue(u8 cpy_u8PortNumber, u8 cpy_u8PortValue)
{
	// PORTs registers
	switch (cpy_u8PortNumber)
	{
	case 	PORT_A:	PORTA = cpy_u8PortValue;	break;
	case	PORT_B:	PORTB = cpy_u8PortValue;	break;
	case	PORT_C:	PORTC = cpy_u8PortValue;	break;
	case	PORT_D:	PORTD = cpy_u8PortValue;	break;
	default:	/* wrong port number */	break;
	}
}

void MDIO_vidGetPortValue(u8 cpy_u8PortNumber, u8* buf_u8PortValue)
{
	// PINs registers
	switch (cpy_u8PortNumber)
	{
	case 	PORT_A:	*buf_u8PortValue = PINA;	break;
	case	PORT_B:	*buf_u8PortValue = PINB;	break;
	case	PORT_C:	*buf_u8PortValue = PINC;	break;
	case	PORT_D:	*buf_u8PortValue = PIND;	break;
	default:	/* wrong port number */	break;
	}
}


