################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cpal_hal.c \
../Src/cpal_i2c.c \
../Src/cpal_i2c_hal_stm32f4xx.c \
../Src/cpal_usercallback.c \
../Src/main.c \
../Src/misc.c \
../Src/stm32f4xx_adc.c \
../Src/stm32f4xx_dma.c \
../Src/stm32f4xx_gpio.c \
../Src/stm32f4xx_i2c.c \
../Src/stm32f4xx_rcc.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/cpal_hal.o \
./Src/cpal_i2c.o \
./Src/cpal_i2c_hal_stm32f4xx.o \
./Src/cpal_usercallback.o \
./Src/main.o \
./Src/misc.o \
./Src/stm32f4xx_adc.o \
./Src/stm32f4xx_dma.o \
./Src/stm32f4xx_gpio.o \
./Src/stm32f4xx_i2c.o \
./Src/stm32f4xx_rcc.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/cpal_hal.d \
./Src/cpal_i2c.d \
./Src/cpal_i2c_hal_stm32f4xx.d \
./Src/cpal_usercallback.d \
./Src/main.d \
./Src/misc.d \
./Src/stm32f4xx_adc.d \
./Src/stm32f4xx_dma.d \
./Src/stm32f4xx_gpio.d \
./Src/stm32f4xx_i2c.d \
./Src/stm32f4xx_rcc.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/ritik/Desktop/STM32CubeIDE/CPAL lib/inc_core" -I"C:/Users/ritik/Desktop/STM32CubeIDE/CPAL lib/inc_drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/cpal_hal.d ./Src/cpal_hal.o ./Src/cpal_hal.su ./Src/cpal_i2c.d ./Src/cpal_i2c.o ./Src/cpal_i2c.su ./Src/cpal_i2c_hal_stm32f4xx.d ./Src/cpal_i2c_hal_stm32f4xx.o ./Src/cpal_i2c_hal_stm32f4xx.su ./Src/cpal_usercallback.d ./Src/cpal_usercallback.o ./Src/cpal_usercallback.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/misc.d ./Src/misc.o ./Src/misc.su ./Src/stm32f4xx_adc.d ./Src/stm32f4xx_adc.o ./Src/stm32f4xx_adc.su ./Src/stm32f4xx_dma.d ./Src/stm32f4xx_dma.o ./Src/stm32f4xx_dma.su ./Src/stm32f4xx_gpio.d ./Src/stm32f4xx_gpio.o ./Src/stm32f4xx_gpio.su ./Src/stm32f4xx_i2c.d ./Src/stm32f4xx_i2c.o ./Src/stm32f4xx_i2c.su ./Src/stm32f4xx_rcc.d ./Src/stm32f4xx_rcc.o ./Src/stm32f4xx_rcc.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su

.PHONY: clean-Src

