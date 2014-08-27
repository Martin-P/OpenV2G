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
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/MethodsBag.c \
../src/codec/v2gEXIDatatypes.c \
../src/codec/v2gEXIDatatypesDecoder.c \
../src/codec/v2gEXIDatatypesEncoder.c 

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
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/MethodsBag.o \
./src/codec/v2gEXIDatatypes.o \
./src/codec/v2gEXIDatatypesDecoder.o \
./src/codec/v2gEXIDatatypesEncoder.o 

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
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/MethodsBag.d \
./src/codec/v2gEXIDatatypes.d \
./src/codec/v2gEXIDatatypesDecoder.d \
./src/codec/v2gEXIDatatypesEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


