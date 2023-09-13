/*
 * ADC_config.h
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/*ADMUX reference selection bit*/
#define ADMUX_REFS1     7  /*use capacitor*/
#define ADMUX_REFS0     6  /*use capacitor*/
#define ADMUX_ADLAR     5  /*read right adjust*/

/*ADCSRA control and status register*/
#define ADCSRA_ADEN     7  /*ADC ENABLE*/
#define ADCSRA_ADSC     6  /*ADC START CONVERSION*/
#define ADCSRA_ADTE     5  /*ADC AUTO TRRIGER INTERRUPT*/
#define ADCSRA_ADIF     4  /*ADC INTERRUPT FLAG*/
#define ADCSRA_ADIE     3  /*ADC INTERRUPT ENABLE*/
#define ADCSRA_ADPS2    2  /*CLOCK (PRESCALER) */
#define ADCSRA_ADPS1    1  /*CLOCK (PRESCALER) */
#define ADCSRA_ADPS0    0  /*CLOCK (PRESCALER) */

/*channel number*/
#define channel0      0b00000
#define channel1      0b00001
#define channel2      0b00010
#define channel3      0b00011
#define channel4      0b00100
#define channel5      0b00101
#define channel6      0b00110
#define channel7      0b00111

/*prescaler*/
#define  PRE_SCALER_VALUE 128

#endif /* ADC_CONFIG_H_ */
