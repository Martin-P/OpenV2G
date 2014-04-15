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
 * @version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer.com</p>
 ********************************************************************/



#ifndef EXI_appHand_ENCODER_C
#define EXI_appHand_ENCODER_C

#include "EXITypes.h"
#include "EXIOptions.h"
#include "BitOutputStream.h"
#include "EncoderChannel.h"

#include "StringTable.h"
#include "appHandNameTableEntries.h"
#include "MethodsBag.h"

#include "EXIOptions.h"

#include "appHandEXICoder.h"
#include "EXIHeaderEncoder.h"
#include "ErrorCodes.h"
#include "appHandQNames.h"
#include "appHandQNameDefines.h"




/* local variables */
static uint32_t bits;
static int errn;

/* ==================================== */

static int _encodeNBitIntegerValue(bitstream_t* stream, exi_integer_t* iv, uint16_t nbits, int32_t lowerBound) {
	int errn;
	uint32_t val;
	switch(iv->type) {
	/* Unsigned Integer */
	case EXI_UNSIGNED_INTEGER_8:
		val = iv->val.int8 - lowerBound;
		break;
	case EXI_UNSIGNED_INTEGER_16:
		val = iv->val.int16 - lowerBound;
		break;
	case EXI_UNSIGNED_INTEGER_32:
		val = (uint32_t)(iv->val.int32 - lowerBound);
		break;
	case EXI_UNSIGNED_INTEGER_64:
		val = (uint32_t)(iv->val.int64 - lowerBound);
		break;
	/* (Signed) Integer */
	case EXI_INTEGER_8:
		val = iv->val.uint8 - lowerBound;
		break;
	case EXI_INTEGER_16:
		val = iv->val.uint16 - lowerBound;
		break;
	case EXI_INTEGER_32:
		val = iv->val.uint32 - lowerBound;
		break;
	case EXI_INTEGER_64:
		val = (uint32_t)(iv->val.uint64 - lowerBound);
		break;
	default:
		return EXI_UNSUPPORTED_INTEGER_VALUE_TYPE;
		break;
	}

	errn = encodeNBitUnsignedInteger(stream, nbits, val);
	return errn;
}



static int _exiValueToString(exi_value_t* val) {
	if (val->type == EXI_DATATYPE_STRING) {
		return 0;
	} else {
		/* TODO convert typed value to string */
		return EXI_ERROR_CONVERSION_TYPE_TO_STRING;
	}
}



static int _exiEncodeEventCode2(bitstream_t* stream, exi_state_t* state, exi_event_t event2) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}


static int _exiEncodeNamespaceUriHit(bitstream_t* stream, exi_state_t* state, uint16_t uriID) {
	int errn;
	uint16_t uriCodingLength;
	uint16_t uriSize;

	errn = exiGetUriSize(&state->nameTablePrepopulated, &state->nameTableRuntime, &uriSize);
	if (errn) {
		return errn;
	}
	/* URI Entries + 1 */
	errn = exiGetCodingLength(uriSize + 1, &uriCodingLength);
	if (errn) {
		return errn;
	}

	/* uri string value found */
	/* ==> value(i+1) is encoded as n-bit unsigned integer */
	errn = encodeNBitUnsignedInteger(stream, uriCodingLength, uriID+1);

	return errn;
}


static int _exiEncodeNamespaceMiss(bitstream_t* stream, exi_state_t* state,
		exi_string_ucs_t* uri, uint16_t* uriID) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}



static int _exiEncodeLocalNameHit(bitstream_t* stream, exi_state_t* state,
		uint16_t uriID, uint16_t localNameID) {
	int errn;
	uint16_t localNameSize;
	uint16_t localNameCodingLength;

	/* string value found in local partition */
	/* ==> string value is represented as zero (0) encoded as an */
	errn = encodeUnsignedInteger32(stream, 0 );
	if (errn < 0) {
		return errn;
	}
	/* Unsigned Integer followed by an the compact identifier of the */
	/* string value as an n-bit unsigned integer n is log2 m and m is */
	/* the number of entries in the string table partition */
	errn = exiGetLocalNameSize(&state->nameTablePrepopulated, &state->nameTableRuntime, uriID, &localNameSize);
	if (errn < 0) {
		return errn;
	}
	errn = exiGetCodingLength(localNameSize, &localNameCodingLength);
	if (errn) {
		return errn;
	}
	errn = encodeNBitUnsignedInteger(stream, localNameCodingLength, localNameID);
	return errn;

}


static int _exiEncodeLocalNameMiss(bitstream_t* stream, exi_state_t* state,
		exi_string_ucs_t* localName, uint16_t uriID, uint16_t* localNameID) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}


static int _encodeAttributeXsiTypeContent(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val) {

	/* encode qname */
	errn = _exiEncodeNamespaceUriHit(stream, state, val->eqname.namespaceURI);
	if (errn < 0) {
		return errn;
	}
	errn = _exiEncodeLocalNameHit(stream, state, val->eqname.namespaceURI, val->eqname.localPart);
	if (errn < 0) {
		return errn;
	}

	/* handle xsi type cast */
	errn = exi_appHand_HandleXsiType(state, &val->eqname);

	return errn;
}


static int _exiEncodeStartElement(bitstream_t* stream, uint16_t nbits,
		uint32_t val, exi_state_t* state, uint16_t qnameID, uint16_t stackId,
		uint16_t newState) {
	/* event-code */
	int errn = encodeNBitUnsignedInteger(stream, nbits, val);
	if (errn) {
		return errn;
	}
	/* move on */
	state->grammarStack[state->stackIndex] = stackId;
	/* push element on stack */
	return exi_appHand_PushStack(state, newState, qnameID);
}


static int _exiEncodeEndElementUndeclared(bitstream_t* stream, exi_state_t* state) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}

static int _encode2ndLevelAttribute(bitstream_t* stream, exi_state_t* state, uint16_t qnameID,
		exi_value_t* val) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}


int exiappHandEncodeListValue(bitstream_t* stream, exi_state_t* state, uint16_t qnameID, exi_value_t* val, exi_list_t lt) {

	switch(lt.type) {
	case EXI_DATATYPE_BINARY_BASE64:
	case EXI_DATATYPE_BINARY_HEX:
		errn = encodeBinary(stream, &val->binary);
		break;
	case EXI_DATATYPE_BOOLEAN:
		errn = encodeBoolean(stream, val->boolean);
		break;
	case EXI_DATATYPE_BOOLEAN_FACET:
		errn = encodeNBitUnsignedInteger(stream, 2, val->boolean ? 2 : 0);
		break;
	case EXI_DATATYPE_DECIMAL:
		errn = encodeDecimal(stream, &val->decimal);
		break;
	case EXI_DATATYPE_FLOAT:
		errn = encodeFloat(stream, &val->float_me);
		break;
	case EXI_DATATYPE_NBIT_UNSIGNED_INTEGER:
		errn = EXI_UNSUPPORTED_LIST_VALUE_TYPE;
		break;
	case EXI_DATATYPE_UNSIGNED_INTEGER:
		errn = encodeUnsignedInteger(stream, &val->integer);
		break;
	case EXI_DATATYPE_INTEGER:
		errn = encodeInteger(stream, &val->integer);
		break;
	case EXI_DATATYPE_DATETIME:
		errn = encodeDateTime(stream, &val->datetime);
		break;
	case EXI_DATATYPE_STRING:
		errn = encodeStringValue(stream, state, qnameID, &val->str);
		break;
	default:
		return EXI_UNSUPPORTED_LIST_VALUE_TYPE;
	}

	return errn;
}


#ifndef __GNUC__
#pragma warning( disable : 4100 ) /* warning unreferenced parameter 'stream' */
#endif /* __GNUC__ */
int exiappHandEncodeStartDocument(bitstream_t* stream, exi_state_t* state) {
	if ( state->grammarStack[state->stackIndex] == 0 ) {
		/* move on */
		state->grammarStack[state->stackIndex] = 13;
		return 0;
	} 
	if ( state->grammarStack[state->stackIndex] == 0 ) {
		/* move on */
		state->grammarStack[state->stackIndex] = 13;
		return 0;
	} 
	if ( state->grammarStack[state->stackIndex] == 105 ) {
		/* move on */
		state->grammarStack[state->stackIndex] = 42;
		return 0;
	} 

	return EXI_ERROR_UNEXPECTED_START_DOCUMENT;
}
#ifndef __GNUC__
#pragma warning( default : 4100 ) /* warning unreferenced parameter 'stream' */
#endif /* __GNUC__ */


#ifndef __GNUC__
#pragma warning( disable : 4100 ) /* warning unreferenced parameter 'stream' */
#endif /* __GNUC__ */
int exiappHandEncodeEndDocument(bitstream_t* stream, exi_state_t* state) {
	if ( state->grammarStack[state->stackIndex] == 42) {
		encodeFinish(stream);
		return 0;
	} 
	if ( state->grammarStack[state->stackIndex] == 14) {
		encodeFinish(stream);
		return 0;
	} 

	return EXI_ERROR_UNEXPECTED_END_DOCUMENT;
}
#ifndef __GNUC__
#pragma warning( default : 4100 ) /* warning unreferenced parameter 'stream' */
#endif /* __GNUC__ */


int exiappHandInitEncoder(bitstream_t* stream, exi_state_t* state,
		exi_name_table_runtime_t runtimeTable, exi_string_table_t stringTable) {
#if EXI_appHandVALUE_PARTITION_CAPACITY != 0
#if EXI_appHandVALUE_MAX_LENGTH != 0
	int i;
#endif /* EXI_appHandVALUE_MAX_LENGTH != 0 */
#endif /* EXI_appHandVALUE_PARTITION_CAPACITY != 0 */
	/* init grammar state */
	state->stackIndex = 0;
	state->grammarStack[0] = DOCUMENT;
	/* name tables */
	state->nameTablePrepopulated = exiappHandNameTablePrepopulated;
	state->nameTableRuntime = runtimeTable;
	/* next qname ID */
	state->nextQNameID = EXI_appHandNUMBER_OF_PREPOPULATED_QNAMES;
	/* string tables */
	state->stringTable = stringTable;
	state->stringTable.numberOfGlobalStrings = 0;
#if EXI_appHandVALUE_PARTITION_CAPACITY != 0
#if EXI_appHandVALUE_MAX_LENGTH != 0
	for(i=0; i<(state->stringTable.sizeLocalStrings); i++) {
		state->stringTable.numberOfLocalStrings[i] = 0;
	}
#endif /* EXI_appHandVALUE_MAX_LENGTH != 0 */
#endif /* EXI_appHandVALUE_PARTITION_CAPACITY != 0 */

	/* runtime grammars */
	state->numberOfRuntimeGrammars = 0;

	/* Avoid warning: Unused declaration of variable 'name' */
	bits = 0;

	/* encode header */
	return writeEXIHeader(stream);
}


int exiappHandEncodeStartElement(bitstream_t* stream, exi_state_t* state, uint16_t qnameID) {
	uint16_t namespaceUriID, localNameID;
	int16_t currentID = state->grammarStack[state->stackIndex];
	errn = EXI_ERROR_UNEXPECTED_START_ELEMENT;

	switch (currentID) {
	case 3:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 4, 5);
			break;
		}
		break;
	case 4:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 124, 5);
			break;
		}
		break;
	case 5:
		/* FirstStartTag[START_ELEMENT(ProtocolNamespace)] */ 
		switch(qnameID) {
		case 2:
			/* SE( ProtocolNamespace ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 31, 18);
			break;
		}
		break;
	case 8:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 9, 5);
			break;
		}
		break;
	case 9:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 92, 5);
			break;
		}
		break;
	case 13:
		/* DocContent[START_ELEMENT({urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq), START_ELEMENT({urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes), START_ELEMENT_GENERIC] */ 
		switch(qnameID) {
		case 65:
			/* SE( {urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 14, 15);
			break;
		case 66:
			/* SE( {urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes ) */
			errn = _exiEncodeStartElement(stream, 2, 1, state, qnameID, 14, 16);
			break;
		}
		break;
	case 15:
		/* FirstStartTag[START_ELEMENT(AppProtocol)] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 3, 5);
			break;
		}
		break;
	case 16:
		/* FirstStartTag[START_ELEMENT(ResponseCode)] */ 
		switch(qnameID) {
		case 3:
			/* SE( ResponseCode ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 66, 44);
			break;
		}
		break;
	case 26:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 27, 5);
			break;
		}
		break;
	case 27:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 97, 5);
			break;
		}
		break;
	case 30:
		/* Element[START_ELEMENT(ProtocolNamespace)] */ 
		switch(qnameID) {
		case 2:
			/* SE( ProtocolNamespace ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 31, 18);
			break;
		}
		break;
	case 31:
		/* Element[START_ELEMENT(VersionNumberMajor)] */ 
		switch(qnameID) {
		case 5:
			/* SE( VersionNumberMajor ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 33, 46);
			break;
		}
		break;
	case 33:
		/* Element[START_ELEMENT(VersionNumberMinor)] */ 
		switch(qnameID) {
		case 6:
			/* SE( VersionNumberMinor ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 34, 35);
			break;
		}
		break;
	case 34:
		/* Element[START_ELEMENT(SchemaID)] */ 
		switch(qnameID) {
		case 4:
			/* SE( SchemaID ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 90, 45);
			break;
		}
		break;
	case 42:
		/* FragmentContent[START_ELEMENT(AppProtocol), START_ELEMENT(Priority), START_ELEMENT(ProtocolNamespace), START_ELEMENT(ResponseCode), START_ELEMENT(SchemaID), START_ELEMENT(VersionNumberMajor), START_ELEMENT(VersionNumberMinor), START_ELEMENT({urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq), START_ELEMENT({urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes), START_ELEMENT_GENERIC, END_DOCUMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 4, 0, state, qnameID, 42, 5);
			break;
		case 1:
			/* SE( Priority ) */
			errn = _exiEncodeStartElement(stream, 4, 1, state, qnameID, 42, 43);
			break;
		case 2:
			/* SE( ProtocolNamespace ) */
			errn = _exiEncodeStartElement(stream, 4, 2, state, qnameID, 42, 18);
			break;
		case 3:
			/* SE( ResponseCode ) */
			errn = _exiEncodeStartElement(stream, 4, 3, state, qnameID, 42, 44);
			break;
		case 4:
			/* SE( SchemaID ) */
			errn = _exiEncodeStartElement(stream, 4, 4, state, qnameID, 42, 45);
			break;
		case 5:
			/* SE( VersionNumberMajor ) */
			errn = _exiEncodeStartElement(stream, 4, 5, state, qnameID, 42, 46);
			break;
		case 6:
			/* SE( VersionNumberMinor ) */
			errn = _exiEncodeStartElement(stream, 4, 6, state, qnameID, 42, 35);
			break;
		case 65:
			/* SE( {urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolReq ) */
			errn = _exiEncodeStartElement(stream, 4, 7, state, qnameID, 42, 15);
			break;
		case 66:
			/* SE( {urn:iso:15118:2:2010:AppProtocol}supportedAppProtocolRes ) */
			errn = _exiEncodeStartElement(stream, 4, 8, state, qnameID, 42, 16);
			break;
		}
		break;
	case 60:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 61, 5);
			break;
		}
		break;
	case 61:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 26, 5);
			break;
		}
		break;
	case 66:
		/* Element[START_ELEMENT(SchemaID), END_ELEMENT] */ 
		switch(qnameID) {
		case 4:
			/* SE( SchemaID ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 129, 45);
			break;
		}
		break;
	case 72:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 73, 5);
			break;
		}
		break;
	case 73:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 109, 5);
			break;
		}
		break;
	case 90:
		/* Element[START_ELEMENT(Priority)] */ 
		switch(qnameID) {
		case 1:
			/* SE( Priority ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 127, 43);
			break;
		}
		break;
	case 92:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 113, 5);
			break;
		}
		break;
	case 94:
		/* Element[START_ELEMENT(AppProtocol)] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 3, 5);
			break;
		}
		break;
	case 97:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 39, 5);
			break;
		}
		break;
	case 109:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 110, 5);
			break;
		}
		break;
	case 110:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 60, 5);
			break;
		}
		break;
	case 113:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 115, 5);
			break;
		}
		break;
	case 115:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 72, 5);
			break;
		}
		break;
	case 117:
		/* Element[START_ELEMENT(ResponseCode)] */ 
		switch(qnameID) {
		case 3:
			/* SE( ResponseCode ) */
			errn = _exiEncodeStartElement(stream, 1, 0, state, qnameID, 66, 44);
			break;
		}
		break;
	case 124:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 125, 5);
			break;
		}
		break;
	case 125:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 128, 5);
			break;
		}
		break;
	case 128:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */ 
		switch(qnameID) {
		case 0:
			/* SE( AppProtocol ) */
			errn = _exiEncodeStartElement(stream, 2, 0, state, qnameID, 8, 5);
			break;
		}
		break;

	default:
		/* element qname not expected */
		return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
	}

	return errn;
}



int exiappHandEncodeStartElementNS(bitstream_t* stream,
		exi_state_t* state, uint16_t namespaceUriID,
		exi_string_ucs_t* localName) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}


int exiappHandEncodeStartElementGeneric(bitstream_t* stream,
		exi_state_t* state, exi_string_ucs_t* namespaceUri,
		exi_string_ucs_t* localName) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}



int exiappHandEncodeEndElement(bitstream_t* stream, exi_state_t* state) {
	int errn = 0;
	int16_t currentID = state->grammarStack[state->stackIndex];
	switch (currentID) {
	case 22:
		/* FirstStartTag[ATTRIBUTE_GENERIC, START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
	case 50:
		/* FirstStartTag[ATTRIBUTE_GENERIC, START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		errn = encodeNBitUnsignedInteger(stream, 3, 2);
		break;
	case 2:
		/* Element[END_ELEMENT] */
	case 39:
		/* Element[END_ELEMENT] */
	case 127:
		/* Element[END_ELEMENT] */
	case 129:
		/* Element[END_ELEMENT] */
		errn = encodeNBitUnsignedInteger(stream, 1, 0);
		break;
	case 3:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 8:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 26:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 60:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 72:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 23:
		/* Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
	case 9:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 97:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 109:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 92:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 115:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 124:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 27:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 51:
		/* Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
	case 128:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 66:
		/* Element[START_ELEMENT(SchemaID), END_ELEMENT] */
	case 110:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 61:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 113:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 4:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 125:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
	case 73:
		/* Element[START_ELEMENT(AppProtocol), END_ELEMENT] */
		errn = encodeNBitUnsignedInteger(stream, 2, 1);
		break;

	default:
		return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
	}

	if (errn < 0) {
		return errn;
	}

	/* pop item */
	return exi_appHand_PopStack(state);
}



int exiappHandEncodeCharacters(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val) {
	int16_t moveOnID = 0;
	int deviantChars = 0;

	int16_t currentID = state->grammarStack[state->stackIndex];
	switch (currentID) {
		case 43:
		/* FirstStartTag[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 5, 1);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 65:
	case 95:
	case 140:
		/* Element[CHARACTERS[LIST]] */
		if (val->type == EXI_DATATYPE_LIST) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeUnsignedInteger32(stream, val->list.len);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 51:
		/* Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 2, 2);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 51;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 2, 3);
			encodeNBitUnsignedInteger(stream, 1, 1);
			deviantChars = 1;
		}
		break;
	case 37:
		/* Element[CHARACTERS[BOOLEAN]] */
		if (val->type == EXI_DATATYPE_BOOLEAN) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBoolean(stream, val->boolean);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 56:
		/* Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 8, -128);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 19:
		/* Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 5, 1);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 44:
		/* FirstStartTag[CHARACTERS[ENUMERATION]] */
		if (val->type == EXI_DATATYPE_ENUMERATION) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeNBitUnsignedInteger(stream, 2, val->enumeration);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 53:
		/* FirstStartTag[CHARACTERS[DECIMAL]] */
		if (val->type == EXI_DATATYPE_DECIMAL) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeDecimal(stream, &val->decimal);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 11:
	case 130:
		/* FirstStartTag[CHARACTERS[FLOAT]] */
		if (val->type == EXI_DATATYPE_FLOAT) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeFloat(stream, &val->float_me);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 116:
		/* Element[CHARACTERS[DECIMAL]] */
		if (val->type == EXI_DATATYPE_DECIMAL) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeDecimal(stream, &val->decimal);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 25:
	case 29:
	case 144:
		/* FirstStartTag[CHARACTERS[LIST]] */
		if (val->type == EXI_DATATYPE_LIST) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeUnsignedInteger32(stream, val->list.len);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 50:
		/* FirstStartTag[ATTRIBUTE_GENERIC, START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 3, 3);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 51;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 3, 4);
			encodeNBitUnsignedInteger(stream, 3, 5);
			deviantChars = 1;
		}
		break;
	case 46:
	case 35:
		/* First(xsi:type)StartTag[CHARACTERS[UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeUnsignedInteger(stream, &val->integer);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 12:
	case 32:
	case 38:
	case 40:
	case 41:
	case 54:
	case 67:
	case 70:
	case 77:
	case 85:
	case 87:
	case 96:
	case 114:
	case 118:
	case 120:
	case 131:
	case 137:
		/* Element[CHARACTERS[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 23:
		/* Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 2, 2);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 23;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 2, 3);
			encodeNBitUnsignedInteger(stream, 1, 1);
			deviantChars = 1;
		}
		break;
	case 111:
		/* FirstStartTag[CHARACTERS[BINARY_BASE64]] */
		if (val->type == EXI_DATATYPE_BINARY_BASE64) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBinary(stream, &val->binary);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 28:
		/* Element[CHARACTERS[BINARY_HEX]] */
		if (val->type == EXI_DATATYPE_BINARY_HEX) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBinary(stream, &val->binary);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 17:
	case 47:
	case 83:
	case 91:
	case 107:
	case 136:
		/* Element[CHARACTERS[INTEGER]] */
		if (val->type == EXI_DATATYPE_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeInteger(stream, &val->integer);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 62:
	case 103:
		/* Element[CHARACTERS[FLOAT]] */
		if (val->type == EXI_DATATYPE_FLOAT) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeFloat(stream, &val->float_me);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 52:
		/* Element[CHARACTERS[BINARY_BASE64]] */
		if (val->type == EXI_DATATYPE_BINARY_BASE64) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBinary(stream, &val->binary);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 132:
		/* FirstStartTag[CHARACTERS[BINARY_HEX]] */
		if (val->type == EXI_DATATYPE_BINARY_HEX) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBinary(stream, &val->binary);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 7:
	case 21:
	case 49:
	case 57:
	case 102:
		/* FirstStartTag[CHARACTERS[UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeUnsignedInteger(stream, &val->integer);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 45:
	case 122:
		/* FirstStartTag[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 8, 0);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 64:
	case 74:
	case 99:
	case 100:
	case 104:
	case 112:
	case 133:
	case 135:
		/* FirstStartTag[CHARACTERS[DATETIME]] */
		if (val->type == EXI_DATATYPE_DATETIME) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeDateTime(stream, &val->datetime);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 1:
	case 75:
		/* Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 8, 0);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 68:
	case 69:
	case 76:
	case 89:
	case 93:
	case 138:
		/* FirstStartTag[CHARACTERS[INTEGER]] */
		if (val->type == EXI_DATATYPE_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeInteger(stream, &val->integer);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 134:
		/* FirstStartTag[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_NBIT_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = _encodeNBitIntegerValue(stream, &val->integer, 8, -128);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 71:
		/* Element[CHARACTERS[ENUMERATION]] */
		if (val->type == EXI_DATATYPE_ENUMERATION) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeNBitUnsignedInteger(stream, 2, val->enumeration);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 59:
	case 81:
	case 108:
	case 119:
	case 145:
		/* Element[CHARACTERS[UNSIGNED_INTEGER]] */
		if (val->type == EXI_DATATYPE_UNSIGNED_INTEGER) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeUnsignedInteger(stream, &val->integer);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 80:
		/* FirstStartTag[CHARACTERS[BOOLEAN]] */
		if (val->type == EXI_DATATYPE_BOOLEAN) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeBoolean(stream, val->boolean);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 63:
	case 82:
	case 84:
	case 88:
	case 121:
	case 123:
	case 126:
	case 139:
		/* Element[CHARACTERS[DATETIME]] */
		if (val->type == EXI_DATATYPE_DATETIME) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeDateTime(stream, &val->datetime);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 2, 2);
			deviantChars = 1;
		}
		break;
	case 10:
	case 18:
	case 20:
	case 24:
	case 36:
	case 48:
	case 55:
	case 58:
	case 78:
	case 79:
	case 86:
	case 98:
	case 101:
	case 106:
	case 141:
	case 142:
	case 143:
		/* FirstStartTag[CHARACTERS[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 1, 0);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 2;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 1, 1);
			encodeNBitUnsignedInteger(stream, 3, 6);
			deviantChars = 1;
		}
		break;
	case 22:
		/* FirstStartTag[ATTRIBUTE_GENERIC, START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		if (val->type == EXI_DATATYPE_STRING) {
			encodeNBitUnsignedInteger(stream, 3, 3);
			errn = encodeStringValue(stream, state, state->elementStack[state->stackIndex], &val->str);
			moveOnID = 23;
		} else { 
			/* deviant characters */ 
			encodeNBitUnsignedInteger(stream, 3, 4);
			encodeNBitUnsignedInteger(stream, 3, 5);
			deviantChars = 1;
		}
		break;

	default:
		return EXI_ERROR_UNEXPECTED_CHARACTERS;
	}

	if (currentID < 0) {
		/* TODO runtime rules */
		errn = EXI_ERROR_UNEXPECTED_CHARACTERS;
	} else if (deviantChars) {
		return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
	} else {
		/* move on */
		state->grammarStack[state->stackIndex] = moveOnID;
	}

	return errn;
}


int exiappHandEncodeAttribute(bitstream_t* stream, exi_state_t* state, uint16_t qnameID,
		exi_value_t* val) {
	int16_t moveOnID = 0;
	int16_t currentID = state->grammarStack[state->stackIndex];
	errn = EXI_ERROR_UNEXPECTED_ATTRIBUTE;

	switch (currentID) {

	}

	/* no expected attribute */
	if (currentID < 0) {
		/* runtime element */
		errn = _encode2ndLevelAttribute(stream, state, qnameID, val);
	} else {
		if(moveOnID == 0) {
			/* no action yet */
#if EXI_appHandSTRICT != 0
			/* no 2nd level events in strict mode for schema-informed grammars */
			errn = EXI_ERROR_UNEXPECTED_ATTRIBUTE;
#else /* EXI_appHandSTRICT != 0 */
			errn = _encode2ndLevelAttribute(stream, state, qnameID, val);
#endif /* EXI_appHandSTRICT != 0 */
		} else {
			state->grammarStack[state->stackIndex] = moveOnID;
		}
	}

	return errn;
}


int exiappHandEncodeAttributeNS(bitstream_t* stream,
		exi_state_t* state, uint16_t namespaceUriID,
		exi_string_ucs_t* localName, exi_value_t* val) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}

int exiappHandEncodeAttributeGeneric(bitstream_t* stream,
		exi_state_t* state, exi_string_ucs_t* namespaceUri,
		exi_string_ucs_t* localName, exi_value_t* val) {
	return EXI_DEVIANT_SUPPORT_NOT_DEPLOYED;
}


int exiappHandEncodeAttributeXsiNil(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val) {

	switch (state->grammarStack[state->stackIndex]) {

	}

	if (errn < 0) {
		return errn;
	}

	errn = encodeBoolean(stream, val->boolean);
	if (!errn && val->boolean) {
		/* handle xsi:nil == true */
		 errn = exi_appHand_HandleXsiNilTrue(state);
	}
	return errn;
}



int exiappHandEncodeAttributeXsiType(bitstream_t* stream, exi_state_t* state,
		exi_value_t* val) {
	/* encode xsi:type event code */
	switch (state->grammarStack[state->stackIndex]) {
	case 46:
		errn = encodeNBitUnsignedInteger(stream, 1, 1);
		if(errn) return errn;
		errn = encodeNBitUnsignedInteger(stream, 3, 1);
		break;
	case 35:
		errn = encodeNBitUnsignedInteger(stream, 1, 1);
		if(errn) return errn;
		errn = encodeNBitUnsignedInteger(stream, 3, 1);
		break;

	default:
		return EXI_ERROR_UNEXPECTED_ATTRIBUTE_XSI_TYPE;
	}
	if (errn) {
		return errn;
	}

	/* encode qname */
	errn = _encodeAttributeXsiTypeContent(stream, state, val);

	return errn;
}




#endif

