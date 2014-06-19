################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/appHandshake/appHandEXIDatatypes.c \
../src/appHandshake/appHandEXIDatatypesDecoder.c \
../src/appHandshake/appHandEXIDatatypesEncoder.c 

OBJS += \
./src/appHandshake/appHandEXIDatatypes.o \
./src/appHandshake/appHandEXIDatatypesDecoder.o \
./src/appHandshake/appHandEXIDatatypesEncoder.o 

C_DEPS += \
./src/appHandshake/appHandEXIDatatypes.d \
./src/appHandshake/appHandEXIDatatypesDecoder.d \
./src/appHandshake/appHandEXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/appHandshake/%.o: ../src/appHandshake/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -Os -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


