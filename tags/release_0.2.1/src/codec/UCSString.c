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

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "BitDecoderChannel.h"
#include "BitInputStream.h"
#include "EXITypes.h"

#ifndef UCS_STRING_C
#define UCS_STRING_C

int toUCSString(char* chars, string_ucs_t* s) {
	unsigned int i;
	s->len = strlen(chars);

	if (s->len <= s->size) {
		for(i=0; i<s->len; i++) {
			s->codepoints[i] = chars[i];
		}
		return 0;
	} else {
		return -1;
	}
}

/* Note: fails if string contains non ASCII characters */
int toASCIIString(string_ucs_t* string, char* outASCII) {
	unsigned int i;
	for(i=0; i<string->len; i++) {
		outASCII[i] = (char)string->codepoints[i];
	}
	outASCII[string->len] = '\0';

	return 0;
}

#endif

