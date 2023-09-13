/*
 * Timer_interface.h
 *
 *  Created on: 
 *      Author: TEAM
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
}et_TIMER0MODE;

typedef enum
{
	No_clock_source=0,
	no_prescaling,
	clk_8prescaker,
	clk_64_prescaler,
	clk_256_prescaler,
	clk_1024_prescaler,
	External_clock_fallingedge,
	External_clock_risingedge
}et_TIMER0PRESSCALER;

typedef enum
{
	inverted,
	non_inverted
}et_TIMER0PWM;

void TIMER0_Vid_init(et_TIMER0MODE mode,et_TIMER0PRESSCALER presscaler);

void TIMER0_Vid_SetCompMatchValue(u8 value);
void TIMER0_Vid_SetFpwm_Mode(et_TIMER0PWM mode);

void TIMER0_Interrupt_Enable();

void TIMER0_Interrupt_Disable();


u8   TIMERS_u8Timer0SetCallBack(void(*Copy_pf)(void));

u8   TIMERS_u8Timer0CTCSetCallBack(void(*Copy_pf)(void));

#endif /* TIMER_INTERFACE_H_ */
