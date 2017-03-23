################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/BitInputStream.c \
../src/codec/BitOutputStream.c \
../src/codec/ByteStream.c \
../src/codec/DecoderChannel.c \
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/EncoderChannel.c \
../src/codec/MethodsBag.c 

OBJS += \
./src/codec/BitInputStream.o \
./src/codec/BitOutputStream.o \
./src/codec/ByteStream.o \
./src/codec/DecoderChannel.o \
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/EncoderChannel.o \
./src/codec/MethodsBag.o 

C_DEPS += \
./src/codec/BitInputStream.d \
./src/codec/BitOutputStream.d \
./src/codec/ByteStream.d \
./src/codec/DecoderChannel.d \
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/EncoderChannel.d \
./src/codec/MethodsBag.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/din" -I"../src/iso1" -I"../src/iso2" -I"../src/xmldsig" -I"../src/appHandshake" -I"../src/transport" -I"../src/test" -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


