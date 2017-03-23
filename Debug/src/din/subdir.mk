################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/din/dinEXIDatatypes.c \
../src/din/dinEXIDatatypesDecoder.c \
../src/din/dinEXIDatatypesEncoder.c 

OBJS += \
./src/din/dinEXIDatatypes.o \
./src/din/dinEXIDatatypesDecoder.o \
./src/din/dinEXIDatatypesEncoder.o 

C_DEPS += \
./src/din/dinEXIDatatypes.d \
./src/din/dinEXIDatatypesDecoder.d \
./src/din/dinEXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/din/%.o: ../src/din/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/iso1" -I"../src/iso2" -I"../src/xmldsig" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -O0 -g3 -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


