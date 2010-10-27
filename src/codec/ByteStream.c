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

#define _CRT_SECURE_NO_DEPRECATE 1

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "EXITypes.h"

#ifndef BYTE_STREAM_C
#define BYTE_STREAM_C

int readBytesFromFile(const char * filename, uint8_t* data, size_t size, size_t pos) {
	FILE* f;
	int character;

	f = fopen(filename, "rb");

	if (f == NULL) {
		printf("\n[Error] no valid file handle !\n");
		return -1;
	} else {
		/* read bytes */
		while ((character = getc(f)) != EOF) {
			if (pos >= size) {
				return -1;
			}
			data[pos++] = (uint8_t) character;
			/* printf("%u \n", character); */
		}
		fclose(f);
	}

	return pos;
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


#endif

