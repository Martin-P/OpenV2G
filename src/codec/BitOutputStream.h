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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "EXITypes.h"

#ifndef BIT_OUTPUT_STREAM_H
#define BIT_OUTPUT_STREAM_H

int writeBits(bitstream_t* stream, size_t nbits, uint8_t bits);

/* flush output */
int flush(bitstream_t* stream);

#endif


#ifdef __cplusplus
}
#endif

