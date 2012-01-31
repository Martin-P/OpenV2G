/*
 * Copyright (C) 2007-2012 Siemens AG
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
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 2012-01-31 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



/*******************************************************************
 *
 * <p>Sample program to illustrate how to read an EXI stream and
 *  directly write it again to an output</p>
 *
 *  <p>e.g., data/test/sessionSetupReq.xml.exi out/test/sessionSetupReq.xml.exi</p>
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "EXIDecoder.h"
#include "StringTable.h"
#include "EXIEncoder.h"
#include "EXITypes.h"
#include "ByteStream.h"

#define DEBUG 1

#if EXI_STREAM == BYTE_ARRAY
/* 64 kilobytes = 65 536 bytes */
/* 1 megabyte = 1 048 576 bytes*/
#define BUFFER_SIZE 1048576
uint8_t bufferIn[BUFFER_SIZE];
uint8_t bufferOut[BUFFER_SIZE];
#endif /* EXI_STREAM == BYTE_ARRAY */

/* avoids warning: initializer element is not computable at load time */
#define ARRAY_SIZE_BYTES 300
uint8_t bytesData[ARRAY_SIZE_BYTES];
#define ARRAY_SIZE_STRINGS 30000
uint32_t codepoints[ARRAY_SIZE_STRINGS];
#define ARRAY_SIZE_STRINGS_ASCII 150
char charsNamespaceURI[ARRAY_SIZE_STRINGS_ASCII];
char charsLocalName[ARRAY_SIZE_STRINGS_ASCII];

void debugValue(exi_value_t* val) ;

int main_codec(int argc, char *argv[]) {

	int errn = 0;

	bitstream_t iStream, oStream;
	uint32_t posDecode;
	uint32_t posEncode;

	/* EXI set-up */
	exi_state_t stateDecode;
	exi_state_t stateEncode;
	exi_event_t event;
	eqname_t eqn; /* efficient qname */
	qname_t qn; /* ascii qname */
	exi_value_t val;

	exi_name_table_runtime_t runtimeTableDecode;
	exi_name_table_runtime_t runtimeTableEncode;

	/* BINARY memory setup */
	bytes_t bytes = { ARRAY_SIZE_BYTES, bytesData, 0 };

	const char * localName;
	const char * namespaceURI;
	int noEndOfDocument = 1; /* true */

	/* STRING memory setup */
	string_ucs_t string = { ARRAY_SIZE_STRINGS, codepoints, 0 };
	string_ascii_t stringNamespaceURI = { ARRAY_SIZE_STRINGS_ASCII, charsNamespaceURI };
	string_ascii_t stringLocalName = { ARRAY_SIZE_STRINGS_ASCII, charsLocalName };
	qn.namespaceURI = stringNamespaceURI;
	qn.localName = stringLocalName;

	if (argc != 3) {
		printf("Usage: %s exiInput exiOutput\n", argv[0]);
		return -1;
	}

	/* input pos */
	posDecode = 0;

#if EXI_STREAM == BYTE_ARRAY
	/* parse EXI stream to internal byte structures  */
	errn = readBytesFromFile(argv[1], bufferIn, BUFFER_SIZE, posDecode);
	if (errn < 0) {
		printf("Problems while reading file into buffer\n");
		return errn;
	}
#endif /* EXI_STREAM == BYTE_ARRAY */

	/* setup input stream */
#if EXI_STREAM == BYTE_ARRAY
	iStream.size = BUFFER_SIZE;
	iStream.data = bufferIn;
	iStream.pos = &posDecode;
#endif /* EXI_STREAM == BYTE_ARRAY */
#if EXI_STREAM == FILE_STREAM
	iStream.file = fopen(argv[1],"rb");
#endif /* EXI_STREAM == FILE_STREAM */

	iStream.buffer = 0;
	iStream.capacity = 0;

	/* setup output stream */
	posEncode = 0;
#if EXI_STREAM == BYTE_ARRAY
	oStream.size = BUFFER_SIZE;
	oStream.data = bufferOut;
	oStream.pos = &posEncode;
#endif
#if EXI_STREAM == FILE_STREAM
	oStream.file = fopen(argv[2],"wb");
#endif /* EXI_STREAM == FILE_STREAM */
	oStream.buffer = 0;
	oStream.capacity = 8;

	val.binary = bytes;
	val.string = string;

	/* init decoder (read header, set initial state) */
	/* init runtime table */
	errn = exiInitNameTableRuntime(&runtimeTableDecode);
	exiInitDecoder(&iStream, &stateDecode, runtimeTableDecode);

	/* init encoder (write header, set initial state) */
	errn = exiInitNameTableRuntime(&runtimeTableEncode);
	exiInitEncoder(&oStream, &stateEncode, runtimeTableEncode);

	if (DEBUG) {
		printf("[DECODE] >>> EXI  >>> [ENCODE] \n");
	}

	do {
		if (errn < 0) {
			if (DEBUG) {
				printf("[Encode-ERROR] %d \n", errn);
			}
			return errn;
		}

		errn = exiDecodeNextEvent(&iStream, &stateDecode, &event);
		if (errn < 0) {
			if (DEBUG) {
				printf("[Decode-ERROR] %d \n", errn);
			}
			return errn;
		}

		switch (event) {
		case START_DOCUMENT:
			/* decode */
			errn = exiDecodeStartDocument(&iStream, &stateDecode);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-SD] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf(">> START_DOCUMENT \n");
			}
			/* encode */
			errn = exiEncodeStartDocument(&oStream, &stateEncode);
			break;
		case END_DOCUMENT:
			/* decode */
			errn = exiDecodeEndDocument(&iStream, &stateDecode);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-ED] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf(">> END_DOCUMENT \n");
			}
			/* encode */
			errn = exiEncodeEndDocument(&oStream, &stateEncode);
			/* signalize end of document */
			noEndOfDocument = 0; /* false */
			break;
		case START_ELEMENT:
			/* decode */
			errn = exiDecodeStartElement(&iStream, &stateDecode, &eqn);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-SE] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				exiGetLocalName(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, eqn.localPart, &localName);
				exiGetUri(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, &namespaceURI);
				printf(">> SE {%s}%s \n", namespaceURI, localName);
			}
			/* encode */
			errn = exiEncodeStartElement(&oStream, &stateEncode, &eqn);
			break;
		case START_ELEMENT_GENERIC:
			/* decode */
			errn = exiDecodeStartElementGeneric(&iStream, &stateDecode, &qn);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-SEgen] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf(">> SE_Gen {%s}%s \n", stringNamespaceURI.chars, stringLocalName.chars);
			}
			/* encode */
			errn = exiEncodeStartElementGeneric(&oStream, &stateEncode,
					&stringNamespaceURI, &stringLocalName);
			break;
		case END_ELEMENT:
			/* decode */
			errn = exiDecodeEndElement(&iStream, &stateDecode, &eqn);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-EE] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf("<< EE \n");
			}
			/* encode */
			errn = exiEncodeEndElement(&oStream, &stateEncode);
			break;
		case END_ELEMENT_UNDECLARED:
			/* decode */
			errn = exiDecodeEndElementUndeclared(&iStream, &stateDecode, &eqn);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-EE-Undecl] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf("<< EEundecl \n");
			}
			/* encode */
			errn = exiEncodeEndElement(&oStream, &stateEncode);
			break;
		case CHARACTERS:
			/* decode */
			errn = exiDecodeCharacters(&iStream, &stateDecode, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-CH] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				debugValue(&val);
			}
			/* encode */
			errn = exiEncodeCharacters(&oStream, &stateEncode, &val);
			break;
		case CHARACTERS_GENERIC:
			/* decode */
			errn = exiDecodeCharactersGeneric(&iStream, &stateDecode, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-CHgen] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				debugValue(&val);
			}
			/* encode */
			errn = exiEncodeCharacters(&oStream, &stateEncode, &val);
			break;
		case CHARACTERS_GENERIC_UNDECLARED:
			/* decode */
			errn = exiDecodeCharactersGenericUndeclared(&iStream, &stateDecode, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-CHgenUndecl] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				debugValue(&val);
			}
			/* encode */
			errn = exiEncodeCharacters(&oStream, &stateEncode, &val);
			break;
		case ATTRIBUTE:
			/* decode */
			errn = exiDecodeAttribute(&iStream, &stateDecode, &eqn, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-AT] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				exiGetLocalName(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, eqn.localPart, &localName);
				exiGetUri(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, &namespaceURI);
				printf(" AT {%s}%s \n", namespaceURI, localName);
				debugValue(&val);
			}
			/* encode */
			errn = exiEncodeAttribute(&oStream, &stateEncode, &eqn, &val);
			break;
		case ATTRIBUTE_XSI_NIL:
			/* decode */
			errn = exiDecodeAttributeXsiNil(&iStream, &stateDecode, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-AT-NIL] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				printf(" AT {xsi}nil == %i \n", val.boolean);
			}
			/* encode */
			errn = exiEncodeAttributeXsiNil(&oStream, &stateEncode, &val);
			break;
		case ATTRIBUTE_XSI_TYPE:
			/* decode */
			errn = exiDecodeAttributeXsiType(&iStream, &stateDecode, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-AT-TYPE] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				exiGetLocalName(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), val.eqname.namespaceURI, val.eqname.localPart, &localName);
				exiGetUri(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), val.eqname.namespaceURI, &namespaceURI);
				printf(" AT {type}type == {%s}%s \n", namespaceURI, localName);
			}
			/* encode */
			errn = exiEncodeAttributeXsiType(&oStream, &stateEncode, &val);
			break;
		case ATTRIBUTE_GENERIC_UNDECLARED:
			/* decode */
			errn = exiDecodeAttributeGenericUndeclared(&iStream, &stateDecode, &qn, &val);
			if (errn < 0) {
				if (DEBUG) {
					printf("[Decode-ERROR-ATgenUnd] %d \n", errn);
				}
				return errn;
			}
			if (DEBUG) {
				/* exiGetLocalName(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, eqn.localPart, &localName);
				exiGetUri(&(stateDecode.nameTablePrepopulated), &(stateDecode.nameTableRuntime), eqn.namespaceURI, &namespaceURI); */
				printf(" AT {%s}%s \n", qn.namespaceURI.chars, qn.localName.chars);
				debugValue(&val);
			}
			/* encode */
			errn = exiEncodeAttribute(&oStream, &stateEncode, &eqn, &val);
			break;
		default:
			/* ERROR */
			if (DEBUG) {
				printf("[Unknown-Event] %d \n", event);
			}
			return EXI_ERROR_UNKOWN_EVENT;
		}

	} while (noEndOfDocument);

#if EXI_STREAM == BYTE_ARRAY
	/* write to file */
	writeBytesToFile(oStream.data, posEncode, argv[2]);
#endif
#if EXI_STREAM == FILE_STREAM
	fclose(iStream.file);
	fclose(oStream.file);
#endif

	return 0;
}

static int _setInt32Value(integer_t* iv, int32_t* int32) {
	int errn = 0;
	switch(iv->type) {
	/* Unsigned Integer */
	case UNSIGNED_INTEGER_8:
		*int32 = iv->val.uint8;
		break;
	case UNSIGNED_INTEGER_16:
		*int32 = iv->val.uint16;
		break;
	case UNSIGNED_INTEGER_32:
		if (iv->val.uint32 <= 2147483647) {
			*int32 = iv->val.uint32;
		} else {
			errn = EXI_UNSUPPORTED_INTEGER_VALUE;
		}
		break;
	case UNSIGNED_INTEGER_64:
		errn = EXI_UNSUPPORTED_INTEGER_VALUE;
		break;
	/* (Signed) Integer */
	case INTEGER_8:
		*int32 = iv->val.int8;
		break;
	case INTEGER_16:
		*int32 = iv->val.int16;
		break;
	case INTEGER_32:
		*int32 = iv->val.int32;
		break;
	case INTEGER_64:
		errn = EXI_UNSUPPORTED_INTEGER_VALUE;
	}
	return errn;
}


void debugValue(exi_value_t* val) {
	int i;
	switch(val->type) {
	case INTEGER:
		switch(val->integer.type) {
		/* Unsigned Integer */
		case UNSIGNED_INTEGER_8:
			printf(" Value uint8 : %d \n", val->integer.val.uint8);
			break;
		case UNSIGNED_INTEGER_16:
			printf(" Value uint16 : %d \n", val->integer.val.uint16);
			break;
		case UNSIGNED_INTEGER_32:
			printf(" Value uint32 : %d \n", val->integer.val.uint32);
			break;
		case UNSIGNED_INTEGER_64:
			printf(" Value uint64 : %ld \n", (long unsigned int) val->integer.val.uint64);
			break;
		/* (Signed) Integer */
		case INTEGER_8:
			printf(" Value int8 : %d \n", val->integer.val.int8);
			break;
		case INTEGER_16:
			printf(" Value int16 : %d \n", val->integer.val.int16);
			break;
		case INTEGER_32:
			printf(" Value int32 : %d \n", val->integer.val.int32);
			break;
		case INTEGER_64:
			printf(" Value int64 : %ld \n", (long int) val->integer.val.int64);
			break;
		}
		break;
	case BINARY_BASE64:
	case BINARY_HEX:
		printf(" Value Binary (len == %d) : ", val->binary.len);
		for (i = 0; i < val->binary.len; i++) {
			printf(" [%d]", val->binary.data[i]);
		}
		printf("\n");
		break;
	case BOOLEAN:
		printf(" Value Boolean : %d \n", val->boolean);
		break;
	case STRING:
		printf(" Value String (len==%d) : '", val->string.len);
		for (i = 0; i < val->string.len; i++) {
			printf("%c", (char) val->string.codepoints[i]);
		}
		printf("'\n");
		break;
	default:
		printf(" Value ?? \n");
	}
}

