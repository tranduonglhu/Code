################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Wire\src\utility\twi.c 

C_DEPS += \
.\libraries\Wire\src\utility\twi.c.d 

LINK_OBJ += \
.\libraries\Wire\src\utility\twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries\Wire\src\utility\twi.c.o: C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Wire\src\utility\twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\tools\avr-gcc\5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\cores\arduino" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\variants\eightanaloginputs" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Arduino-DS3231-master" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Arduino-LiquidCrystal-I2C" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Arduino-SerialCommand-master" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Low-Power-master" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\SimpleTimer-master" -I"C:\Eclipse\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.22\libraries\Wire\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


