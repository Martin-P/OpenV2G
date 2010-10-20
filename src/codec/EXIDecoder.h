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
 * @version 0.2.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_DECODER_H
#define EXI_DECODER_H

#include "EXITypes.h"

int exiInitDecoder(bitstream_t* stream, exi_state_t* state);

int exiDecodeNextEvent(bitstream_t* stream, exi_state_t* state,
		exi_event_t* nextEvent);

int exiDecodeStartDocument(bitstream_t* stream, exi_state_t* state);

int exiDecodeEndDocument(bitstream_t* stream, exi_state_t* state);

int exiDecodeStartElement(bitstream_t* stream, exi_state_t* state,
		eqname_t* se);

int exiDecodeEndElement(bitstream_t* stream, exi_state_t* state,
		eqname_t* ee);

int exiDecodeCharacters(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val);

int exiDecodeAttribute(bitstream_t* stream, exi_state_t* state,
		eqname_t* at, exi_value_t* val);

#endif

#ifdef __cplusplus
}
#endif

