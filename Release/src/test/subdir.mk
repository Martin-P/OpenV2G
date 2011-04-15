################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/test/main.c \
../src/test/main_codec.c \
../src/test/main_service.c \
../src/test/v2g_server.c \
../src/test/v2g_serviceClientDataTransmitter.c \
../src/test/v2g_serviceMethods.c 

OBJS += \
./src/test/main.o \
./src/test/main_codec.o \
./src/test/main_service.o \
./src/test/v2g_server.o \
./src/test/v2g_serviceClientDataTransmitter.o \
./src/test/v2g_serviceMethods.o 

C_DEPS += \
./src/test/main.d \
./src/test/main_codec.d \
./src/test/main_service.d \
./src/test/v2g_server.d \
./src/test/v2g_serviceClientDataTransmitter.d \
./src/test/v2g_serviceMethods.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\transport" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\service" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\test" -O3 -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


