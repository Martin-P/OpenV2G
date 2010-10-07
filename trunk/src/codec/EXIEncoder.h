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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_ENCODER_H
#define EXI_ENCODER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "EXITypes.h"

int exiInitEncoder(bitstream_t* stream, exi_state_t* state);

int exiEncodeStartDocument(bitstream_t* stream, exi_state_t* state);

int exiEncodeEndDocument(bitstream_t* stream, exi_state_t* state);

int exiEncodeStartElement(bitstream_t* stream, exi_state_t* state,
				eqname_t* se);

int exiEncodeEndElement(bitstream_t* stream, exi_state_t* state, eqname_t* ee);

int exiEncodeCharacters(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val);

int exiEncodeAttribute(bitstream_t* stream, exi_state_t* state, eqname_t* at,
		exi_value_t* val);

#endif

#ifdef __cplusplus
}
#endif

