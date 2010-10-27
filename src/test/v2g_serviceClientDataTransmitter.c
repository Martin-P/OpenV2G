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
 * @version 0.3
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceClientDataTransmitter.h"
#include "v2g_server.h"
#include "doip.h"

/* This method has to be implemented!
 * Send EXI stream (outStream) to EVSE and receive response stream (inStream)*/
int serviceDataTransmitter(uint8_t* outStream, size_t outStreamLength, uint8_t* inStream)
{
	/* send output stream to the underlying network to the EVSE and wait for response
	 * --> here provide data to the V2G server directly*/

	size_t inStreamLength = 0;
	size_t payloadLength = 0;

	/* setup DoIP header information; outStreamLength==payloadLength*/
	write_doIPHeader(outStream,&outStreamLength,DOIP_EXI_TYPE);

	/* send data to EVSE server (add DoIP offset)*/
	testV2GService(outStream, outStreamLength, inStream, &inStreamLength);

	return read_doIPHeader(inStream,inStreamLength, &payloadLength);
}
