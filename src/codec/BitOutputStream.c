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
 * @version 0.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include <string.h>

#include "EXITypes.h"
#include "BitOutputStream.h"

#ifndef BIT_OUTPUT_STREAM_C
#define BIT_OUTPUT_STREAM_C

/*	NOTE: nbits <= 8 */
int writeBits(bitstream_t* stream, size_t nbits, uint8_t val) {
	/*  is there enough space in the buffer */
	if (nbits <= stream->capacity) {
		/* all bits fit into the current buffer */
		stream->buffer = (stream->buffer << (nbits)) | (val & (0xff
				>> (BITS_IN_BYTE - nbits)));
		stream->capacity -= nbits;
		/* if the buffer is full write it into the data */
		if (stream->capacity == 0) {
			if ((*stream->pos) >= stream->size) {
				return -1;
			}
			stream->data[(*stream->pos)++] = 0xFF & stream->buffer;
			stream->capacity = BITS_IN_BYTE;
			stream->buffer = 0;
		}
	} else {
		/* the buffer is not enough
		 * fill the buffer */
		stream->buffer = (stream->buffer << stream->capacity) | ((val >> (nbits
				- stream->capacity)) & (0xff >> (BITS_IN_BYTE
				- stream->capacity)));

		nbits -= stream->capacity;
		if ((*stream->pos) >= stream->size) {
			return -1;
		}
		stream->data[(*stream->pos)++] = 0xFF & stream->buffer;
		stream->buffer = 0;

		/* write whole bytes */
		while (nbits >= BITS_IN_BYTE) {
			nbits -= BITS_IN_BYTE;
			if ((*stream->pos) >= stream->size) {
				return -1;
			}
			stream->data[(*stream->pos)++] = 0xFF & (val >> (nbits));
		}

		/* spared bits are kept in the buffer */
		stream->buffer = val; /* Note: the high bits will be shifted out during further filling */
		stream->capacity = BITS_IN_BYTE - (nbits);
	}

	return 0;
}

/**
 * Flush output
 */
int flush(bitstream_t* stream) {
	if (stream->capacity == BITS_IN_BYTE) {
		/* nothing to do, no bits in buffer */
		return 0;
	} else {
		return writeBits(stream, stream->capacity, 0);
	}
}

#endif

