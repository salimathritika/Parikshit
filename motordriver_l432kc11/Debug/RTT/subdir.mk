################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTT/SEGGER_RTT.c \
../RTT/SEGGER_RTT_Syscalls_GCC.c 

OBJS += \
./RTT/SEGGER_RTT.o \
./RTT/SEGGER_RTT_Syscalls_GCC.o 

C_DEPS += \
./RTT/SEGGER_RTT.d \
./RTT/SEGGER_RTT_Syscalls_GCC.d 


# Each subdirectory must supply rules for building sources it contributes
RTT/%.o RTT/%.su RTT/%.cyclo: ../RTT/%.c RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Core/Config -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ritik/Desktop/STM32CubeIDE/motordriver_l432kc11/User_Defined" -I"C:/Users/ritik/Desktop/STM32CubeIDE/motordriver_l432kc11/RTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTT

clean-RTT:
	-$(RM) ./RTT/SEGGER_RTT.cyclo ./RTT/SEGGER_RTT.d ./RTT/SEGGER_RTT.o ./RTT/SEGGER_RTT.su ./RTT/SEGGER_RTT_Syscalls_GCC.cyclo ./RTT/SEGGER_RTT_Syscalls_GCC.d ./RTT/SEGGER_RTT_Syscalls_GCC.o ./RTT/SEGGER_RTT_Syscalls_GCC.su

.PHONY: clean-RTT

