################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/appHandCodec/appHand_EXIDecoder.c \
../src/codec/appHandCodec/appHand_EXIEncoder.c \
../src/codec/appHandCodec/appHand_NameTableEntries.c 

OBJS += \
./src/codec/appHandCodec/appHand_EXIDecoder.o \
./src/codec/appHandCodec/appHand_EXIEncoder.o \
./src/codec/appHandCodec/appHand_NameTableEntries.o 

C_DEPS += \
./src/codec/appHandCodec/appHand_EXIDecoder.d \
./src/codec/appHandCodec/appHand_EXIEncoder.d \
./src/codec/appHandCodec/appHand_NameTableEntries.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/appHandCodec/%.o: ../src/codec/appHandCodec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\appHandshake" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec\appHandCodec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\transport" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\service" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\test" -O0 -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


