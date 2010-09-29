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

#include <stdio.h>
#include <stdlib.h>

#include "EXIHeaderDecoder.h"
#include "BitInputStream.h"
#include "BitDecoderChannel.h"

#ifndef EXI_HEADER_DECODER_C
#define EXI_HEADER_DECODER_C

int readEXIHeader(bitstream_t* stream) {
	uint8_t header;
	int errn = readBits(stream, 8, &header);
	if (errn < 0) {
		return errn;
	}
	if(header == '$') {
		/*	we do not support "EXI Cookie" */
		errn = -1;
	} else if ( header & 0x20 ) {
		/* we do not support "Presence Bit for EXI Options" */
		errn = -2;
	} else {
		/* Yes, a *simple* header */
		errn = 0;
	}
	return errn;
}


#endif


