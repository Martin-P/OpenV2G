################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/AbstractDecoderChannel.c \
../src/codec/AbstractEncoderChannel.c \
../src/codec/BitDecoderChannel.c \
../src/codec/BitEncoderChannel.c \
../src/codec/BitInputStream.c \
../src/codec/BitOutputStream.c \
../src/codec/ByteDecoderChannel.c \
../src/codec/ByteEncoderChannel.c \
../src/codec/ByteStream.c \
../src/codec/DynamicMemory.c \
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/MethodsBag.c \
../src/codec/StringNameTable.c \
../src/codec/StringValueTable.c \
../src/codec/UCSString.c \
../src/codec/main_codec.c \
../src/codec/v2gEXICoder.c \
../src/codec/v2gEXIDecoder.c \
../src/codec/v2gEXIEncoder.c \
../src/codec/v2gNameTableEntries.c \
../src/codec/v2gQNames.c 

OBJS += \
./src/codec/AbstractDecoderChannel.o \
./src/codec/AbstractEncoderChannel.o \
./src/codec/BitDecoderChannel.o \
./src/codec/BitEncoderChannel.o \
./src/codec/BitInputStream.o \
./src/codec/BitOutputStream.o \
./src/codec/ByteDecoderChannel.o \
./src/codec/ByteEncoderChannel.o \
./src/codec/ByteStream.o \
./src/codec/DynamicMemory.o \
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/MethodsBag.o \
./src/codec/StringNameTable.o \
./src/codec/StringValueTable.o \
./src/codec/UCSString.o \
./src/codec/main_codec.o \
./src/codec/v2gEXICoder.o \
./src/codec/v2gEXIDecoder.o \
./src/codec/v2gEXIEncoder.o \
./src/codec/v2gNameTableEntries.o \
./src/codec/v2gQNames.o 

C_DEPS += \
./src/codec/AbstractDecoderChannel.d \
./src/codec/AbstractEncoderChannel.d \
./src/codec/BitDecoderChannel.d \
./src/codec/BitEncoderChannel.d \
./src/codec/BitInputStream.d \
./src/codec/BitOutputStream.d \
./src/codec/ByteDecoderChannel.d \
./src/codec/ByteEncoderChannel.d \
./src/codec/ByteStream.d \
./src/codec/DynamicMemory.d \
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/MethodsBag.d \
./src/codec/StringNameTable.d \
./src/codec/StringValueTable.d \
./src/codec/UCSString.d \
./src/codec/main_codec.d \
./src/codec/v2gEXICoder.d \
./src/codec/v2gEXIDecoder.d \
./src/codec/v2gEXIEncoder.d \
./src/codec/v2gNameTableEntries.d \
./src/codec/v2gQNames.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/codec/appHandCodec" -I"../src/appHandshake" -I"../src/transport" -I"../src/service" -I"../src/test" -O0 -g3 -pedantic -pedantic-errors -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


