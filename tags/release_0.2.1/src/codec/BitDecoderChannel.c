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
 * @version 0.2.1
 * @contact Joerg.Heuer@siemens.com
 *
 * Bit decoding functionalities
 *
 ********************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "BitDecoderChannel.h"
#include "BitInputStream.h"
#include "EXITypes.h"

#ifndef BIT_DECODER_CHANNEL_C
#define BIT_DECODER_CHANNEL_C

int decode(bitstream_t* stream, uint8_t* b) {
	return readBits(stream, 8, b);
}

int decodeBoolean(bitstream_t* stream, int* b) {
	uint8_t ub;
	int errn = readBits(stream, 1, &ub);
	*b = (ub == 0) ? 0 : 1;
	return errn;
}

int decodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint8_t* uint8) {
	if (nbits == 0) {
		*uint8 = 0;
		return 0;
	} else {
		return readBits(stream, nbits, uint8);
	}
}

int decodeUnsignedInteger32(bitstream_t* stream, uint32_t* uint32) {
	/* 0XXXXXXX ... 1XXXXXXX 1XXXXXXX */
	unsigned int mShift = 0;
	int errn = 0;
	uint8_t b;
	*uint32 = 0;

	do {
		/* 1. Read the next octet */
		errn = decode(stream, &b);
		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint32 += (b & 127) << mShift;
		/* 3. Multiply the multiplier by 128 */
		mShift += 7;
		/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn >= 0 && (b >> 7) == 1);

	return errn;
}

/**
 * Decode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int decodeUnsignedInteger64(bitstream_t* stream, uint64_t* uint64) {
	unsigned int mShift = 0;
	int errn = 0;
	uint8_t b;
	*uint64 = 0L;

	do {
		errn = decode(stream, &b);
		*uint64 += ((uint64_t) (b & 127)) << mShift;
		mShift += 7;
	} while (errn >= 0 && (b >> 7) == 1);

	return errn;
}

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger32(bitstream_t* stream, int32_t* int32) {
	int b;
	uint32_t uint32;
	int errn = decodeBoolean(stream, &b);

	if (errn < 0) {
		return errn;
	}

	if (b) {
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		errn = decodeUnsignedInteger32(stream, &uint32);
		*int32 = -(uint32 + 1);
	} else {
		/* positive */
		errn = decodeUnsignedInteger32(stream, &uint32);
		*int32 = (int32_t)(uint32);
	}

	return errn;
}

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger64(bitstream_t* stream, int64_t* int64) {
	int b;
	uint64_t uint64;
	int errn = decodeBoolean(stream, &b);

	if (errn < 0) {
		return errn;
	}

	if (b) {
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		errn = decodeUnsignedInteger64(stream, &uint64);
		*int64 = -(uint64 + 1);
	} else {
		/* positive */
		errn = decodeUnsignedInteger64(stream, &uint64);
		*int64 = (int64_t)(uint64);
	}

	return errn;
}

/**
 * Decode a Float datatype as two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int decodeFloat(bitstream_t* stream, float_me_t* f) {
	int errn = decodeInteger64(stream, &f->mantissa);
	if (errn < 0) {
		return errn;
	}
	return decodeInteger32(stream, &f->exponent);
}

/**
 * Decode a sequence of characters for a given length.
 */
int decodeStringOnly(bitstream_t* stream, size_t len, string_ucs_t* s) {
	decodeCharacters(stream, len, s->codepoints);
	s->len = len;
	return 0;
}

/**
 * Decode a length prefixed sequence of characters.
 */
int decodeString(bitstream_t* stream, string_ucs_t* s) {
	int errn = decodeUnsignedInteger32(stream, &s->len);
	if (errn < 0) {
		return errn;
	}
	return decodeStringOnly(stream, s->len, s);
}

int decodeStringValue(bitstream_t* stream, string_ucs_t* s) {
	int errn = decodeUnsignedInteger32(stream, &s->len);
	if (errn < 0) {
		return errn;
	}

	switch (s->len) {
	case 0:
		/* local value partition */
		printf("[ERROR] String local value partition hit not supported \n");
		return -2;
	case 1:
		/* found in global value partition */
		printf("[ERROR] String global value partition hit not supported \n");
		return -3;
	default:
		/* not found in global value (and local value) partition
		 * ==> string literal is encoded as a String with the length
		 * incremented by two */
		return decodeStringOnly(stream, ((s->len) - 2), s);
		/* After encoding the string value, it is added to both the
		 * associated "local" value string table partition and the global
		 * value string table partition */
		/* addValue(context, value); */
	}
}

/**
 * Decode a sequence of characters according to a given length.
 * Each character is represented by its UCS [ISO/IEC 10646]
 * code point encoded as an Unsigned Integer
 */
int decodeCharacters(bitstream_t* stream, size_t len, uint32_t* chars) {
	unsigned int i;
	int errn = 0;
	for (i = 0; i < len && errn >= 0; i++) {
		errn = decodeUnsignedInteger32(stream, &chars[i]);
	}

	return errn;
}

/**
 * Decode a binary value as a length-prefixed sequence of octets.
 */
int decodeBinary(bitstream_t* stream, bytes_t* bytes) {
	unsigned int i;
	int errn = decodeUnsignedInteger32(stream, &bytes->len);
	if (errn < 0) {
		return errn;
	}

	for (i = 0; i < bytes->len && errn >= 0; i++) {
		errn = decode(stream, &bytes->data[i]);
	}

	return errn;
}

#endif

