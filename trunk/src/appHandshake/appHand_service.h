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
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.6
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_DATABINDER_H_
#define EXI_DATABINDER_H_

#include "appHand_dataTypes.h"

struct uniqueIDPath2
{
	int id[10];
	size_t pos;
};


struct EXIDatabinder
{
	/* in-/ out-stream */
	bitstream_t inStream;
	bitstream_t outStream;

	/* EXI */
	exi_state_t stateDecode;
	exi_state_t stateEncode;
	exi_event_t event;
	eqname_t eqn;
	exi_value_t val;

	/* main message data structure */
	struct EXIDocumentType_appHand exiMsg;

	/* unique id for ambiguous elements */
	struct uniqueIDPath2 idPath;

	uint16_t transportHeaderOffset;

	/* error code */
	uint8_t errorCode;
};

int serialize_appHand(struct EXIDatabinder* service, uint8_t* outStream, uint16_t* outPos, struct EXIDocumentType_appHand* exiDoc);
int deserialize_appHand(struct EXIDatabinder* service, uint8_t* inStream, uint16_t sizeInStream, struct EXIDocumentType_appHand* exiDoc);
int init_appHandSerializer(struct EXIDatabinder* service, bytes_t bytes, string_ucs_t string, size_t max_outStream_size, uint16_t transportHeaderOffset);
int init_appHandDeserializer(struct EXIDatabinder* service, bytes_t bytes, string_ucs_t string, uint16_t transportHeaderOffset);



/* define error codes (TODO: define precise error codes) */
#define EXI_NON_VALID_MESSAGE 0x01
#define EXI_SERIALIZATION_FAILED 0x02

#define EXI_UNKNOWN_ERROR 0xFF

#endif /* EXI_DATABINDER_H_ */

#ifdef __cplusplus
}
#endif
