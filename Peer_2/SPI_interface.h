/*
 * SPI_interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: DELL
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_VidMasterInit(void);
void SPI_VidSlaveInit(void);
u8 SPI_U8TranSceive(u8 Copy_U8Data);

#endif /* SPI_INTERFACE_H_ */
