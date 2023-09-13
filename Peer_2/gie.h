/*
 * gie.h
 *
 *  Created on: Aug 23, 2023
 *      Author: DELL
 */

#ifndef GIE_H_
#define GIE_H_

#define SREG  (*(volatile u8*)0x5F)

void MGIE_vidEnable();
void MGIE_vidDisable();

#define I (u8)7
#endif /* GIE_H_ */
