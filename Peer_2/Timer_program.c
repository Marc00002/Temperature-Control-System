/*
 * Timer_program.c
 *
 *  Created on: 
 *      Author: TEAM
 */


#include "STD_TYPES.h"
//#include <util/delay.h>
#include "Timer_private.h"
#include "Timer_interface.h"
#include "BIT_MATHS.h"


static void(*TIMERS_pfTimer0OVF)(void) = NULL;
static void(*TIMERS_pfTimer0CTC)(void) = NULL;

void TIMER0_Vid_init(et_TIMER0MODE mode,et_TIMER0PRESSCALER presscaler)
{
	//timer mode
	switch(mode)
	{
	case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		break;
	case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;
	case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;
	case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		break;
	}
	//presscaler
	TCCR0=TCCR0 & 0xf8; //0b11111000 3ashan at2aked en awel 3 bit b zero
	TCCR0=TCCR0 | presscaler;

}
void TIMER0_Interrupt_Enable()
{
	SET_BIT(TIMSK,TIMSK_TOIE0);
}

void TIMER0_Interrupt_Disable()
{
	CLR_BIT(TIMSK,TIMSK_TOIE0);
}

void TIMER0_Vid_SetCompMatchValue(u8 value)
{
	OCRO=value;
}
void TIMER0_Vid_SetFpwm_Mode(et_TIMER0PWM mode)
{
	switch(mode)
	{
	case inverted:
		SET_BIT(TCCR0,TCCR0_COM01);
		SET_BIT(TCCR0,TCCR0_COM00);
		break;
		//set on compare match,clear on top
	case non_inverted:
		SET_BIT(TCCR0,TCCR0_COM01);
		CLR_BIT(TCCR0,TCCR0_COM00);
		break;
	}
}




u8   TIMERS_u8Timer0SetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = 1;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0OVF =Copy_pf;
	}
	else
	{
		Local_u8ErrorState = 0;
	}
	return Local_u8ErrorState;
}

u8   TIMERS_u8Timer0CTCSetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = 1;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0CTC =Copy_pf;
	}
	else
	{
		Local_u8ErrorState = 0;
	}
	return Local_u8ErrorState;
}

/* Prototype for ISR of TIMER0 OVF */
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	static u16 Local_u16OCounterOVF = 0;
	Local_u16OCounterOVF++;
	if(Local_u16OCounterOVF == 3907)
	{
		/* UpdatePreload Value */
		TCNT0 = 192;
		/* Clear the OVF Counter */
		Local_u16OCounterOVF = 0;
		/* Call App function */
		if(TIMERS_pfTimer0OVF != NULL)
		{
			TIMERS_pfTimer0OVF();
		}
	}
}

/* Prototype for ISR of TIMER0 CTC */
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	static u16 Local_u16OCounterCTC = 0;
	Local_u16OCounterCTC++;
	if(Local_u16OCounterCTC == 10000)
	{
      /* Clear CounterCTC = 0 */
		Local_u16OCounterCTC = 0;
		/* Call CallBack  function*/
		if(TIMERS_pfTimer0CTC != NULL)
		{
			TIMERS_pfTimer0CTC();
		}
	}
}

