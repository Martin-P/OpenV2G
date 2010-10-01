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
 * @version 0.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_server.h"
#include "v2g_service.h"
#include "v2g_serviceDispatcher.h"

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 60

int testV2GService(uint8_t* inStream, size_t inStreamLength, uint8_t* outStream)
{
	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	size_t posIn, posOut;

	struct v2gService service;

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/**********************************************
	 * Init V2G server and initialize array types *
	 * for the EXI decoding						  *
	 **********************************************/

	init_v2gservice(&service, bytes, string);

	/* assign the position where to read / write in the inStream / outStream */
	posIn=0;
	posOut=0;

	/****************************************************************************
	 * Pass the received EXI message stream (inStream + inStreamLength) to the  *
	 * message dispatcher. 	The outStream contains the response message stream. *
	 * posOut==length of outStream                                              *
	 ****************************************************************************/

	messageDispatcher(&service, inStream, inStreamLength, &posIn, outStream, MAX_STREAM_SIZE, &posOut);

	return 0;
}
