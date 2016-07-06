################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Program\ Files/eclipse/arduinoPlugin/libraries/Servo/1.1.1/src/samd/Servo.cpp 

LINK_OBJ += \
./libraries/Servo/src/samd/Servo.cpp.o 

CPP_DEPS += \
./libraries/Servo/src/samd/Servo.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Servo/src/samd/Servo.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/libraries/Servo/1.1.1/src/samd/Servo.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


