################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/misc.c \
../Src/stm32f4xx_gpio.c \
../Src/stm32f4xx_it.c \
../Src/stm32f4xx_rcc.c \
../Src/stm32f4xx_tim.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/main.o \
./Src/misc.o \
./Src/stm32f4xx_gpio.o \
./Src/stm32f4xx_it.o \
./Src/stm32f4xx_rcc.o \
./Src/stm32f4xx_tim.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/main.d \
./Src/misc.d \
./Src/stm32f4xx_gpio.d \
./Src/stm32f4xx_it.d \
./Src/stm32f4xx_rcc.d \
./Src/stm32f4xx_tim.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/ritik/Desktop/STM32CubeIDE/STM32 lib/inc_core" -I"C:/Users/ritik/Desktop/STM32CubeIDE/STM32 lib/inc_drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/misc.cyclo ./Src/misc.d ./Src/misc.o ./Src/misc.su ./Src/stm32f4xx_gpio.cyclo ./Src/stm32f4xx_gpio.d ./Src/stm32f4xx_gpio.o ./Src/stm32f4xx_gpio.su ./Src/stm32f4xx_it.cyclo ./Src/stm32f4xx_it.d ./Src/stm32f4xx_it.o ./Src/stm32f4xx_it.su ./Src/stm32f4xx_rcc.cyclo ./Src/stm32f4xx_rcc.d ./Src/stm32f4xx_rcc.o ./Src/stm32f4xx_rcc.su ./Src/stm32f4xx_tim.cyclo ./Src/stm32f4xx_tim.d ./Src/stm32f4xx_tim.o ./Src/stm32f4xx_tim.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su

.PHONY: clean-Src

