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
 * @@version 0.5
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "evse_server.h"
#include "v2g_service.h"
#include "v2g_serviceDispatcher.h"
#include "v2gtp.h"

#define MAX_BYTE_SIZE 64
#define MAX_STRING_SIZE 64
#define MAX_STREAM_SIZE 100

int testV2GService(uint8_t* inStream, uint16_t inStreamLength, uint8_t* outStream, uint16_t* outStreamLength)
{
	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/


	uint16_t exiMsgLength;

	struct EXIService service;

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/**********************************************
	 * Init V2G server and initialize array types *
	 * for the EXI decoding	as well as the offset *
	 * for the transportation header			  *
	 **********************************************/

	init_v2gservice(&service, bytes, string, V2GTP_HEADER_LENGTH);

	/* check, if the DoIP header is correct and determine payload */
	if(read_v2gtpHeader(inStream,inStreamLength, &exiMsgLength))
	{
		/* v2gtp header not correct */
		return -1;
	}

	/****************************************************************************
	 * Pass the received EXI message stream (inStream + exiMsgLength) to the    *
	 * v2g message dispatcher. 	The outStream contains the response message     *
	 * stream.  																*
	 ****************************************************************************/

	if(messageDispatcher(&service, inStream, exiMsgLength, outStream, MAX_STREAM_SIZE, outStreamLength))
	{
		/* an error occured */

	}
	else
	{
		/* write v2gtp header */
		write_v2gtpHeader(outStream, outStreamLength, V2GTP_EXI_TYPE);

	}


	return 0;

}
