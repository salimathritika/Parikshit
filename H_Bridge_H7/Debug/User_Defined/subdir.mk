################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_Defined/hbridge.c 

OBJS += \
./User_Defined/hbridge.o 

C_DEPS += \
./User_Defined/hbridge.d 


# Each subdirectory must supply rules for building sources it contributes
User_Defined/%.o User_Defined/%.su User_Defined/%.cyclo: ../User_Defined/%.c User_Defined/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H725xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ritik/Desktop/STM32CubeIDE/H_Bridge_H7/User_Defined" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_Defined

clean-User_Defined:
	-$(RM) ./User_Defined/hbridge.cyclo ./User_Defined/hbridge.d ./User_Defined/hbridge.o ./User_Defined/hbridge.su

.PHONY: clean-User_Defined

