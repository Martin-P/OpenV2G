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

#include <stdio.h>
#include <stdlib.h>

#include "EXIHeaderEncoder.h"
#include "BitOutputStream.h"
#include "BitEncoderChannel.h"

#ifndef EXI_HEADER_ENCODER_C
#define EXI_HEADER_ENCODER_C

int writeEXIHeader(bitstream_t* stream) {
	return writeBits(stream, 8, 144);
}


#endif


