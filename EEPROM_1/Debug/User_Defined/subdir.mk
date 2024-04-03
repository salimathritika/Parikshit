################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_Defined/eeprom.c 

OBJS += \
./User_Defined/eeprom.o 

C_DEPS += \
./User_Defined/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
User_Defined/%.o User_Defined/%.su: ../User_Defined/%.c User_Defined/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ritik/Desktop/STM32CubeIDE/EEPROM_1/User_Defined" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_Defined

clean-User_Defined:
	-$(RM) ./User_Defined/eeprom.d ./User_Defined/eeprom.o ./User_Defined/eeprom.su

.PHONY: clean-User_Defined

