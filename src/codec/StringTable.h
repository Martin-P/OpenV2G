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

#ifndef STRING_TABLE_H
#define STRING_TABLE_H

#include "EXITypes.h"

int exiGetUri(uint16_t uriID, const char** uri);

int exiGetUriLength(uint16_t* uriLength);

int exiGetUriID(const char* uri, uint16_t* uriID);

int exiGetLocalName(uint16_t uriID, uint16_t localNameID, const char** localName);

int exiGetLocalNameLength(uint16_t uriID, uint16_t* localNameLength);

int exiGetLocalNameID(uint16_t uriID, const char* localName, uint16_t* localNameID);

#endif


#ifdef __cplusplus
}
#endif

