/*
 * Timer_private.h
 *
 *  Created on: Aug 27, 2023
 *      Author: DELL
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_


#define TCNT0   (*(volatile u8*)0x52)
//timer control register
#define TCCR0      (*(volatile u8*)0x53)//timer counter control register
//generation mode bit0 normal or ctc
#define TCCR0_WGM00 6  //waveform generation mode 0 timer 0
//generation mode bit1 normal or ctc
#define TCCR0_WGM01 3  //waveform generation mode 1 timer 0
//presscaler bit 2
#define TCCR0_CS02  2  //clock selection
//presscaler bit 1
#define TCCR0_CS01  1
//presscaler bit 0
#define TCCR0_CS00  0
//output compare register0




//#define TIFR   (*(volatile u8*)0x58)//
//#define TIFR_TOV0 0
//output compare register
#define OCRO (*(volatile u8*)0x5c)
//timer mask
#define TIMSK   (*(volatile u8*)0x59)
//output compare 0 interrupt enable
#define TIMSK_OCIE0 1
//normal mode interrupt enable
#define TIMSK_TOIE0 0

//inverted mode or non inverted mode fast pwm
#define TCCR0_COM01 5
#define TCCR0_COM00 4


#define TCCR1A        (*(volatile u8*)0x4F)//timer counter1 control register A
#define TCCR1A_WGM10        0
#define TCCR1A_WGM11        1
#define TCCR1A_FOC1B        2
#define TCCR1A_FOC1A        3
#define TCCR1A_COM1B0       4
#define TCCR1A_COM1B1       5
#define TCCR1A_COM1A0       6
#define TCCR1A_COM1A1       7


#define TCCR1B        (*(volatile u8*)0x4E)//timer counter1 control register B
#define TCCR1B_CS10          0
#define TCCR1B_CS11          1
#define TCCR1B_CS12          2
#define TCCR1B_WGM12         3
#define TCCR1B_WGM13         4
#define TCCR1B_ICES1         6
#define TCCR1B_ICNC1         7


//#define TCNT1  (*(volatile u8*)0x4)

#endif /* TIMER_PRIVATE_H_ */
