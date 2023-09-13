/*
 * KPD_Cfg.h
 *
 *  Created on: Aug 17, 2021
 *      Author: Mosad
 */

#ifndef KPD_CFG_H_
#define KPD_CFG_H_

/**************************** Macros ****************************
 ****************************************************************/
#define   ROWS_NUMBER       4
#define   COLUMNS_NUMBER    4

/**************************** Variables **************************
 ****************************************************************/

/* Values of the Key Pad switches                                                      */
/* Matrix is not standard it depends on the connection between the Micro and KeyPad    */
const u8 KPD_SwitchVal[ROWS_NUMBER][COLUMNS_NUMBER] = {
	  {'7' , '8' , '9' , '/' } ,
	  {'4' , '5' , '6' , '*' } ,
	  {'1' , '2' , '3' , '-' } ,
	  {'C' , '0' , '=' , '+' }
};

const u8 KPD_rowPort [ROWS_NUMBER]     = {PORT_B , PORT_B , PORT_B , PORT_B};
const u8 KPD_rowPins [ROWS_NUMBER]     = {0 , 1 , 2 , 3};
const u8 KPD_coloumsPort [COLUMNS_NUMBER] = {PORT_B , PORT_B , PORT_B , PORT_B};
const u8 KPD_coloumsPins [COLUMNS_NUMBER] = {4 , 5 , 6 , 7};

#endif /* KPD_CFG_H_ */
