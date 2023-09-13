/*
 * UART_interface.h
 *
 *  Created on: 
 *      Author: TEAM
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_VidSendData(u8 Copy_u8Data);
u8 UART_VidReceiveData(void);
void UART_VidInit(void);

#endif /* UART_INTERFACE_H_ */
