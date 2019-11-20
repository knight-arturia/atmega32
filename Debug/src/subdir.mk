################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/Mikrocontrolle.o \
../src/led.o \
../src/timer2.o 

C_SRCS += \
../src/Mikrocontrolle.c \
../src/led.c \
../src/timer0.c \
../src/timer2.c 

OBJS += \
./src/Mikrocontrolle.o \
./src/led.o \
./src/timer0.o \
./src/timer2.o 

C_DEPS += \
./src/Mikrocontrolle.d \
./src/led.d \
./src/timer0.d \
./src/timer2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/avr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


