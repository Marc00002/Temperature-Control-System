/*
 * SPI_progarm.c
 *
 *  Created on: 
 *      Author: TEAM
 */

#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include "SPI_private.h"
#include "SPI_interface.h"

void SPI_VidMasterInit(void)
{
	//select clk pol=0;clk ph=0
	CLR_BIT(SPI_SPCR,SPCR_CPHA);
	CLR_BIT(SPI_SPCR,SPCR_CPOL);

	//select master mode
	SET_BIT(SPI_SPCR,SPCR_MSTR);

	//set data order MSB
	CLR_BIT(SPI_SPSR,SPSR_SPI2X);
	CLR_BIT(SPI_SPCR,SPCR_SPR1);
	CLR_BIT(SPI_SPCR,SPCR_SPR0);

	//enable SPI
	SET_BIT(SPI_SPCR,SPCR_SPE);

}
void SPI_VidSlaveInit(void)
{
	//select slave mode
	CLR_BIT(SPI_SPCR,SPCR_MSTR);

	//set data order MSB
	CLR_BIT(SPI_SPCR,SPCR_DORD);

	//enable SPI
	SET_BIT(SPI_SPCR,SPCR_SPE);
}
u8 SPI_U8TranSceive(u8 Copy_U8Data)
{
	//send data
	SPI_SPDR=Copy_U8Data;

	//flag check
	while (GET_BIT(SPI_SPSR,SPSR_SPIF)==0);
	return SPI_SPDR;
}
