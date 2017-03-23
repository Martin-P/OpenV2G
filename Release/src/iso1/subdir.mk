################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/iso1/iso1EXIDatatypes.c \
../src/iso1/iso1EXIDatatypesDecoder.c \
../src/iso1/iso1EXIDatatypesEncoder.c 

OBJS += \
./src/iso1/iso1EXIDatatypes.o \
./src/iso1/iso1EXIDatatypesDecoder.o \
./src/iso1/iso1EXIDatatypesEncoder.o 

C_DEPS += \
./src/iso1/iso1EXIDatatypes.d \
./src/iso1/iso1EXIDatatypesDecoder.d \
./src/iso1/iso1EXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/iso1/%.o: ../src/iso1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/iso1" -I"../src/iso2" -I"../src/xmldsig" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


