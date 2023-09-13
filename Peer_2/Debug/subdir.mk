################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EEP_Prog.c \
../SPI_progarm.c \
../TWI_Prog.c \
../Timer_program.c \
../UART_program.c \
../dio.c \
../gie.c \
../main.c 

OBJS += \
./EEP_Prog.o \
./SPI_progarm.o \
./TWI_Prog.o \
./Timer_program.o \
./UART_program.o \
./dio.o \
./gie.o \
./main.o 

C_DEPS += \
./EEP_Prog.d \
./SPI_progarm.d \
./TWI_Prog.d \
./Timer_program.d \
./UART_program.d \
./dio.d \
./gie.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


