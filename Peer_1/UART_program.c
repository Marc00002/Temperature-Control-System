/*
 * UART_program.c
 *
 *  Created on: Aug 30, 2023
 *      Author: TEAM
 */
#include"STD_TYPES.h"
#include"BIT_MATHS.h"
#include"UART_interface.h"
#include"UART_private.h"

void UART_VidSendData(u8 Copy_u8Data)
{
	while (GET_BIT(UCSRA,UDRE)!=1);
	UDR=Copy_u8Data;
}
u8 UART_VidReceiveData(void)
{
	while (GET_BIT(UCSRA,RXC)!=1);
	return UDR;
}
void UART_VidInit(void)
{
	//Set frame format -> 8 data, 1 stop, no parity
	u8 local =0;
	SET_BIT(local,URSEL);
	SET_BIT(local,UCSZ1);
	SET_BIT(local,UCSZ0);

	UCSRC=local;//or 0x68,0b100000110

	//boud rate 9600........ table datasheet
	UBRRL=51;
	//rx enable and tx enable
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}
