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
 * <p>Sample program to illustrate how to read an EXI stream and
 *  directly write it again to an output</p>
 *
 *  <p>e.g., data/test/sessionSetupReq.xml_SCHEMA.exi out/test/sessionSetupReq.xml_SCHEMA.exi</p>
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "EXIDecoder.h"
#include "StringTable.h"
#include "EXIEncoder.h"
#include "EXITypes.h"
#include "Bitstream.h"

#define ARRAY_SIZE_BYTES 50
#define ARRAY_SIZE_STRINGS 50

/* avoids warning: initializer element is not computable at load time */
uint8_t data[ARRAY_SIZE_BYTES];
uint32_t codepoints[ARRAY_SIZE_STRINGS];

int main(int argc, char *argv[]) {

	int errn = 0;
	unsigned int i;

	bitstream_t iStream, oStream;
	size_t posDecode, posEncode;

	/* EXI set-up */
	exi_state_t stateDecode;
	exi_state_t stateEncode;
	exi_event_t event;
	eqname_t eqn;
	exi_value_t val;

	/* BINARY memory setup */
	bytes_t bytes = { ARRAY_SIZE_BYTES, data, 0 };

	/* STRING memory setuo */
	string_ucs_t string = { ARRAY_SIZE_STRINGS, codepoints, 0 };

	const char * localName;
	const char * namespaceURI;

	int noEndOfDocument = 1; /* true */

	if (argc != 3) {
		printf("Usage: %s exiInput exiOutput\n", argv[0]);
		return -1;
	}

	/* parse EXI stream to internal byte structures  */
	toBitstream(argv[1], &iStream);

	/* input */
	posDecode = 0;
	iStream.pos = &posDecode;
	iStream.buffer = 0;
	iStream.capacity = 0;

	/* output */
	posEncode = 0;
	oStream.data = malloc(sizeof(uint8_t)*iStream.size);
	oStream.size = iStream.size;
	oStream.pos = &posEncode;
	oStream.buffer = 0;
	oStream.capacity = 8;

	val.binary = bytes;
	val.string = string;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&iStream, &stateDecode);

	/* init encoder (write header, set initial state) */
	exiInitEncoder(&oStream, &stateEncode);

	printf("[DECODE] >>> EXI  >>> [ENCODE] \n");

	do {
		if (errn < 0) {
			printf("[Encode-ERROR] %d \n", errno);
			return errn;
		}

		errn = exiDecodeNextEvent(&iStream, &stateDecode, &event);
		if (errn < 0) {
			printf("[Decode-ERROR] %d \n", errno);
			return errn;
		}

		switch (event) {
		case START_DOCUMENT:
			/* decode */
			errn = exiDecodeStartDocument(&iStream, &stateDecode);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			printf(">> START_DOCUMENT \n");
			/* encode */
			errn = exiEncodeStartDocument(&oStream, &stateEncode);
			break;
		case END_DOCUMENT:
			/* decode */
			errn = exiDecodeEndDocument(&iStream, &stateDecode);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			printf(">> END_DOCUMENT \n");
			/* encode */
			errn = exiEncodeEndDocument(&oStream, &stateEncode);
			/* signalize end of document */
			noEndOfDocument = 0; /* false */
			break;
		case START_ELEMENT:
			/* decode */
			errn = exiDecodeStartElement(&iStream, &stateDecode, &eqn);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			exiGetLocalName(eqn.namespaceURI, eqn.localPart, &localName);
			exiGetUri(eqn.namespaceURI, &namespaceURI);
			printf(">> SE {%s}%s \n", namespaceURI, localName);
			/* encode */
			errn = exiEncodeStartElement(&oStream, &stateEncode, &eqn);
			break;
		case END_ELEMENT:
			/* decode */
			errn = exiDecodeEndElement(&iStream, &stateDecode, &eqn);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			exiGetLocalName(eqn.namespaceURI, eqn.localPart, &localName);
			exiGetUri(eqn.namespaceURI, &namespaceURI);
			printf("<< EE {%s}%s \n", namespaceURI, localName);
			/* encode */
			errn = exiEncodeEndElement(&oStream, &stateEncode, &eqn);
			break;
		case CHARACTERS:
			/* decode */
			errn = exiDecodeCharacters(&iStream, &stateDecode, &val);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			if (val.type == INTEGER_BIG) {
				printf(" CH int64 : %lld \n", val.int64);
			} else if (val.type == BINARY_BASE64 || val.type == BINARY_HEX) {
				printf(" CH Binary (len == %d) : ", val.binary.len);
				for(i=0; i<val.binary.len; i++) {
					printf(" [%d]", val.binary.data[i]);
				}
				printf("\n");
			} else if (val.type == BOOLEAN) {
				printf(" CH Boolean : %d \n", val.boolean);
			} else if (val.type == STRING) {
				printf(" CH String (len==%d) : '", val.string.len);
				for(i=0;i<val.string.len; i++) {
					printf("%c", (char)val.string.codepoints[i]);
				}
				printf("'\n");
			} else {
				printf(" CH ?? \n");
			}
			/* encode */
			errn = exiEncodeCharacters(&oStream, &stateEncode, &val);
			break;
		case ATTRIBUTE:
			/* decode */
			errn = exiDecodeAttribute(&iStream, &stateDecode, &eqn, &val);
			if (errn < 0) {
				printf("[Decode-ERROR] %d \n", errno);
				return errn;
			}
			exiGetLocalName(eqn.namespaceURI, eqn.localPart, &localName);
			exiGetUri(eqn.namespaceURI, &namespaceURI);
			printf(" AT {%s}%s \n", namespaceURI, localName);
			/* encode */
			errn = exiEncodeAttribute(&oStream, &stateEncode, &eqn, &val);
			break;
		default:
			/* ERROR */
			return -1;
		}

	} while (noEndOfDocument);

	/* write to file */
	writeBytesToFile(oStream.data, iStream.size, argv[2]);

	return 0;
}

