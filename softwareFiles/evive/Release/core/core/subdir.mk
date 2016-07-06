################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/CDC.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial0.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial1.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial2.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial3.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/IPAddress.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/PluggableUSB.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Print.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Stream.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Tone.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/USBCore.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WMath.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WString.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/abi.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/main.cpp \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/new.cpp 

S_UPPER_SRCS += \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_pulse.S 

C_SRCS += \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WInterrupts.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/hooks.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_analog.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_digital.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_pulse.c \
C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_shift.c 

C_DEPS += \
./core/WInterrupts.c.d \
./core/hooks.c.d \
./core/wiring.c.d \
./core/wiring_analog.c.d \
./core/wiring_digital.c.d \
./core/wiring_pulse.c.d \
./core/wiring_shift.c.d 

AR_OBJ += \
./core/CDC.cpp.o \
./core/HardwareSerial.cpp.o \
./core/HardwareSerial0.cpp.o \
./core/HardwareSerial1.cpp.o \
./core/HardwareSerial2.cpp.o \
./core/HardwareSerial3.cpp.o \
./core/IPAddress.cpp.o \
./core/PluggableUSB.cpp.o \
./core/Print.cpp.o \
./core/Stream.cpp.o \
./core/Tone.cpp.o \
./core/USBCore.cpp.o \
./core/WInterrupts.c.o \
./core/WMath.cpp.o \
./core/WString.cpp.o \
./core/abi.cpp.o \
./core/hooks.c.o \
./core/main.cpp.o \
./core/new.cpp.o \
./core/wiring.c.o \
./core/wiring_analog.c.o \
./core/wiring_digital.c.o \
./core/wiring_pulse.S.o \
./core/wiring_pulse.c.o \
./core/wiring_shift.c.o 

S_UPPER_DEPS += \
./core/wiring_pulse.S.d 

CPP_DEPS += \
./core/CDC.cpp.d \
./core/HardwareSerial.cpp.d \
./core/HardwareSerial0.cpp.d \
./core/HardwareSerial1.cpp.d \
./core/HardwareSerial2.cpp.d \
./core/HardwareSerial3.cpp.d \
./core/IPAddress.cpp.d \
./core/PluggableUSB.cpp.d \
./core/Print.cpp.d \
./core/Stream.cpp.d \
./core/Tone.cpp.d \
./core/USBCore.cpp.d \
./core/WMath.cpp.d \
./core/WString.cpp.d \
./core/abi.cpp.d \
./core/main.cpp.d \
./core/new.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
core/CDC.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/CDC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/HardwareSerial.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/HardwareSerial0.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial0.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/HardwareSerial1.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial1.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/HardwareSerial2.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial2.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/HardwareSerial3.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/HardwareSerial3.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/IPAddress.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/IPAddress.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/PluggableUSB.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/PluggableUSB.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/Print.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Print.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/Stream.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Stream.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/Tone.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/Tone.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/USBCore.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/USBCore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/WInterrupts.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WInterrupts.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/WMath.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WMath.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/WString.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/WString.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/abi.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/abi.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/hooks.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/hooks.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/main.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/main.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/new.cpp.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/new.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring_analog.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_analog.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring_digital.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_digital.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring_pulse.S.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_pulse.S
	@echo 'Building file: $<'
	@echo 'Starting S compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -x assembler-with-cpp -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring_pulse.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_pulse.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

core/wiring_shift.c.o: C:/Program\ Files/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.10/cores/arduino/wiring_shift.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -c -g -Os -std=gnu11 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\cores\arduino" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\variants\mega" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.10\libraries\SPI\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Servo\1.1.1\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


