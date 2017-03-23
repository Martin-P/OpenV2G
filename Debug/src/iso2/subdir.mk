################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/iso2/iso2EXIDatatypes.c \
../src/iso2/iso2EXIDatatypesDecoder.c \
../src/iso2/iso2EXIDatatypesEncoder.c 

OBJS += \
./src/iso2/iso2EXIDatatypes.o \
./src/iso2/iso2EXIDatatypesDecoder.o \
./src/iso2/iso2EXIDatatypesEncoder.o 

C_DEPS += \
./src/iso2/iso2EXIDatatypes.d \
./src/iso2/iso2EXIDatatypesDecoder.d \
./src/iso2/iso2EXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/iso2/%.o: ../src/iso2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/iso1" -I"../src/iso2" -I"../src/xmldsig" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -O0 -g3 -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


