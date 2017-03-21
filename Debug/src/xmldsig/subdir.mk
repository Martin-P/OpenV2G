################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/xmldsig/xmldsigEXIDatatypes.c \
../src/xmldsig/xmldsigEXIDatatypesDecoder.c \
../src/xmldsig/xmldsigEXIDatatypesEncoder.c 

OBJS += \
./src/xmldsig/xmldsigEXIDatatypes.o \
./src/xmldsig/xmldsigEXIDatatypesDecoder.o \
./src/xmldsig/xmldsigEXIDatatypesEncoder.o 

C_DEPS += \
./src/xmldsig/xmldsigEXIDatatypes.d \
./src/xmldsig/xmldsigEXIDatatypesDecoder.d \
./src/xmldsig/xmldsigEXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/xmldsig/%.o: ../src/xmldsig/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/xmldsig" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -O0 -g3 -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


