################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/service/v2g_serviceClientStubs.c \
../src/service/v2g_serviceDataSerialization.c \
../src/service/v2g_serviceDataTypes.c \
../src/service/v2g_serviceDispatcher.c 

OBJS += \
./src/service/v2g_serviceClientStubs.o \
./src/service/v2g_serviceDataSerialization.o \
./src/service/v2g_serviceDataTypes.o \
./src/service/v2g_serviceDispatcher.o 

C_DEPS += \
./src/service/v2g_serviceClientStubs.d \
./src/service/v2g_serviceDataSerialization.d \
./src/service/v2g_serviceDataTypes.d \
./src/service/v2g_serviceDispatcher.d 


# Each subdirectory must supply rules for building sources it contributes
src/service/%.o: ../src/service/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec\appHandCodec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\appHandshake" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\transport" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\service" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\test" -O3 -Os -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


