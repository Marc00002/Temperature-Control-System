/*
 * SPI_private.h
 *
 *  Created on: Aug 31, 2023
 *      Author: TEAM
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//SPI control register
#define SPI_SPCR  *((volatile u8*)0x2D)

//SPI interrupt enable
#define SPCR_SPIE         7

//SPI Enable
#define SPCR_SPE          6

//data order lsb (write 1) or msb (write 0)
#define SPCR_DORD         5

//Master or slave select master(write 1), slave(write 0)
#define SPCR_MSTR         4

//CLOCK polarity low (write 0), high (write 1)
#define SPCR_CPOL         3

/*Clock phase
 * Sample (leading) and setup (tralling) write (0)
 * setup (leading) and Sample (tralling) write (1)
 * */

#define SPCR_CPHA          2

//SPI clock rate select, master only
#define SPCR_SPR1          1
#define SPCR_SPR0          0

//SPI status register
#define SPI_SPSR  *((volatile u8*)0x2E)

//SPI interrupt flag
#define SPSR_SPIF          7

//Write collision flag
#define SPSR_WCOL          6

//double speed bit
#define SPSR_SPI2X         0

//SPI data register
#define SPI_SPDR  *((volatile u8*)0x2F)

#define SPSR_MSB            7
#define SPSR_LSB            0
#endif /* SPI_PRIVATE_H_ */
