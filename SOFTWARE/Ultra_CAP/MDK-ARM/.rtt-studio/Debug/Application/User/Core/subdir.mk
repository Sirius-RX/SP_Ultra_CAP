################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/CAN_receive.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/IIR_Filter.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/SEEKFREE_FONT.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/SEEKFREE_IPS114_SPI.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/adc.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/dma.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/fdcan.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/filter.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/fmac.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/function.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/gpio.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/hrtim.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/main.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/opamp.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/pid.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/power_ctrl.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/spi.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/stm32g4xx_hal_msp.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/stm32g4xx_it.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/tim.c \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/usart.c 

OBJS += \
./Application/User/Core/CAN_receive.o \
./Application/User/Core/IIR_Filter.o \
./Application/User/Core/SEEKFREE_FONT.o \
./Application/User/Core/SEEKFREE_IPS114_SPI.o \
./Application/User/Core/adc.o \
./Application/User/Core/dma.o \
./Application/User/Core/fdcan.o \
./Application/User/Core/filter.o \
./Application/User/Core/fmac.o \
./Application/User/Core/function.o \
./Application/User/Core/gpio.o \
./Application/User/Core/hrtim.o \
./Application/User/Core/main.o \
./Application/User/Core/opamp.o \
./Application/User/Core/pid.o \
./Application/User/Core/power_ctrl.o \
./Application/User/Core/spi.o \
./Application/User/Core/stm32g4xx_hal_msp.o \
./Application/User/Core/stm32g4xx_it.o \
./Application/User/Core/tim.o \
./Application/User/Core/usart.o 

C_DEPS += \
./Application/User/Core/CAN_receive.d \
./Application/User/Core/IIR_Filter.d \
./Application/User/Core/SEEKFREE_FONT.d \
./Application/User/Core/SEEKFREE_IPS114_SPI.d \
./Application/User/Core/adc.d \
./Application/User/Core/dma.d \
./Application/User/Core/fdcan.d \
./Application/User/Core/filter.d \
./Application/User/Core/fmac.d \
./Application/User/Core/function.d \
./Application/User/Core/gpio.d \
./Application/User/Core/hrtim.d \
./Application/User/Core/main.d \
./Application/User/Core/opamp.d \
./Application/User/Core/pid.d \
./Application/User/Core/power_ctrl.d \
./Application/User/Core/spi.d \
./Application/User/Core/stm32g4xx_hal_msp.d \
./Application/User/Core/stm32g4xx_it.d \
./Application/User/Core/tim.d \
./Application/User/Core/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/CAN_receive.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/CAN_receive.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/IIR_Filter.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/IIR_Filter.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/SEEKFREE_FONT.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/SEEKFREE_FONT.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/SEEKFREE_IPS114_SPI.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/SEEKFREE_IPS114_SPI.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/adc.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/adc.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/dma.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/dma.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/fdcan.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/fdcan.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/filter.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/filter.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/fmac.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/fmac.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/function.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/function.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/gpio.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/gpio.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/hrtim.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/hrtim.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/main.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/main.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/opamp.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/opamp.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/pid.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/pid.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/power_ctrl.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/power_ctrl.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/spi.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/spi.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/stm32g4xx_hal_msp.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/stm32g4xx_hal_msp.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/stm32g4xx_it.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/stm32g4xx_it.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/tim.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/tim.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
Application/User/Core/usart.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/usart.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

