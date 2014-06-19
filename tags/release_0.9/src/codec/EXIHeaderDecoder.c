/* $EXI_SOURCE_PREAMBLE$ */

#include "EXIHeaderDecoder.h"
#include "BitInputStream.h"
#include "DecoderChannel.h"
#include "ErrorCodes.h"

#ifndef EXI_HEADER_DECODER_C
#define EXI_HEADER_DECODER_C

int readEXIHeader(bitstream_t* stream) {
	int errn;
	uint32_t header = 0;

	/* init stream */
	stream->buffer = 0;
	stream->capacity = 0;

	errn = readBits(stream, 8, &header);
	if (errn == 0) {
		if(header == '$') {
			/*	we do not support "EXI Cookie" */
			errn = EXI_UNSUPPORTED_HEADER_COOKIE;
		} else if ( header & 0x20 ) {
			/* we do not support "Presence Bit for EXI Options" */
			errn = EXI_UNSUPPORTED_HEADER_OPTIONS;
		} else {
			/* Yes, a *simple* header */
			errn = 0;
		}
	}

	return errn;
}


#endif


