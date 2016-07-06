################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../evive.ino 

CPP_SRCS += \
../.ino.cpp \
../Adafruit_GFX.cpp \
../Adafruit_ST7735.cpp \
../action.cpp \
../adc_ade7912.cpp \
../button.cpp \
../evive.cpp \
../motor.cpp \
../navkey.cpp \
../potentiometer.cpp \
../screen.cpp \
../servoControl.cpp \
../setPinMode.cpp \
../slideSwitch.cpp \
../status.cpp \
../stepper.cpp 

C_SRCS += \
../glcdfont.c 

C_DEPS += \
./glcdfont.c.d 

LINK_OBJ += \
./.ino.cpp.o \
./Adafruit_GFX.cpp.o \
./Adafruit_ST7735.cpp.o \
./action.cpp.o \
./adc_ade7912.cpp.o \
./button.cpp.o \
./evive.cpp.o \
./glcdfont.c.o \
./motor.cpp.o \
./navkey.cpp.o \
./potentiometer.cpp.o \
./screen.cpp.o \
./servoControl.cpp.o \
./setPinMode.cpp.o \
./slideSwitch.cpp.o \
./status.cpp.o \
./stepper.cpp.o 

INO_DEPS += \
./evive.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./Adafruit_GFX.cpp.d \
./Adafruit_ST7735.cpp.d \
./action.cpp.d \
./adc_ade7912.cpp.d \
./button.cpp.d \
./evive.cpp.d \
./motor.cpp.d \
./navkey.cpp.d \
./potentiometer.cpp.d \
./screen.cpp.d \
./servoControl.cpp.d \
./setPinMode.cpp.d \
./slideSwitch.cpp.d \
./status.cpp.d \
./stepper.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_GFX.cpp.o: ../Adafruit_GFX.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Adafruit_ST7735.cpp.o: ../Adafruit_ST7735.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

action.cpp.o: ../action.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

adc_ade7912.cpp.o: ../adc_ade7912.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

button.cpp.o: ../button.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

evive.cpp.o: ../evive.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

evive.o: ../evive.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

glcdfont.c.o: ../glcdfont.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

motor.cpp.o: ../motor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

navkey.cpp.o: ../navkey.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

potentiometer.cpp.o: ../potentiometer.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

screen.cpp.o: ../screen.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

servoControl.cpp.o: ../servoControl.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

setPinMode.cpp.o: ../setPinMode.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

slideSwitch.cpp.o: ../slideSwitch.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

status.cpp.o: ../status.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

stepper.cpp.o: ../stepper.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


