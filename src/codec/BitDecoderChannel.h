/*
 * Copyright (C) 2007-2010 Siemens AG
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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.3
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "EXITypes.h"

#ifndef BIT_DECODER_CHANNEL_H
#define BIT_DECODER_CHANNEL_H

/**
 * Decode a single boolean value. The value false is represented by the bit
 * 0, and the value true is represented by the bit 1.
 */
int decodeBoolean(bitstream_t* stream, int* b);

/**
 * Decodes and returns an n-bit unsigned integer.
 */
int decodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint8_t* uint8);

/**
 * Decode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int decodeUnsignedInteger32(bitstream_t* stream, uint32_t* uint32);

/**
 * Decode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int decodeUnsignedInteger64(bitstream_t* stream, uint64_t* uint64);

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger32(bitstream_t* stream, int32_t* int32);

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger64(bitstream_t* stream, int64_t* int64);

/**
 * Decode a Float datatype as two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int decodeFloat(bitstream_t* stream, float_me_t* f);

/**
 * Decode a length prefixed sequence of characters.
 */
int decodeString(bitstream_t* stream, string_ucs_t* s);

/**
 * Decode a length prefixed sequence of characters in the sense of string tables.
 * length == 0, local value partition hit
 * length == 1, global value partition hit
 * --> string literal is encoded as a String with the length incremented by two
 */
int decodeStringValue(bitstream_t* stream, string_ucs_t* s);


/**
 * Decode a sequence of characters according to a given length.
 */
int decodeCharacters(bitstream_t* stream, size_t len, uint32_t* chars);

/**
 * Decode a binary value as a length-prefixed sequence of octets.
 */
int decodeBinary(bitstream_t* stream, bytes_t* bytes);


#endif


#ifdef __cplusplus
}
#endif

