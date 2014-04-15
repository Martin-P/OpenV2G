################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/appHandshake/appHand_dataDeserialization.c \
../src/appHandshake/appHand_dataSerialization.c \
../src/appHandshake/appHand_dataTypes.c 

OBJS += \
./src/appHandshake/appHand_dataDeserialization.o \
./src/appHandshake/appHand_dataSerialization.o \
./src/appHandshake/appHand_dataTypes.o 

C_DEPS += \
./src/appHandshake/appHand_dataDeserialization.d \
./src/appHandshake/appHand_dataSerialization.d \
./src/appHandshake/appHand_dataTypes.d 


# Each subdirectory must supply rules for building sources it contributes
src/appHandshake/%.o: ../src/appHandshake/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/codec/appHandCodec" -I"../src/appHandshake" -I"../src/transport" -I"../src/service" -I"../src/test" -O3 -Os -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


