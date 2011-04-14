
/*
 * Copyright (C) 2007-2011 Siemens AG
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
 * @version 0.4
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

/*
 * This file implements the DoIP header writer and reader.
 * Note: Not all functions are implemented yet.
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "doIP.h"

int write_doIPNack(uint8_t* outStream, uint16_t* outStreamLength, uint8_t nackCode)
{
/*	if(outStreamLength<DOIP_HEADER_LENGTH+1)
		return -1;*/

	/* payload length=1 and nack payload type*/
	*outStreamLength = 1;

	write_doIPHeader(outStream,outStreamLength, DOIP_NEGATIVE_ACKNOWLEDGE);
	outStream[8]=nackCode;

	return 0;
}

int write_doIPHeader(uint8_t* outStream, uint16_t* outStreamLength, uint16_t payloadType)
{

	/* write DoIP version number 1=byte */
	outStream[0]=DOIP_VERSION;

	/* write inverse DoIP version */
	outStream[1]=DOIP_VERSION_INV;


	/* write payload type */
	outStream[2] = (uint8_t)(payloadType & 0xFF);
	outStream[3] = (uint8_t)(payloadType >> 8 & 0xFF);

	/* write payload length */
	outStream[4] = (uint8_t)(*outStreamLength & 0xFF);
	outStream[5] = (uint8_t)(*outStreamLength>>8 & 0xFF);
	outStream[6] = (uint8_t)(*outStreamLength>>16 & 0xFF);
	outStream[7] = (uint8_t)(*outStreamLength>>24 & 0xFF);

	/* here, the outStream length have to be resized by the DoIP offset*/
	*outStreamLength += DOIP_HEADER_LENGTH;

	return 0;
}

int read_doIPHeader(uint8_t* inStream, uint16_t inStreamLength, uint16_t* payloadLength)
{
	uint16_t payloadType=0;


	/* check, if we support this DoIP version */
	if(inStream[0]!=DOIP_VERSION && inStream[1]!=DOIP_VERSION_INV)
		return DOIP_INCORRECT_PATTERN_FORMAT;


	/* check, if we support this payload type*/
	payloadType = inStream[3];
	payloadType = (payloadType << 8 | inStream[2]);

	if(payloadType != DOIP_EXI_TYPE && payloadType != DOIP_NEGATIVE_ACKNOWLEDGE)
		return DOIP_UNKNOWN_PAYLOAD_TYPE;


	/* determine payload length*/
	*payloadLength = inStream[7];
	*payloadLength = (*payloadLength << 8 | inStream[6]);
	*payloadLength = (*payloadLength << 16 | inStream[5]);
	*payloadLength = (*payloadLength << 24 | inStream[4]);

	if((*payloadLength+DOIP_HEADER_LENGTH)!=inStreamLength)
		return DOIP_INVALID_PAYLOAD_LENGTH;

	/* if payload is a NACK read its NACK code and return it*/
	/* TODO: should be handled by an extra method */
	if(payloadType == DOIP_NEGATIVE_ACKNOWLEDGE)
				return inStream[8];


	return 0;
}

