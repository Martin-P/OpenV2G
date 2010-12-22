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
 * @version 0.3.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>

#ifndef EXI_TYPES_H
#define EXI_TYPES_H

#define BITS_IN_BYTE 8

#define UINT_MAX_VALUE 65535

#define EXI_ELEMENT_STACK_SIZE 16

/* EXI automaton methods prefixes such as "inline" etc. */
#ifndef EXI_MPFX
#define EXI_MPFX
#endif

#define FLOAT_EXPONENT_SPECIAL_VALUES -16384
#define FLOAT_MANTISSA_INFINITY 1
#define FLOAT_MANTISSA_MINUS_INFINITY -1
#define FLOAT_MANTISSA_NOT_A_NUMBER 0

typedef struct {
	/*	Integer Array */
	uint16_t size; /* array size */
	uint8_t* data; /* int data array */
	uint16_t* pos; /* next position in array */
	/* Current byte buffer & its remaining bit capacity */
	uint8_t buffer;
	uint16_t capacity;
} bitstream_t;

typedef struct {
	/* Bytes Size and array container */
	uint16_t size;
	uint8_t* data;
	/* current length (len <= size) */
	uint16_t len;
} bytes_t;

/* Universal Character Set (UCS) strings */
typedef struct {
	/* UCS size and UCS character container*/
	uint16_t size;
	uint32_t* codepoints;
	/* current length == number of code-points, (len <= size) */
	uint16_t len;
} string_ucs_t;

typedef struct {
	/* range of the mantissa is -(2^63) to 2^63-1 */
	int64_t mantissa;
	/* range of the exponent is - (2^14-1) to 2^14-1 */
	int32_t exponent; /* base-10 */
} float_me_t;


typedef enum
{
	/* Binary */
	BINARY_BASE64, BINARY_HEX,
	/* Boolean */
	BOOLEAN,
	/* Decimal */
	DECIMAL,
	/* Float */
	FLOAT, DOUBLE,
	/* N-Bit Integer */
	NBIT_INTEGER_32, NBIT_INTEGER_64, NBIT_INTEGER_BIG,
	/* Unsigned Integer */
	UNSIGNED_INTEGER_16, UNSIGNED_INTEGER_32, UNSIGNED_INTEGER_64, UNSIGNED_INTEGER_BIG,
	/* (Signed) Integer */
	INTEGER_16, INTEGER_32, INTEGER_64, INTEGER_BIG,
	/* Datetime */
	DATETIME,
	/* String */
	STRING,
	/* Enumeration */
	ENUMERATION,
	/* List */
	LIST
}  exi_datatype_t;


typedef enum
{
	START_DOCUMENT,
	END_DOCUMENT,
	START_ELEMENT,
	START_ELEMENT_GENERIC, /* not supported yet */
	END_ELEMENT,
	CHARACTERS,
	CHARACTERS_GENERIC, /* not supported yet */
	ATTRIBUTE,
	ATTRIBUTE_GENERIC, /* not supported yet */
	/* error state */
	ERROR
} exi_event_t;

/* TODO list support */
typedef struct {
	/* List container with memory size */
	uint16_t size;
	uint8_t* data;
	/* list item type */
	exi_datatype_t type;
	/* number of items */
	uint16_t len;
} list_t;


typedef struct {
	uint16_t namespaceURI;
	uint16_t localPart;
} eqname_t;

typedef struct  {
	/* stack of grammar states and elements */
	uint16_t grammarStack [EXI_ELEMENT_STACK_SIZE];
	eqname_t elementStack [EXI_ELEMENT_STACK_SIZE];
	uint16_t stackIndex;
	/* event-code */
	uint32_t eventCode;
} exi_state_t;


typedef struct  {
	/* type of value */
	exi_datatype_t type;

	/* base types */
	int boolean;
	uint32_t uint32;
	uint64_t uint64;
	int32_t int32;
	int64_t int64;
	uint32_t enumeration;

	/* Bytes, Strings and Lists are not native types anymore */
	bytes_t binary;
	string_ucs_t string;
	float_me_t float_me;
	list_t list;
} exi_value_t;


/*
 * ERROR-Codes
 */
# define EXI_ERROR_OUT_OF_BOUNDS -100

# define EXI_ERROR_UNKOWN_EVENT_CODE -110

#endif

#ifdef __cplusplus
}
#endif
