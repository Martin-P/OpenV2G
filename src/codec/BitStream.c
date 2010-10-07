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
 ********************************************************************/

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "EXITypes.h"

#ifndef BIT_STREAM_C
#define BIT_STREAM_C

int toBitstream(const char * filename, bitstream_t* bitstream) {
	FILE* f;
	int character;
	size_t len = 0, pos = 0, i;

	f = fopen(filename, "rb");

	if (f == NULL) {
		printf("\n[Error] no valid file handle !\n");
		return -1;
	} else {
		/* detect file size */
		while ((character = getc(f)) != EOF) {
			/* printf("%u \n", character); */
			len++;
		}
		fclose(f);
		/* printf("%u Zeichen", len); */

		/* setup stream */
		bitstream->data = malloc(sizeof(uint8_t) * len);
		bitstream->size = len;
		bitstream->pos = &pos;
		bitstream->buffer = 0;
		bitstream->capacity = 8;

		/* read file byte per byte */
		f = fopen(filename, "rb");
		i = 0;
		while ((character = getc(f)) != EOF) {
			bitstream->data[i] = (uint8_t) character;
			i++;
		}
		fclose(f);
	}

	return 0;
}

int writeBytesToFile(uint8_t* data, size_t len, const char * filename) {
	size_t rlen;
	FILE* f = fopen(filename, "wb+");

	if (f == NULL) {
		return -1;
	} else {
		rlen = fwrite(data, sizeof(uint8_t), len, f);
		fflush(f);
		fclose(f);
		if(rlen == len) {
			return 0;
		} else {
			return -1;
		}
	}
}

int writeBitstreamToFile(bitstream_t* bitsream, const char * filename) {
	return writeBytesToFile(bitsream->data, bitsream->size, filename);
}



#endif

