/*
 * ADC_private.h
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*ADMUX reference selection bit*/
#define ADMUX *((volatile u8*)0x27)

/*ADSCRA control and status register*/
#define ADCSRA *((volatile u8*)0x26)

/*READ CONVERTION VALUE*/
#define ADCL_H *((volatile u16*)0x24)



#endif /* ADC_PRIVATE_H_ */
