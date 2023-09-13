################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Master_SPI.lss \

FLASH_IMAGE += \
Master_SPI.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Master_SPI.elf secondary-outputs

# Tool invocations
Master_SPI.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Master_SPI.map -mmcu=atmega32 -o "Master_SPI.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Master_SPI.lss: Master_SPI.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Master_SPI.elf  >"Master_SPI.lss"
	@echo 'Finished building: $@'
	@echo ' '

Master_SPI.hex: Master_SPI.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Master_SPI.elf  "Master_SPI.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Master_SPI.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Master_SPI.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Master_SPI.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
