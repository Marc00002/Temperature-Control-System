/*
 * ADC_interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: DELL
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include"STD_TYPES.h"
typedef enum
{
	chanel0,
	chanel1,
	chanel2,
	chanel3,
	chanel4,
	chanel5,
	chanel6,
	chanel7
}ChannelName;

void ADC_VidInIt(void);
u16 ADC_u16ReadChannelSyn(u8 Copy_u8Channel);

#endif /* ADC_INTERFACE_H_ */
