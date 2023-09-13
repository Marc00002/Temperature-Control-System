################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../KPD_Prog.c \
../LCD_Prog.c \
../SPI_progarm.c \
../UART_program.c \
../dio.c \
../main.c 

OBJS += \
./ADC_program.o \
./KPD_Prog.o \
./LCD_Prog.o \
./SPI_progarm.o \
./UART_program.o \
./dio.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./KPD_Prog.d \
./LCD_Prog.d \
./SPI_progarm.d \
./UART_program.d \
./dio.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


