/*
 * gie.h
 *
 *  Created on: 
 *      Author: TEAM
 */

#ifndef GIE_H_
#define GIE_H_

#define SREG  (*(volatile u8*)0x5F)

void MGIE_vidEnable();
void MGIE_vidDisable();

#define I (u8)7
#endif /* GIE_H_ */
