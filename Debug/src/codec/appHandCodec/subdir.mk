################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/appHandCodec/appHandEXICoder.c \
../src/codec/appHandCodec/appHandEXIDecoder.c \
../src/codec/appHandCodec/appHandEXIEncoder.c \
../src/codec/appHandCodec/appHandNameTableEntries.c \
../src/codec/appHandCodec/appHandQNames.c 

OBJS += \
./src/codec/appHandCodec/appHandEXICoder.o \
./src/codec/appHandCodec/appHandEXIDecoder.o \
./src/codec/appHandCodec/appHandEXIEncoder.o \
./src/codec/appHandCodec/appHandNameTableEntries.o \
./src/codec/appHandCodec/appHandQNames.o 

C_DEPS += \
./src/codec/appHandCodec/appHandEXICoder.d \
./src/codec/appHandCodec/appHandEXIDecoder.d \
./src/codec/appHandCodec/appHandEXIEncoder.d \
./src/codec/appHandCodec/appHandNameTableEntries.d \
./src/codec/appHandCodec/appHandQNames.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/appHandCodec/%.o: ../src/codec/appHandCodec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/codec/appHandCodec" -I"../src/appHandshake" -I"../src/transport" -I"../src/service" -I"../src/test" -O0 -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


