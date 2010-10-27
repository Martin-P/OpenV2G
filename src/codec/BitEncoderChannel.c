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
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "BitEncoderChannel.h"
#include "BitOutputStream.h"
#include "EXITypes.h"

#ifndef BIT_ENCODER_CHANNEL_C
#define BIT_ENCODER_CHANNEL_C

/**
 * Returns the least number of 7 bit-blocks that is needed to represent the
 * int <param>n</param>. Returns 1 if <param>n</param> is 0.
 *
 * @param n
 *            integer value
 *
 */
uint8_t numberOf7BitBlocksToRepresent(int n) {
	/* assert (n >= 0); */

	/* 7 bits */
	if (n < 128) {
		return 1;
	}
	/* 14 bits */
	else if (n < 16384) {
		return 2;
	}
	/* 21 bits */
	else if (n < 2097152) {
		return 3;
	}
	/* 28 bits */
	else if (n < 268435456) {
		return 4;
	}
	/* 35 bits */
	else {
		/* int, 32 bits */
		return 5;
	}
}


int encode(bitstream_t* stream, uint8_t b) {
	return writeBits(stream, 8, b);
}

/**
 * Encode a single boolean value. A false value is encoded as bit 0 and true
 * value is encode as bit 1.
 */
int encodeBoolean(bitstream_t* stream, int b) {
	uint8_t val = b ? 1 : 0;
	return writeBits(stream, 1, val);
}


/**
 * Encode n-bit unsigned integer. The n least significant bits of parameter
 * b starting with the most significant, i.e. from left to right.
 */
int encodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint8_t val)  {
	return writeBits(stream, nbits, val);
}




/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger32(bitstream_t* stream, uint32_t n) {
	int errn = 0;
	if (n < 128) {
		/* write byte as is */
		errn = encode(stream, (uint8_t)n);
	} else {
		uint8_t n7BitBlocks = numberOf7BitBlocksToRepresent(n);

		switch (n7BitBlocks) {
		case 5:
			errn = encode(stream, (uint8_t)(128 | n));
			n = n >> 7;
			if (errn < 0) {
				break;
			}
		case 4:
			errn = encode(stream, (uint8_t)(128 | n));
			n = n >> 7;
			if (errn < 0) {
				break;
			}
		case 3:
			errn = encode(stream, (uint8_t)(128 | n));
			n = n >> 7;
			if (errn < 0) {
				break;
			}
		case 2:
			errn = encode(stream, (uint8_t)(128 | n));
			n = n >> 7;
			if (errn < 0) {
				break;
			}
		case 1:
			/* 0 .. 7 (last byte) */
			errn = encode(stream, (uint8_t)(0 | n));
		}
	}

	return errn;
}

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger64(bitstream_t* stream, uint64_t n) {
	int errn = 0;
	uint8_t lastEncode = (uint8_t) n;
	n >>= 7;

	while (n != 0) {
		errn = encode(stream, lastEncode | 128);
		if (errn < 0) {
			return errn;
		}
		lastEncode = (uint8_t) n;
		n >>= 7;
	}

	return encode(stream, lastEncode);
}


/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger32(bitstream_t* stream, int32_t n) {
	int errn;
	/* signalize sign */
	if (n < 0) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn < 0) {
		return errn;
	}
	return encodeUnsignedInteger32(stream, n);
}

/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger64(bitstream_t* stream, int64_t n) {
	int errn;
	/* signalize sign */
	if (n < 0) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn < 0) {
		return errn;
	}
	return encodeUnsignedInteger64(stream, n);
}


/**
 * The Float datatype representation is two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int encodeFloat(bitstream_t* stream, float_me_t* f) {
	int errn = encodeInteger64(stream, f->mantissa);
	if (errn >= 0) {
		errn = encodeInteger32(stream, f->exponent);
	}
	return errn;
}


/**
 * Encode a length prefixed sequence of characters.
 */
int encodeString(bitstream_t* stream, string_ucs_t* string) {
	int errn = encodeUnsignedInteger32(stream, string->len);
	if (errn >= 0) {
		errn = encodeCharacters(stream, string->codepoints, string->len);
	}
	return errn;
}

int encodeStringValue(bitstream_t* stream, string_ucs_t* string) {
	/* encode string as string table miss */
	int errn = encodeUnsignedInteger32(stream, string->len+2);
	if (errn >= 0) {
		errn = encodeCharacters(stream, string->codepoints, string->len);
	}
	return errn;
}

/**
 * Encode a sequence of characters according to a given length.
 * Each character is represented by its UCS [ISO/IEC 10646]
 * code point encoded as an Unsigned Integer
 */
int encodeCharacters(bitstream_t* stream, uint32_t* chars, size_t len) {
	unsigned int i;
	int errn = 0;
	for(i=0; i<len && errn>=0; i++) {
		errn = encodeUnsignedInteger32(stream, chars[i]);
	}
	return errn;
}


/**
 * Encode a binary value as a length-prefixed sequence of octets.
 */
int encodeBinary(bitstream_t* stream, bytes_t* bytes)  {
	unsigned int i;
	int errn = encodeUnsignedInteger32(stream, bytes->len);

	for(i=0; i<bytes->len && errn>=0; i++) {
		errn = encode(stream, bytes->data[i]);
	}
	return errn;
}

/**
 * Flush underlying bit output stream.
 */
int encodeFinish(bitstream_t* stream) {
	return flush(stream);
}


#endif












