################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_defined/ocpc.c 

OBJS += \
./User_defined/ocpc.o 

C_DEPS += \
./User_defined/ocpc.d 


# Each subdirectory must supply rules for building sources it contributes
User_defined/%.o User_defined/%.su: ../User_defined/%.c User_defined/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H725xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ritik/Desktop/STM32CubeIDE/OCPC/User_defined" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_defined

clean-User_defined:
	-$(RM) ./User_defined/ocpc.d ./User_defined/ocpc.o ./User_defined/ocpc.su

.PHONY: clean-User_defined

