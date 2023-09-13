/*
 * Keypad.c
 *
 *  Created on: 
 *      Author: TEAM
 */
/* Library */
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#define F_CPU 8000000
#include "util/delay.h"

/* MCAL */
#include "dio.h"

/* Own driver include */
#include "KPD_Interface.h"
#include "KPD_Private.h"
#include "KPD_Cfg.h"


void KPD_voidInitPins(void)
{
	/* Init Rows */
	for (u8 loc_counter = 0 ; loc_counter < ROWS_NUMBER ; loc_counter++ )
	{
		/* Set Rows as output */
		MDIO_vidSetPinDirection(KPD_rowPort[loc_counter] ,KPD_rowPins[loc_counter] ,OUTPUT );
		/* Init Rows with High */
		MDIO_vidSetPinValue(KPD_rowPort[loc_counter] ,KPD_rowPins[loc_counter] ,HIGH );
	}

	/* Init Columns */
	for (u8 loc_counter = 0 ; loc_counter < COLUMNS_NUMBER ; loc_counter++)
	{
		/* Set columns as input*/
		MDIO_vidSetPinDirection(KPD_coloumsPort[loc_counter] ,KPD_coloumsPins[loc_counter] ,INPUT );
		/* Enable pull up*/
		MDIO_vidSetPinValue(KPD_coloumsPort[loc_counter] ,KPD_coloumsPins[loc_counter] ,HIGH );
	}
}


u8 KPD_u8GetPressedKey(void)
{
	s8 loc_pressed_key = 0 ;
	u8 loc_keyState ;

	for (u8 loc_row = 0 ; loc_row < ROWS_NUMBER ; loc_row++ )
	{
		/* Activate one row */
		MDIO_vidSetPinValue(KPD_rowPort[loc_row] , KPD_rowPins[loc_row] , LOW);

		/* Check on columns */
		for (u8 loc_col = 0 ; loc_col < COLUMNS_NUMBER ; loc_col++ )
		{
			MDIO_vidGetPinValue(KPD_coloumsPort[loc_col] ,KPD_coloumsPins[loc_col],&loc_keyState );
			/* Check on column */
			if (loc_keyState == 0)
			{
				loc_pressed_key = KPD_SwitchVal[loc_row][loc_col];
			}

			/* Wait to release the key */
			while (loc_keyState == 0)
			{
				MDIO_vidGetPinValue(KPD_coloumsPort[loc_col] ,KPD_coloumsPins[loc_col],&loc_keyState );
			}

			/* Delay for debounce */
			_delay_ms(10);

		}

		/* Deactivate the row */
		MDIO_vidSetPinValue(KPD_rowPort[loc_row] , KPD_rowPins[loc_row] , HIGH);
	}
	return loc_pressed_key ;
}




