################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/BitDecoderChannel.c \
../src/codec/BitEncoderChannel.c \
../src/codec/BitInputStream.c \
../src/codec/BitOutputStream.c \
../src/codec/ByteStream.c \
../src/codec/EXICoder.c \
../src/codec/EXIDecoder.c \
../src/codec/EXIEncoder.c \
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/StringTable.c \
../src/codec/StringTableEntries.c \
../src/codec/UCSString.c 

OBJS += \
./src/codec/BitDecoderChannel.o \
./src/codec/BitEncoderChannel.o \
./src/codec/BitInputStream.o \
./src/codec/BitOutputStream.o \
./src/codec/ByteStream.o \
./src/codec/EXICoder.o \
./src/codec/EXIDecoder.o \
./src/codec/EXIEncoder.o \
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/StringTable.o \
./src/codec/StringTableEntries.o \
./src/codec/UCSString.o 

C_DEPS += \
./src/codec/BitDecoderChannel.d \
./src/codec/BitEncoderChannel.d \
./src/codec/BitInputStream.d \
./src/codec/BitOutputStream.d \
./src/codec/ByteStream.d \
./src/codec/EXICoder.d \
./src/codec/EXIDecoder.d \
./src/codec/EXIEncoder.d \
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/StringTable.d \
./src/codec/StringTableEntries.d \
./src/codec/UCSString.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\codec" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\transport" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\service" -I"D:\Data\MCHN4240\workspace_c\OpenV2G\trunk\src\test" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


