/*
 * gie.c

 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATHS.h"
#include "gie.h"




void MGIE_vidEnable()
{
	/*set bit #7 at the status register*/
	SET_BIT(SREG,I);
}
void MGIE_vidDisable()
{
	/*Clear bit #7 at the status register*/
	CLR_BIT(SREG,I);

}
