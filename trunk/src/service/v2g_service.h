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
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_SERVICE_H_
#define EXI_SERVICE_H_

#include "v2g_dataTypes.h"
#include "EXITypes.h"

struct uniqueIDPath
{
	int id[10];
	size_t pos;
};


struct EXIService
{
	/* in-/ out-stream */
	bitstream_t inStream;
	bitstream_t outStream;

	/* EXI */
	exi_state_t stateDecode;
	exi_state_t stateEncode;
	exi_event_t event;
	uint16_t qnameID;
	exi_value_t val;

	/* v2g message data structure */
	struct EXIDocumentType exiMsg;

	/* unique id for ambiguous elements */
	struct uniqueIDPath idPath;

	/* error code */
	uint8_t errorCode;

	/* offset for transported header data */
	uint16_t transportHeaderOffset;
};


/* define error codes  */
#define EXI_NON_VALID_MESSAGE 0x01
#define EXI_SERIALIZATION_FAILED 0x02
#define EXI_DESERIALIZATION_FAILED 0x03
#define EXI_DATATYPE_FAILED 0x04
#define EXI_VALUE_RANGE_FAILED 0x05

#define EXI_UNKNOWN_ERROR 0xFF

#endif /* EXI_SERVICE_H_ */

#ifdef __cplusplus
}
#endif
