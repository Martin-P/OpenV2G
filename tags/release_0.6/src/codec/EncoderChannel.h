/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.6 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

#include "EXITypes.h"

#ifndef ENCODER_CHANNEL_H
#define ENCODER_CHANNEL_H

/**
 * Encode a byte value.
 */
int encode(bitstream_t* stream, uint8_t b);

/**
 * Encode a single boolean value. A false value is encoded as 0 and true
 * value is encode as 1.
 */
int encodeBoolean(bitstream_t* stream, int b);


/**
 * Encode n-bit unsigned integer. The n least significant bits of parameter
 * b starting with the most significant, i.e. from left to right.
 */
int encodeNBitUnsignedInteger(bitstream_t* stream, uint16_t nbits, uint32_t val);

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger(bitstream_t* stream, integer_t* iv);


/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger32(bitstream_t* stream, uint32_t n);

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger64(bitstream_t* stream, uint64_t n);


/**
 * Encode an arbitrary precision integer using a sign boolean followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger(bitstream_t* stream, integer_t* iv);

/**
 * Encode an arbitrary precision integer using a sign boolean followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger32(bitstream_t* stream, int32_t n);

/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger64(bitstream_t* stream, int64_t n);

/**
 * Encode a Float datatype as two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int encodeFloat(bitstream_t* stream, float_me_t* f);

/**
 * Encode a decimal represented as a Boolean sign followed by two Unsigned
 * Integers. A sign value of zero (0) is used to represent positive Decimal
 * values and a sign value of one (1) is used to represent negative Decimal
 * values The first Integer represents the integral portion of the Decimal
 * value. The second positive integer represents the fractional portion of
 * the decimal with the digits in reverse order to preserve leading zeros.
 */
int encodeDecimal(bitstream_t* stream, decimal_t* d);

/**
 * Encode a length prefixed sequence of characters.
 */
int encodeString(bitstream_t* stream, string_ucs_t* string);
int encodeASCII(bitstream_t* stream, const char* ascii);

/**
 * Encode a length prefixed sequence of characters in the sense of string tables
 */
int encodeStringValue(bitstream_t* stream, string_ucs_t* string);

/**
 * Restricted character set
 */
int encodeRCSStringValue(bitstream_t* stream, rcs_t* rcs, string_ucs_t* string);

/**
 * Encode a sequence of characters according to a given length.
 * Each character is represented by its UCS [ISO/IEC 10646]
 * code point encoded as an Unsigned Integer
 */
int encodeUCSCharacters(bitstream_t* stream, uint32_t* chars, uint16_t len);

int encodeASCIICharacters(bitstream_t* stream, const char* chars, uint16_t len);

/**
 * Encode a binary value as a length-prefixed sequence of octets.
 */
int encodeBinary(bitstream_t* stream, bytes_t* bytes);

/**
 * Encode a datetime representation which is a sequence of values
 * representing the individual components of the Date-Time
 */
int encodeDateTime(bitstream_t* stream, datetime_t* datetime);

/**
 * Flush underlying bit output stream
 */
int encodeFinish(bitstream_t* stream);


#endif


#ifdef __cplusplus
}
#endif








