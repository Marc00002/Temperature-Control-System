/*
 * main.c
 *
 *  Created on: Aug 31, 2023
 *      Author: TEAM
 */
#include "dio.h"
#include "SPI_interface.h"
#include "STD_TYPES.h"
#include "BIT_MATHS.h"
#include <util/delay.h>
#include "UART_interface.h"

//#include "IIC_interface.h"
//#include "EEPROM_interface.h"

#include "ADC_interface.h"
#include "ADC_config.h"

//#include <stdio.h> // Include standard I/O functions for snprintf

#include "LCD_Interface.h"
#include "KPD_Interface.h"

#define HEATING         0
#define COOLING         1
#define NoOperation     2

u8 global_u8Num1 , global_u8Num2 , global_u8Operation;
s8 global_u8Sum;
u8 global_u8WrongFlag ;
u8 global_u8StrArr[10];
u8 global_u8DesiredTemp;
u8 global_u8Choose;
u8 global_u8ChooseFlag;


void Welcome()
{
	LCD_voidGoTo(1 , 5);
	LCD_voidWriteString("WELCOME!");

	// Clear the text letter after letter
	_delay_ms(1000); // Wait for 2 seconds
	LCD_voidSendCommand(lcd_Clear);

	// Display "TEMPERATURE CONTROL SYSTEM" all text at the same time

	LCD_voidGoTo(1 , 3);   /* Move to second line */
	LCD_voidWriteString("TEMPERATURE");
	LCD_voidGoTo(2 , 2);
	LCD_voidWriteString("CONTROL SYSTEM");
	// Clear all text
	_delay_ms(1000); // Wait for 2 seconds
	LCD_voidWriteString(lcd_Clear);
}


//#define OFFSET         (u8)1


void ReceiveOperation(u8 Operation)
{
	MDIO_vidSetPinDirection(PORT_A,3,OUTPUT);
	MDIO_vidSetPinDirection(PORT_A,4,OUTPUT);
	MDIO_vidSetPinDirection(PORT_A,5,OUTPUT);
//	LCD_voidSendCommand(lcd_Clear);
//	LCD_voidWriteString(lcd_Clear);

	if(Operation == HEATING)
	{
		MDIO_vidSetPinValue(PORT_A,5,LOW);
		MDIO_vidSetPinValue(PORT_A,4,LOW);
		MDIO_vidSetPinValue(PORT_A,3,HIGH);
//		TOG_BIT(PORTA,3);
//		LCD_voidWriteString(lcd_Clear);
		LCD_voidGoTo(2 , 5);
     	LCD_voidWriteString("HEATING");
		//_delay_ms(500);
	}
	else if(Operation == COOLING)
	{
		MDIO_vidSetPinValue(PORT_A,5,LOW);
		MDIO_vidSetPinValue(PORT_A,3,LOW);
		MDIO_vidSetPinValue(PORT_A,4,HIGH);
		//TOG_BIT(PORTA,4);
		LCD_voidGoTo(2 , 5);
		LCD_voidWriteString("COOLING");
		//_delay_ms(500);
	}
	else if(Operation == NoOperation)
	{
		MDIO_vidSetPinValue(PORT_A,3,LOW);
		MDIO_vidSetPinValue(PORT_A,4,LOW);
		MDIO_vidSetPinValue(PORT_A,5,HIGH);
		//TOG_BIT(PORTA,5);
		//LCD_voidWriteString(lcd_Clear);
		LCD_voidGoTo(2 , 3);
		LCD_voidWriteString("NO Operation");
		//_delay_ms(500);
	}
}

void SendReceiveData(u8 CurrentTemp,u8 DesiredTemp)
{
	u8 Operation;

	if(global_u8Choose !='2')
	UART_VidSendData(DesiredTemp);
	//_delay_ms(100);

	UART_VidSendData(CurrentTemp);
	//_delay_ms(100);

	Operation=UART_VidReceiveData();
	//_delay_ms(100);

	LCD_voidSendCommand(lcd_Clear);
	LCD_voidGoTo(1 , 4);
	LCD_voidPrintInt(CurrentTemp);
	LCD_voidWriteString(" --> ");
	LCD_voidPrintInt(DesiredTemp);

	ReceiveOperation(Operation);
}




void GETDesiredTemp(u8 CurrentTemp)
{
	/* Clear screen at the start of every operation */
			LCD_voidSendCommand(lcd_Clear);

			LCD_voidWriteString("Current Temp:");
			LCD_voidPrintInt(CurrentTemp);

			LCD_voidSendCommand(0xC0);
			LCD_voidWriteString("1.New 2.Old ");

			while (global_u8Choose != '1'  && global_u8Choose != '2' )
			{
				global_u8Choose = KPD_u8GetPressedKey();

			}

			if((global_u8Choose != '1'  &&  global_u8Choose != '2' ))
			{
				//global_u8ChooseFlag=1;
				LCD_voidSendCommand(lcd_Clear);
				LCD_voidWriteString("WRONG INPUT !");
				LCD_voidSendCommand(0xC0);
				LCD_voidWriteString("TRY AGAIN !");
				_delay_ms(1000);
				global_u8Choose=0;
				GETDesiredTemp(CurrentTemp);

			}
			if(global_u8Choose=='1')
			{
				LCD_voidSendCommand(0xC0);
				LCD_voidWriteString("Desired Temp: ");
				//LCD_DisplayMessage("Targeted Temp:");

				/************** To Enter first operand ******************/

				/* Wait till button is pressed */
				while (global_u8Num1 == 0)
				{
					global_u8Num1 = KPD_u8GetPressedKey();
				}
				if(global_u8Num1 <'1' || global_u8Num1 > '9')
				{
					LCD_voidSendCommand(lcd_Clear);
					LCD_voidWriteString("WRONG INPUT !");
					LCD_voidSendCommand(0xC0);
					LCD_voidWriteString("TRY AGAIN !");
					_delay_ms(1000);
					global_u8Choose=0;
					global_u8Num1 = 0 ;
					GETDesiredTemp(CurrentTemp);
				}

				// Set cursor to the first line
				//LCD_voidSendCommand(lcd_Clear);

				/* Print the number on screen first */
				LCD_voidSendChar(global_u8Num1);

				/* Then convert from Ascii to integer */
				global_u8Num1 -= 48 ;

				//global_u8DesiredTemp=global_u8Num1*10;

				/********************** To Enter second operand *************/

				/* Wait till button is pressed */
				while (global_u8Num2 == 0)
				{
					global_u8Num2 = KPD_u8GetPressedKey();
				}
				if(global_u8Num2 <'0' || global_u8Num2 > '9')
				{
					LCD_voidSendCommand(lcd_Clear);
					LCD_voidWriteString("WRONG INPUT !");
					LCD_voidSendCommand(0xC0);
					LCD_voidWriteString("TRY AGAIN !");
					_delay_ms(1000);
					global_u8Choose = 0;
					global_u8Num1 = 0 ;
					global_u8Num2 = 0 ;
					GETDesiredTemp(CurrentTemp);
				}

				/* Print the number on screen first */
				LCD_voidSendChar(global_u8Num2);

				/* Then convert from Ascii to integer */
				global_u8Num2 -= 48 ;

				/****************** Wait to enter equal *********************/
				//while (KPD_u8GetPressedKey() != 'C');

				global_u8DesiredTemp = global_u8Num1*10 + global_u8Num2;

			}
			else if(global_u8Choose=='2')
			{
				UART_VidSendData(2);
				global_u8DesiredTemp = UART_VidReceiveData();
				LCD_voidSendCommand(0xC0);
				LCD_voidWriteString("Desired Temp: ");
				LCD_voidPrintInt(global_u8DesiredTemp);
				//LCD_voidSendCommand(lcd_Clear);
			}


			if(global_u8DesiredTemp>=20 && global_u8DesiredTemp <=40 )
			{
				MDIO_vidSetPinDirection(PORT_A,6,OUTPUT);
				MDIO_vidSetPinValue(PORT_A,6,HIGH);
			}
			else
			{
				MDIO_vidSetPinDirection(PORT_A,6,OUTPUT);
				MDIO_vidSetPinValue(PORT_A,6,LOW);
				LCD_voidSendCommand(lcd_Clear);
				//LCD_voidSendCommand(0xC0);
				//LCD_voidGoTo(2 , 5);   /* Move to second line */
				LCD_voidWriteString("WRONG INPUT !");
				LCD_voidSendCommand(0xC0);
				LCD_voidWriteString("TRY AGAIN !");
				_delay_ms(1000);
				global_u8Choose = 0;
				global_u8Num1 = 0 ;
				global_u8Num2 = 0 ;
				//global_u8Operation = 0 ;
				global_u8DesiredTemp=0;

				GETDesiredTemp(CurrentTemp);
			}

			SendReceiveData(CurrentTemp,global_u8DesiredTemp);
			/****************** Re init variables ***************/
//			global_u8Num1 = 0 ;
//			global_u8Num2 = 0 ;
//			global_u8DesiredTemp=0;
//			global_u8Choose=0;
//
//			/********* Wait User to enter any key to start new operation  ******/
//			while ( ! (KPD_u8GetPressedKey()) );

}

//int main ()
//{
//
//	/* Init HAL modules */
//	LCD_voidInit();
//	KPD_voidInitPins();
//
//	Welcome();
//	LCD_voidGoTo(1 , 5);
//	LCD_voidWriteString("WELCOME!");
//
//	// Clear the text letter after letter
//	_delay_ms(1000); // Wait for 2 seconds
//	LCD_voidSendCommand(lcd_Clear);
//
//	// Display "TEMPERATURE CONTROL SYSTEM" all text at the same time
//
//	LCD_voidGoTo(1 , 3);   /* Move to second line */
//	LCD_voidWriteString("TEMPERATURE");
//	LCD_voidGoTo(2 , 2);
//	LCD_voidWriteString("CONTROL SYSTEM");
//	// Clear all text
//	_delay_ms(1000); // Wait for 2 seconds
//	LCD_voidWriteString(lcd_Clear);


void GetCurrentTemp()
{
	u8 CurrentTemp;

	u8 DesiredTemp=35;
	CurrentTemp = ADC_u16ReadChannelSyn(channel7);
	//float temperature = ((CurrentTemp * 5.0) / (1024.0 * 10.0))/2;
    //float temperature = (float)CurrentTemp * (60.0 / 1023.0) - 10.0;
    CurrentTemp = (CurrentTemp *0.5)-1;
    //_delay_ms(100);
    GETDesiredTemp(CurrentTemp);
   // SendReceiveData( CurrentTemp, DesiredTemp);

}


 //Function to initialize the system
//void System_Init() {
//    LCD_Init();     // Initialize LCD
//    KEYPAD_Init();
//    // Initialize Keypad
//}
//
//// Function to display a message on LCD character by character with delay
//void LCD_DisplayMessage(const char* message) {
//    int i = 0;
//    while (message[i] != '\0') {
//        LCD_WriteChar(message[i]);
//        _delay_ms(100); // Delay between characters (adjust as needed)
//        i++;
//    }
//}


void Start()
{
	GetCurrentTemp();
}
int main()
{
//	MDIO_vidSetPortDirection(PORT_C,0xFF);
//	MDIO_vidSetPortDirection(PORT_B,0xFF);
//
//	MDIO_vidSetPinDirection(PORT_D,4,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);
//
//	MDIO_vidSetPinDirection(PORT_D,4,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_D,5,OUTPUT);



//	MDIO_vidSetPinDirection(PORT_B,7,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_B,5,OUTPUT);
//	MDIO_vidSetPinDirection(PORT_B,6,INPUT);
//	MDIO_vidSetPinDirection(PORT_B,4,INPULL);

	//MDIO_vidSetPinDirection(PORT_A,0,OUTPUT);

//  SPI_VidMasterInit();

	LCD_voidInit();
	KPD_voidInitPins();

	Welcome();

	MDIO_vidSetPinDirection(PORT_D,0,INPUT);
	MDIO_vidSetPinDirection(PORT_D,1,OUTPUT);

	ADC_VidInIt();

	UART_VidInit();

//	u8 CurrentTemp;
//
//	u8 DesiredTemp=30;
//
//	u8 Operation;

	//TWI_voidInitMaster(0b1010);

//    // Define some sample data
//    u8 data1 = 0x11;
//    u8 data2 = 0x22;
//    u8 data3 = 0x33;
//    u8 data4 = 0x44;
//
//    // Save data in block 0
//    EEPROM_voidSendDataByte(0, data1);
//
//    _delay_ms(100);
//
//    EEPROM_voidSendDataByte(1, data2);
//
//    _delay_ms(100);
//
//    // Save data in block 1
//    EEPROM_voidSendDataByte(256, data3);
//
//    _delay_ms(100);
//
//    EEPROM_voidSendDataByte(257, data4);
//
//    _delay_ms(100);
//    // Read data from block 0
//    u8 readData1 = EEPROM_u8ReadDataByte(0);
//
//    _delay_ms(100);
//
//    u8 readData2 = EEPROM_u8ReadDataByte(1);
//
//    _delay_ms(100);
//    // Read data from block 1
//    u8 readData3 = EEPROM_u8ReadDataByte(256);
//
//    _delay_ms(100);
//
//    u8 readData4 = EEPROM_u8ReadDataByte(257);
//
//    _delay_ms(100);
//
//    // Check if the data was read correctly
//    if (readData1 == data1 && readData2 == data2)
//    {
//		MDIO_vidSetPinDirection(PORT_A,4,OUTPUT);
//		MDIO_vidSetPinDirection(PORT_A,4,HIGH);
//
//
//        // Data in block 0 is correct
//    } else {
//        // Data in block 0 is incorrect
//    }
//
//    if (readData3 == data3 && readData4 == data4) {
//        // Data in block 1 is correct
//    } else {
//        // Data in block 1 is incorrect
//    }

	//EEPROM_voidSendDataByte(0xAE,0x1);
//
//	//EEPROM_voidReadDataByte(0xAE);
//
//	MDIO_vidSetPinDirection(PORT_A,2,OUTPUT);
//	MDIO_vidSetPinValue(PORT_A,2,EEPROM_u8ReadDataByte(0xAE));




//    DDRD=0XFF;
//    DDRA=0XFF;
//    System_Init(); // Initialize the system
//
//   // LCD_DisplayMessage("LCD Blink");
//    _delay_ms(1000);
//    // LCD opens and blinks twice
//    for (int i = 0; i < 2; i++) {
//        LCD_DisplayMessage(" ");
//        _delay_ms(500); // Delay for blinking
//        LCD_DisplayMessage("LCD Blink");
//        _delay_ms(500); // Delay for blinking
//    }
//
//    // Display "WELCOME!" letter after letter
//    LCD_Clear();
//    LCD_DisplayMessage("WELCOME!");
//
//    // Clear the text letter after letter
//    _delay_ms(2000); // Wait for 2 seconds
//    LCD_Clear();
//
//    // Display "TEMPERATURE CONTROL SYSTEM" all text at the same time
//    LCD_DisplayMessage("TEMPERATURE CONTROL SYSTEM");
//
//    // Clear all text
//    _delay_ms(2000); // Wait for 2 seconds
//    LCD_Clear();

    // Display "current temperature is :x"
//    char temperature_value = CurrentTemp ; // Replace 'X' with the actual temperature value
//    char temperature_message[20];
//    snprintf(temperature_message, sizeof(temperature_message), "Current temperature is: %c", temperature_value);
//    LCD_DisplayMessage(temperature_message);
//
//    // Display targeted temperature and options
//    LCD_Clear();
//    LCD_SendCommand(0x80); // Set cursor to the first line
//    LCD_DisplayMessage("Targeted Temp:");
//    LCD_SendCommand(0xC0); // Set cursor to the second line
//    LCD_DisplayMessage("1-Prev Temp 2-New Temp");
//
//    char key;
//    int Target_temp = 0; // Initialize the target temperature variable



	while(1)
	{
		//GetCurrentTemp();
		Start();
		global_u8Num1 = 0 ;
		global_u8Num2 = 0 ;
		global_u8DesiredTemp=0;
		global_u8Choose=0;

		/********* Wait User to enter any key to start new operation  ******/
		while ( ! (KPD_u8GetPressedKey()) );
//		CurrentTemp = ADC_u16ReadChannelSyn(channel7);
//		//float temperature = ((CurrentTemp * 5.0) / (1024.0 * 10.0))/2;
//        //float temperature = (float)CurrentTemp * (60.0 / 1023.0) - 10.0;
//        CurrentTemp = (CurrentTemp *0.5);
////
//        _delay_ms(100);


//        char temperature_value = CurrentTemp ; // Replace 'X' with the actual temperature value
//        char temperature_message[20];
//        snprintf(temperature_message, sizeof(temperature_message), "Current temperature is: %c", temperature_value);
//        LCD_DisplayMessage(temperature_message);
//
//        // Display targeted temperature and options
//        LCD_Clear();
//        LCD_SendCommand(0x80); // Set cursor to the first line
//        LCD_DisplayMessage("Targeted Temp:");
//        LCD_SendCommand(0xC0); // Set cursor to the second line
//        LCD_DisplayMessage("1-Prev Temp 2-New Temp");
//
//        char key;
//        int Target_temp = 0; // Initialize the target temperature variable
//
//		        key = KEYPAD_GetKey();
//		        if (key == '1') {
//		            // User chose option 1: Display previous temperature
//		            LCD_Clear();
//		            char prev_temp_message[20];
//		            snprintf(prev_temp_message, sizeof(prev_temp_message), "Previous Temp: %c", 'Y');
//		            LCD_DisplayMessage(prev_temp_message);
//		        } else if (key == '2') {
//		            // User chose option 2: Input new temperature
//		            LCD_Clear();
//		            LCD_DisplayMessage("Enter New Temp:");
//		            char new_temp[3] = {0};
//		            for (int i = 0; i < 2; i++) {
//		                while (1) {
//		                    key = KEYPAD_GetKey();
//		                    if (key >= '0' && key <= '9') {
//		                        new_temp[i] = key;
//		                        LCD_WriteChar(key);
//		                        break;
//		                    }
//		                }
//		            }
//		            int new_temp_value = atoi(new_temp);
//		            if (new_temp_value >= 10 && new_temp_value <= 70) {
//		                Target_temp = new_temp_value;
//		                LCD_Clear();
//		                LCD_DisplayMessage("New Temp Saved");
//		                _delay_ms(2000);
//		            } else {
//		                LCD_Clear();
//		                LCD_DisplayMessage("Invalid Temp!");
//		                _delay_ms(2000);
//		                LCD_Clear();
//		                LCD_DisplayMessage("Enter New Temp:");
//		            }
//		        } else if (key == 'c') {
//		            LCD_Clear();
//		            LCD_SendCommand(0x80);
//		            LCD_DisplayMessage("Change Temp? 1-Yes 2-No");
//		            while (1) {
//		                key = KEYPAD_GetKey();
//		                if (key == '1') {
//		                    LCD_Clear();
//		                    LCD_DisplayMessage("Enter New Temp:");
//		                    char new_temp[3] = {0};
//		                    for (int i = 0; i < 2; i++) {
//		                        while (1) {
//		                            key = KEYPAD_GetKey();
//		                            if (key >= '0' && key <= '9') {
//		                                new_temp[i] = key;
//		                                LCD_WriteChar(key);
//		                                break;
//		                            }
//		                        }
//		                    }
//		                    int new_temp_value = atoi(new_temp);
//		                    if (new_temp_value >= 10 && new_temp_value <= 70) {
//		                        Target_temp = new_temp_value;
//		                        LCD_Clear();
//		                        LCD_DisplayMessage("New Temp Saved");
//		                        _delay_ms(2000);
//		                    } else {
//		                        LCD_Clear();
//		                        LCD_DisplayMessage("Invalid Temp!");
//		                        _delay_ms(2000);
//		                        LCD_Clear();
//		                        LCD_DisplayMessage("Enter New Temp:");
//		                    }
//		                } else if (key == '2') {
//		                    // User chose not to change the temperature
//		                    break;
//		                }
//		            }
//		        }
//




//		EEPROM_voidSendDataByte(0xAE,0x1);
//
//		//EEPROM_voidReadDataByte(0xAE);
//
//		MDIO_vidSetPinDirection(PORT_A,2,OUTPUT);
//		MDIO_vidSetPinValue(PORT_A,2,EEPROM_u8ReadDataByte(0xAE));

//		EEPROM_voidSendDataByte(0xAE,0x1);
//
//		//EEPROM_voidReadDataByte(0xAE);
//
//		MDIO_vidSetPinDirection(PORT_A,1,OUTPUT);
//
//		u8 data = 0;
//		data = EEPROM_u8ReadDataByte(0xAE);
//
//		MDIO_vidSetPinValue(PORT_A,1,data);

//		CurrentTemp = ADC_u16ReadChannelSyn(channel7);
//		//float temperature = ((CurrentTemp * 5.0) / (1024.0 * 10.0))/2;
//        //float temperature = (float)CurrentTemp * (60.0 / 1023.0) - 10.0;
//        CurrentTemp = (CurrentTemp *0.5);
////
//        _delay_ms(100);

//		EEPROM_voidSendDataByte(0xAE,1);
//
//		//EEPROM_voidReadDataByte(0xAE);
//
//		MDIO_vidSetPinDirection(PORT_A,2,OUTPUT);
//		MDIO_vidSetPinValue(PORT_A,2,EEPROM_u8ReadDataByte(0xAE));

//		UART_VidSendData(CurrentTemp);
//		_delay_ms(100);
//
//		UART_VidSendData(DesiredTemp);
//		_delay_ms(100);
//
//		Operation=UART_VidReceiveData();
//		_delay_ms(100);



//		SPI_U8TranSceive(CurrentTemp);
//		_delay_ms(30);
//
//	    SPI_U8TranSceive(DesiredTemp);
//		_delay_ms(30);

//		MDIO_vidSetPinDirection(PORT_A,2,OUTPUT);
//		MDIO_vidSetPinDirection(PORT_A,3,OUTPUT);
//		MDIO_vidSetPinDirection(PORT_A,4,OUTPUT);
//
//		if(Operation == HEATING)
//		{
//			MDIO_vidSetPinValue(PORT_A,4,LOW);
//			MDIO_vidSetPinValue(PORT_A,3,LOW);
//			TOG_BIT(PORTA,2);
//			_delay_ms(500);
//		}
//		else if(Operation == COOLING)
//		{
//			MDIO_vidSetPinValue(PORT_A,4,LOW);
//			MDIO_vidSetPinValue(PORT_A,2,LOW);
//			TOG_BIT(PORTA,3);
//			_delay_ms(500);
//		}
//		else if(Operation == NoOperation)
//		{
//			MDIO_vidSetPinValue(PORT_A,2,LOW);
//			MDIO_vidSetPinValue(PORT_A,3,LOW);
//			TOG_BIT(PORTA,4);
//			_delay_ms(500);
//		}


//		ADC_VidInIt();
//
//		u16 temp = ADC_u16ReadChannelSyn(channel7);
//		temp = (temp*0.25);
//
//		if(temp<15 && temp>5){
//		MDIO_vidSetPinDirection(PORT_A,1,OUTPUT);
//		MDIO_vidSetPinValue(PORT_A,1,HIGH);
//		}

//		MDIO_vidSetPinDirection(PORT_C,0,INPUT);
//		MDIO_vidSetPinDirection(PORT_C,1,INPUT);
//				EEPROM_voidSendDataByte(0xAE,0x1);
//
//				//EEPROM_voidReadDataByte(0xAE);
//				_delay_ms(10);
//
//				MDIO_vidSetPinDirection(PORT_A,1,OUTPUT);
//				MDIO_vidSetPinValue(PORT_A,1,EEPROM_u8ReadDataByte(0xAE));

//		if(data1<data2)
//		{
//			buffer=SPI_U8TranSceive(0);
//			MDIO_vidSetPinDirection(PORT_A,0,OUTPUT);
//			MDIO_vidSetPinValue(PORT_A,0,HIGH);
////			_delay_ms(10);
//		}
//
//		else if(data1>data2)
//		{
//			buffer=SPI_U8TranSceive(1);
//			MDIO_vidSetPinDirection(PORT_A,1,OUTPUT);
//			MDIO_vidSetPinValue(PORT_A,1,HIGH);
//			//_delay_ms(10);
//		}
//		else
//		{
//			buffer=SPI_U8TranSceive(2);
//			MDIO_vidSetPinDirection(PORT_A,2,OUTPUT);
//			MDIO_vidSetPinValue(PORT_A,2,HIGH);
//			//_delay_ms(10);
//		}

//		_delay_ms(30);








//		if(buffer==1)
//		{
//			MDIO_vidSetPinDirection(PORT_A,0,OUTPUT);
//			MDIO_vidSetPinValue(PORT_A,0,HIGH);
//		}
//
//		MDIO_vidSetPinDirection(PORT_A,buffer,OUTPUT);
//		MDIO_vidSetPinValue(PORT_A,buffer,HIGH);


		//
//		TOG_BIT(data1,0);
//
//		_delay_ms(10);

//		if(data2==HIGH || data2==LOW)
//		MDIO_vidSetPinValue(PORT_A,0,data2);

//		SPI_U8TranSceive(data2);
//
//		_delay_ms(10);
//
//		TOG_BIT(data2,0);
//
//		_delay_ms(10);
	}
	return 0;
}
