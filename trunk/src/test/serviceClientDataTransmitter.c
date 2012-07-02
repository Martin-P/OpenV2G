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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @@version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#include "v2g_serviceClientDataTransmitter.h"
#include "evse_server.h"
#include "v2gtp.h"



void binaryToBits(uint8_t x)
{
	uint8_t cnt, mask = 1 << 7;

	for(cnt=1;cnt<=8;++cnt)
	{
		printf("%c",((x & mask) == 0) ? '0' : '1');
		x <<= 1;
	}
}

/*
 * Send EXI stream (outStream) to EVSE and receive a response stream (inStream)*/
int serviceDataTransmitter(uint8_t* outStream, uint32_t outStreamLength, uint8_t* inStream)
{
	/* send output stream to the underlying network to the EVSE and wait for response
	 * --> here provide data to the V2G server directly*/

	uint32_t inStreamLength = 0;
	uint32_t payloadLength = 0;

	printf("\nEXI request message size=%d bytes\n",outStreamLength);



	/* setup v2gtp header information; outStreamLength==payloadLength*/
	write_v2gtpHeader(outStream,&outStreamLength,V2GTP_EXI_TYPE);


/*	uint8_t* outStream2 = {1,254,128,1,0,0,0,33,128,154,2,2,192,0,0,0,0,0,0,16,209,64,22,64,200,8,1,146,64,12,3,32,40,128,50,50,8,201,208,4,0};*/
/*	uint8_t outStream2[] = {0x01, 0xFE, 0x80, 0x01, 0x00, 0x00, 0x00, 0x21, 0x80, 0x9A, 0x02, 0x02, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xD1, 0x40, 0x16, 0x40, 0xC8, 0x08, 0x01, 0x92, 0x40, 0x0C, 0x03, 0x20, 0x28, 0x80, 0x32, 0x32, 0x08, 0xC9, 0xD0, 0x04, 0x00};
	outStreamLength = 41;
*/


	/* send data to EVSE server (add v2g offset)*/
	testV2GService(outStream, outStreamLength, inStream, &inStreamLength);

	read_v2gtpHeader(inStream,inStreamLength, &payloadLength);

	printf("\nEXI response message size=%d bytes\n",payloadLength);


	return 0;
}
