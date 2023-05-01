################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/system_stm32g4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32g4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32g4xx.o: D:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Src/system_stm32g4xx.c
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -ffunction-sections -fdata-sections -Wall  -g -gdwarf-2 -DUSE_HAL_DRIVER -DSTM32G474xx -D__CC_ARM -D__FPU_PRESENT = 1U -DARM_MATH_CM4 -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Core/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Device/ST/STM32G4xx/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/Include -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP -ID:/RT-ThreadStudio/workspace/Ultra_CAP/Drivers/CMSIS/DSP/Include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

