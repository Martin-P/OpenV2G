################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/appHandshake/appHand_DataDeserialization.c \
../src/appHandshake/appHand_DataSerialization.c \
../src/appHandshake/appHand_dataTypes.c 

OBJS += \
./src/appHandshake/appHand_DataDeserialization.o \
./src/appHandshake/appHand_DataSerialization.o \
./src/appHandshake/appHand_dataTypes.o 

C_DEPS += \
./src/appHandshake/appHand_DataDeserialization.d \
./src/appHandshake/appHand_DataSerialization.d \
./src/appHandshake/appHand_dataTypes.d 


# Each subdirectory must supply rules for building sources it contributes
src/appHandshake/%.o: ../src/appHandshake/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\appHandshake" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec\appHandCodec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\transport" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\service" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\test" -O0 -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


