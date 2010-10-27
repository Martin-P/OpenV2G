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

#ifndef STRING_TABLE_C
#define STRING_TABLE_C

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "StringTable.h"
#include "EXITypes.h"
#include "BitInputStream.h"
#include "BitDecoderChannel.h"

#include "StringTableEntries.h"

#include "assert.h"

int exiGetUri(size_t uriID, const char** uri) {
	if ( uriID < stringTable.len ) {
		*uri = stringTable.uris[uriID];
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}

	return 0;
}

int exiGetUriLength(size_t* uriLength) {
	*uriLength =  stringTable.len;
	return 0;
}


int exiGetUriID(const char* uri, size_t* uriID) {
	unsigned int i;
	for(i=0; i<stringTable.len; i++) {
		if ( strcmp ( uri, stringTable.uris[i] ) == 0 ) {
			*uriID = i;
			return 0;
		}
	}
	return -1;
}


int exiGetLocalName(size_t uriID, size_t localNameID, const char** localName) {
	if ( uriID < stringTable.len ) {
		if ( localNameID < stringTable.localNames[uriID].len ) {
			*localName = stringTable.localNames[uriID].entries[localNameID];
		} else {
			return EXI_ERROR_OUT_OF_BOUNDS;
		}
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}
	return 0;
}

int exiGetLocalNameLength(size_t uriID, size_t* localNameLength) {
	if ( uriID < stringTable.len ) {
		*localNameLength =  stringTable.localNames[uriID].len;
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}

	return 0;
}

int exiGetLocalNameID(size_t uriID, const char* localName, size_t* localNameID) {
	unsigned int i;
	if ( uriID < stringTable.len ) {
		/* TODO binary search */
		for(i=0; i<stringTable.localNames[uriID].len; i++) {
			if ( strcmp ( localName, stringTable.localNames[uriID].entries[i] ) == 0 ) {
				*localNameID = i;
				return 0;
			}
		}
	} else {
		return EXI_ERROR_OUT_OF_BOUNDS;
	}

	return -1;
}

#endif

