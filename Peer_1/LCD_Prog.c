/*
 * LCD.c
 *
 *  Created on: Aug 14, 2021
 *      Author: Mosad
 */
/* Library */
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#define F_CPU 8000000
#include "util/delay.h"

/* MCAL */
#include "dio.h"

/* Own driver include */
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Cfg.h"


void LCD_voidInit(void)
{
	/* Initialize the Pins */
	MDIO_vidSetPinDirection(LCD_RS_PORT , LCD_RS_PIN , OUTPUT);
	MDIO_vidSetPinDirection(LCD_RW_PORT ,LCD_RW_PIN , OUTPUT );
	MDIO_vidSetPinDirection(LCD_E_PORT ,LCD_E_PIN , OUTPUT );
	MDIO_vidSetPortDirection(LCD_DATA_PORT , OUTPUT);

	_delay_ms(30);

	/* Send command function set */
	LCD_voidSendCommand(lcd_FunctionSet8bit);
	_delay_ms(10);

	/* Send command dispaly on */
	LCD_voidSendCommand(lcd_DisplayOn);
	_delay_ms(10);

	/* Clear the display  */
	LCD_voidSendCommand(lcd_Clear);
	_delay_ms(10);

	/* Entry mode set  */
	LCD_voidSendCommand(lcd_EntryMode);
	_delay_ms(10);

	/* Set cursor home */
	LCD_voidSendCommand(lcd_Home);
	_delay_ms(10);
}

void LCD_voidSendCommand (u8 Cpy_command )
{
	/* Reset RS and RW */
	MDIO_vidSetPinValue(LCD_RS_PORT , LCD_RS_PIN , LOW);
	MDIO_vidSetPinValue(LCD_RW_PORT , LCD_RW_PIN , LOW);

	/* Write the command to data port */
	MDIO_vidSetPortValue(LCD_DATA_PORT , Cpy_command);

	/* Send Enable signal */
	MDIO_vidSetPinValue(LCD_E_PORT , LCD_E_PIN , HIGH);
	_delay_ms(1);
	MDIO_vidSetPinValue(LCD_E_PORT , LCD_E_PIN , LOW);
	_delay_ms(10);
}

void LCD_voidSendChar (u8 Cpy_data)
{
	/* Reset RW */
	MDIO_vidSetPinValue(LCD_RW_PORT , LCD_RW_PIN , LOW);

	/* Set RS */
	MDIO_vidSetPinValue(LCD_RS_PORT , LCD_RS_PIN , HIGH);

	/* Write the command to data port */
	MDIO_vidSetPortValue(LCD_DATA_PORT , Cpy_data);

	/* Send Enable signal */
	MDIO_vidSetPinValue(LCD_E_PORT , LCD_E_PIN , HIGH);
	_delay_ms(1);
	MDIO_vidSetPinValue(LCD_E_PORT , LCD_E_PIN , LOW);
	_delay_ms(10);
}


void LCD_voidPrintString(char *str)
{
	for (u8 i=0;str[i]!=0;i++)
		LCD_voidSendChar(str[i]);
}

void LCD_voidWriteString(const u8 *Cpy_str)
{
	while ( (*Cpy_str) != NULL)
	{
		LCD_voidSendChar(*Cpy_str);
		Cpy_str++;
		_delay_ms(5);
	}
}

void LCD_voidGoTo(u8 Cpy_row , u8 Cpy_column)
{
	if ((Cpy_row>0) && (Cpy_column<=16))
	{
	    switch(Cpy_row)
	    {
		    case 1:
		    	LCD_voidSendCommand(Cpy_column+127);
		    break;

		    case 2:
		    	LCD_voidSendCommand(Cpy_column+191);
		    break;

		    default:
		    break;
	    }
	}
}

void LCD_voidAddNewPattern (u8 *Cpy_patternArray , u8 Cpy_blockNumber)
{
	u8 local_CGAdress = Cpy_blockNumber*LCD_CGRAM_BLOCKS_SIZE + LCD_CGRAM_START ;
	if (Cpy_blockNumber < LCD_CGRAM_BLOCKS_NUMBER)
	{
		LCD_voidSendCommand(local_CGAdress);
		for (u8 i = 0 ; i < LCD_CGRAM_BLOCKS_SIZE ; i++)
		{
			LCD_voidSendChar(Cpy_patternArray[i]);
		}
	}
	else
	{
		/* Error */
	}
}

void LCD_voidWritePattern (u8 Cpy_blockNumber , u8 Cpy_row , u8 Cpy_column)
{
	if (Cpy_blockNumber < LCD_CGRAM_BLOCKS_NUMBER)
	{
		LCD_voidGoTo(Cpy_row , Cpy_column);
		LCD_voidSendChar(Cpy_blockNumber);
	}
	else
	{
		/* Error */
	}
}


void LCD_voidPrintInt(s32 Number)
{
	s32 a[100];
	s32 i=0;
	u8 c=0;
	if(Number==0)
		LCD_voidSendChar('0');
	if(Number<0)
	{
		Number*=-1;
		c='-';
	}
	while(Number!=0)
	{
		a[i]=Number%10;
		//LCD_voidSendData(x+48);
		Number/=10;
		i++;
	}
	for(s32 j=i-1;j>=0;j--)
	{
		if(c=='-')
		{
			LCD_voidSendChar(c);
			c=0;
		}
		LCD_voidSendChar(a[j]+48);
	}
}
