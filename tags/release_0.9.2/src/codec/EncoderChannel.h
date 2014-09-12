/*
 * Copyright (C) 2007-2014 Siemens AG
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
 * @version 0.9.2
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



/**
 * \file 	EncoderChannel.h
 * \brief 	EXI Encoder Channel
 *
 */

#ifndef ENCODER_CHANNEL_H
#define ENCODER_CHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "EXITypes.h"


/**
 * \brief 		Encode byte value
 *
 * \param       stream   		Output Stream
 * \param       b		   		byte
 * \return                  	Error-Code <> 0
 *
 */
int encode(bitstream_t* stream, uint8_t b);


/**
 * \brief 		Encode a single boolean value
 *
 * 				A false value is encoded as 0 and true value is encode as 1.
 *
 * \param       stream   		Output Stream
 * \param       b		   		boolean
 * \return                  	Error-Code <> 0
 *
 */
int encodeBoolean(bitstream_t* stream, int b);


/**
 * \brief 		Encode n-bit unsigned integer
 *
 * 				The n least significant bits of parameter b starting with the
 * 				most significant, i.e. from left to right.
 *
 * \param       stream   		Output Stream
 * \param       nbits		   	number of bits
 * \param       val		   		value
 * \return                  	Error-Code <> 0
 *
 */
int encodeNBitUnsignedInteger(bitstream_t* stream, uint16_t nbits, uint32_t val);


/**
 * \brief 		Encode unsigned integer
 *
 * 				Encode an arbitrary precision non negative integer using
 * 				a sequence of octets. The most significant bit of the last
 * 				octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       iv		   		Unsigned integer value
 * \return                  	Error-Code <> 0
 *
 */
int encodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv);


/**
 * \brief 		Encode unsigned integer
 *
 * 				Encode an arbitrary precision non negative integer using
 * 				a sequence of octets. The most significant bit of the last
 * 				octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Unsigned integer value 16 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeUnsignedInteger16(bitstream_t* stream, uint16_t n);



/**
 * \brief 		Encode unsigned integer
 *
 * 				Encode an arbitrary precision non negative integer using
 * 				a sequence of octets. The most significant bit of the last
 * 				octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Unsigned integer value 32 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeUnsignedInteger32(bitstream_t* stream, uint32_t n);


/**
 * \brief 		Encode unsigned integer
 *
 * 				Encode an arbitrary precision non negative integer using
 * 				a sequence of octets. The most significant bit of the last
 * 				octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Unsigned integer value 64 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeUnsignedInteger64(bitstream_t* stream, uint64_t n);


/**
 * \brief 		Encode integer
 *
 * 				Encode an arbitrary precision integer using a sign boolean
 * 				followed by a sequence of octets. The most significant bit
 * 				of the last octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       iv		   		Integer value
 * \return                  	Error-Code <> 0
 *
 */
int encodeInteger(bitstream_t* stream, exi_integer_t* iv);


/**
 * \brief 		Encode integer
 *
 * 				Encode an arbitrary precision integer using a sign boolean
 * 				followed by a sequence of octets. The most significant bit
 * 				of the last octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Integer value 16 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeInteger16(bitstream_t* stream, int16_t n);

/**
 * \brief 		Encode integer
 *
 * 				Encode an arbitrary precision integer using a sign boolean
 * 				followed by a sequence of octets. The most significant bit
 * 				of the last octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Integer value 32 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeInteger32(bitstream_t* stream, int32_t n);


/**
 * \brief 		Encode integer
 *
 * 				Encode an arbitrary precision integer using a sign boolean
 * 				followed by a sequence of octets. The most significant bit
 * 				of the last octet is set to zero to indicate sequence termination.
 * 				Only seven bits per octet are used to store the integer's value.
 *
 * \param       stream   		Output Stream
 * \param       n		   		Integer value 64 bits
 * \return                  	Error-Code <> 0
 *
 */
int encodeInteger64(bitstream_t* stream, int64_t n);


/**
 * \brief 		Encode float
 *
 * 				Encode a Float datatype as two consecutive Integers. The first
 * 				Integer represents the mantissa of the floating point number
 * 				and the second Integer represents the base-10 exponent of the
 * 				floating point number.
 *
 * \param       stream   		Output Stream
 * \param       f		   		Float value
 * \return                  	Error-Code <> 0
 *
 */
int encodeFloat(bitstream_t* stream, exi_float_me_t* f);


/**
 * \brief 		Encode decimal
 *
 * 				Encode a decimal represented as a Boolean sign followed by two
 * 				Unsigned Integers. A sign value of zero (0) is used to represent
 * 				positive Decimal values and a sign value of one (1) is used to
 * 				represent negative Decimal values The first Integer represents
 * 				the integral portion of the Decimal value. The second positive
 * 				integer represents the fractional portion of the decimal with
 * 				the digits in reverse order to preserve leading zeros.
 *
 * \param       stream   		Output Stream
 * \param       d		   		Decimal value
 * \return                  	Error-Code <> 0
 *
 */
int encodeDecimal(bitstream_t* stream, exi_decimal_t* d);


/**
 * \brief 		Encode string
 *
 * 				Encode a length prefixed sequence of characters.
 *
 * \param       stream   		Output Stream
 * \param       string		   	String
 * \return                  	Error-Code <> 0
 *
 */
int encodeString(bitstream_t* stream, exi_string_t* string);


/**
 * \brief 		Encode string value
 *
 * 				 Encode a length prefixed sequence of characters
 * 				 in the sense of string tables
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \param       string		   	String value
 * \return                  	Error-Code <> 0
 *
 */
int encodeStringValue(bitstream_t* stream, exi_state_t* state, uint16_t qnameID,
		exi_string_value_t* string);


/**
 * \brief 		Encode restricted character set value
 *
 * 				 Encode a length prefixed sequence of characters
 * 				 in the sense of string tables
 *
 * \param       stream   		Output Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \param       rcs   			Restricted character set
 * \param       string		   	String value
 * \return                  	Error-Code <> 0
 *
 */
int encodeRCSStringValue(bitstream_t* stream, exi_state_t* state,
		uint16_t qnameID, exi_rcs_t* rcs, exi_string_value_t* string);


/**
 * \brief 		Encode characters
 *
 * 				Encode a sequence of characters according to a given length.
 * 				Each character is represented by its UCS [ISO/IEC 10646]
 * 				code point encoded as an Unsigned Integer.
 *
 * \param       stream   		Output Stream
 * \param       chars   		Characters
 * \param       len				Numbr of characters
 * \return                  	Error-Code <> 0
 *
 */
int encodeCharacters(bitstream_t* stream, exi_string_character_t* chars, uint16_t len);


/**
 * \brief 		Encode characters
 *
 * 				Encode a sequence of characters according to a given length.
 * 				Each character is represented by its UCS [ISO/IEC 10646]
 * 				code point encoded as an Unsigned Integer.
 *
 * \param       stream   		Output Stream
 * \param       chars   		Characters
 * \param       len				Numbr of characters
 *  \param       rcsCodeLength   RCS code-length
 * \param       rcsCodeLength   RCS size
 * \param       rcsCodeLength   RCS set
 * \return                  	Error-Code <> 0
 *
 */
int encodeRCSCharacters(bitstream_t* stream, exi_string_character_t* chars, uint16_t len, uint16_t rcsCodeLength, uint16_t rcsSize, const exi_string_character_t rcsSet[]);



/**
 * \brief 		Encode binary
 *
 * 				Encode a binary value as a length-prefixed sequence of octets.
 *
 * \param       stream   		Output Stream
 * \param       bytes   		Byte values
 * \return                  	Error-Code <> 0
 *
 */
int encodeBinary(bitstream_t* stream, exi_bytes_t* bytes);


/**
 * \brief 		Encode binary data
 *
 * 				Encode a sequence of octets.
 *
 * \param       stream   		Output Stream
 * \param       data	   		Byte values
 * \param       len		   		Length
 * \return                  	Error-Code <> 0
 *
 */
int encodeBytes(bitstream_t* stream, uint8_t* data, uint16_t len);

/**
 * \brief 		Encode datetime
 *
 * 				Encode a datetime representation which is a sequence of values
 * 				representing the individual components of the Date-Time.
 *
 * \param       stream   		Output Stream
 * \param       datetime   		Datetime values
 * \return                  	Error-Code <> 0
 *
 */
int encodeDateTime(bitstream_t* stream, exi_datetime_t* datetime);


/**
 * \brief 		Flush underlying bit output stream
 *
 * \param       stream   		Output Stream
 * \return                  	Error-Code <> 0
 *
 */
int encodeFinish(bitstream_t* stream);

#ifdef __cplusplus
}
#endif

#endif
