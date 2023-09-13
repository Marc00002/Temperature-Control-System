/*
 * main.c
 *
 *  Created on: Aug 31, 2023
 *      Author: DELL
 */

#include "STD_TYPES.h"
#include "dio.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "util/delay.h"
#include "gie.h"

#include "UART_interface.h"
#include "SPI_interface.h"
#include "TWI_Interface.h"

#include "EEP_Interface.h"

//#include "STD_TYPES.h"
//#include <util/delay.h>

#define HEATING         0
#define COOLING         1
#define NoOperation     2


f64 DutyCycle=80;
//
//void OverFlowInterrupt()
//{
//	TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
//}

void TurnOnHeater()
{


	MDIO_vidSetPinDirection(PORT_B,3,OUTPUT);
	TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
	TIMER0_Vid_SetFpwm_Mode(non_inverted);
	TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);

	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,5,LOW);

	MDIO_vidSetPinDirection(PORT_D,6,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,6,LOW);

	MDIO_vidSetPinDirection(PORT_D,7,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,7,LOW);

//	TIMER0_Interrupt_Enable();
//	MGIE_vidEnable();
//
//	TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
}

void TurnOnCooler()
{


	MDIO_vidSetPinDirection(PORT_B,3,OUTPUT);
	TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
	TIMER0_Vid_SetFpwm_Mode(non_inverted);
	TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);

	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,5,LOW);

	MDIO_vidSetPinDirection(PORT_D,6,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,6,LOW);

	MDIO_vidSetPinDirection(PORT_D,7,OUTPUT);
	MDIO_vidSetPinValue(PORT_D,7,HIGH);

//	TIMER0_Interrupt_Enable();
//	MGIE_vidEnable();

	//TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
}

void TurnOnEqualLed()
{
	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);
	MDIO_vidSetPinDirection(PORT_D,6,OUTPUT);

	MDIO_vidSetPinValue(PORT_D,5,HIGH);
	MDIO_vidSetPinValue(PORT_D,6,HIGH);

//				MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
//				MDIO_vidSetPinValue(PORT_D,1,LOW);
	//_delay_ms(10);
}

void CompareTemp(u8 CurrentTemp,u8 DesiredTemp)
{
	if(CurrentTemp<DesiredTemp)
	{
		TurnOnHeater();
		//return HEATING;
		UART_VidSendData(HEATING);
	}


	else if(CurrentTemp>DesiredTemp)
	{
		TurnOnCooler();
		//return COOLING;
		UART_VidSendData(COOLING);
	}
	else
	{
		TurnOnEqualLed();
		//return NoOperation;
		UART_VidSendData(NoOperation);
	}
}

int main()
{

//	MDIO_vidSetPinDirection(PORT_B,3,OUTPUT);

//	MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
//	MDIO_vidSetPinValue(PORT_D,0,LOW);
//
//	MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
//	MDIO_vidSetPinValue(PORT_D,1,LOW);

//	TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
//	TIMER0_Vid_SetFpwm_Mode(non_inverted);
//	TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
//
//	TIMER0_Interrupt_Enable();
//	MGIE_vidEnable();
//
//	TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);

//	MDIO_vidSetPinDirection(PORT_B,7,INPUT);
//	MDIO_vidSetPinDirection(PORT_B,5,INPUT);
//	MDIO_vidSetPinDirection(PORT_B,6,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_B,4,INPUT);

	//MDIO_vidSetPinDirection(PORT_A,7,OUTPUT);

	//SPI_VidSlaveInit();

	MDIO_vidSetPinDirection(PORT_D,0,INPUT);
	MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);

	TWI_voidInitMaster(0);
	UART_VidInit();

	u8 CurrentTemp;
	u8 DesiredTemp;

	EEP_WriteByte(0x01,25);
	_delay_ms(20);

	EEP_WriteByte(0x02,30);
	_delay_ms(20);

    EEP_ReadByte(0x01 , & DesiredTemp);
	_delay_ms(20);

//    EEP_ReadByte(0x02 , & CurrentTemp);
//	_delay_ms(20);



//	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_D,6,OUTPUT);

//	MDIO_vidSetPinValue(PORT_D,5,LOW);
//	MDIO_vidSetPinValue(PORT_D,6,HIGH);

//	MDIO_vidSetPinDirection(PORT_D,7,OUTPUT);
//	MDIO_vidSetPinValue(PORT_D,7,LOW);

	while(1)
	{
		//u8 x,y;

		u8 Buffer;
		Buffer=UART_VidReceiveData();
		if(Buffer==2)
		{
			UART_VidSendData(DesiredTemp);
		}
		//_delay_ms(10);

		else
		{
			DesiredTemp=Buffer;
		}
		CurrentTemp=UART_VidReceiveData();

		CompareTemp(CurrentTemp,DesiredTemp);

		EEP_WriteByte(0x01,DesiredTemp);
		_delay_ms(20);

		EEP_WriteByte(0x02,CurrentTemp);
		_delay_ms(20);
//
//	    EEP_ReadByte(0x01 , & x);
//		_delay_ms(20);
//
//		EEP_ReadByte(0x02 , & y);
//		_delay_ms(20);
//
//		if(CurrentTemp==y && DesiredTemp==x)
//		{
//			MDIO_vidSetPinDirection(PORT_A,5,OUTPUT);
//			MDIO_vidSetPinValue(PORT_A,5,HIGH);
//		}

		//_delay_ms(10);

//		 CurrentTemp = SPI_U8TranSceive(0);
//
//		_delay_ms(10);
//
//		 DesiredTemp = SPI_U8TranSceive(0);
//
//		_delay_ms(10);
//
		//CompareTemp(CurrentTemp,DesiredTemp);
//
////				if(CurrentTemp<DesiredTemp)
////				{
////					MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////					MDIO_vidSetPinValue(PORT_D,0,LOW);
////
////					MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
////					MDIO_vidSetPinValue(PORT_D,1,LOW);
////
////           		MDIO_vidSetPinDirection(PORT_B,3,OUTPUT);
////					TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
////					TIMER0_Vid_SetFpwm_Mode(non_inverted);
////					TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
////
////					TIMER0_Interrupt_Enable();
////					MGIE_vidEnable();
////
////					TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
////				}
////
////
////				else if(CurrentTemp>DesiredTemp)
////				{
////					MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////					MDIO_vidSetPinValue(PORT_D,0,LOW);
////
////					MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
////					MDIO_vidSetPinValue(PORT_D,1,HIGH);
////
////           		MDIO_vidSetPinDirection(PORT_B,3,OUTPUT);
////					TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
////					TIMER0_Vid_SetFpwm_Mode(non_inverted);
////					TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
////
////					TIMER0_Interrupt_Enable();
////					MGIE_vidEnable();
////
////					TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
////				}
////				else
////				{
////					MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////					MDIO_vidSetPinValue(PORT_D,0,HIGH);
////
////	//				MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
////	//				MDIO_vidSetPinValue(PORT_D,1,LOW);
////					//_delay_ms(10);
////				}
////		 if(CurrentTemp==0)
////		 {
////				MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////				MDIO_vidSetPinValue(PORT_D,0,LOW);
////
////				MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
////				MDIO_vidSetPinValue(PORT_D,1,LOW);
////
////				TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
////				TIMER0_Vid_SetFpwm_Mode(non_inverted);
////				TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
////
////				TIMER0_Interrupt_Enable();
////				MGIE_vidEnable();
////
////				TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
////
////		 }
////		 else if(CurrentTemp==1)
////		 {
////				MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////				MDIO_vidSetPinValue(PORT_D,0,LOW);
////
////				MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
////				MDIO_vidSetPinValue(PORT_D,1,HIGH);
////
////				TIMER0_Vid_init(TIMER0_FASTPWM_MODE,clk_64_prescaler);
////				TIMER0_Vid_SetFpwm_Mode(non_inverted);
////				TIMER0_Vid_SetCompMatchValue((DutyCycle/100)*255);
////
////				TIMER0_Interrupt_Enable();
////				MGIE_vidEnable();
////
////				TIMERS_u8Timer0SetCallBack(&OverFlowInterrupt);
////
////		 }
////		 else if(CurrentTemp==2)
////		 {
////				MDIO_vidSetPinDirection(PORT_D,0,OUTPUT);
////				MDIO_vidSetPinValue(PORT_D,0,HIGH);
////
//////				MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);
//////				MDIO_vidSetPinValue(PORT_D,1,LOW);
////		 }
//
//		//if(data)
//			//MDIO_vidSetPinValue(PORT_A,7,CurrentTemp);
//		_delay_ms(10);
//
////			if(CurrentTemp==0)
////				 SPI_U8TranSceive(1);
////			else if(CurrentTemp==1)
////				SPI_U8TranSceive(0);
//
////
////			 DesiredTemp = SPI_U8TranSceive(2);
////
////			_delay_ms(10);
////
////			//if(data)
////				MDIO_vidSetPinValue(PORT_A,0,DesiredTemp);
////				_delay_ms(10);
	}
	return 0;
}
