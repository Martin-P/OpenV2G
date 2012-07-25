################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/test/evse_server.c \
../src/test/evse_serviceMethods.c \
../src/test/main.c \
../src/test/main_codec.c \
../src/test/pev_service.c \
../src/test/serviceClientDataTransmitter.c 

OBJS += \
./src/test/evse_server.o \
./src/test/evse_serviceMethods.o \
./src/test/main.o \
./src/test/main_codec.o \
./src/test/pev_service.o \
./src/test/serviceClientDataTransmitter.o 

C_DEPS += \
./src/test/evse_server.d \
./src/test/evse_serviceMethods.d \
./src/test/main.d \
./src/test/main_codec.d \
./src/test/pev_service.d \
./src/test/serviceClientDataTransmitter.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/codec/appHandCodec" -I"../src/appHandshake" -I"../src/transport" -I"../src/service" -I"../src/test" -O0 -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


