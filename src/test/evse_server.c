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
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/


/* includes for the application handshake protocol */
#include "appHand_service.h"
#include "appHand_dataTypes.h"
#include "v2g_service.h"
#include "v2gtp.h"
#include "evse_server.h"

#include "v2g_serviceDispatcher.h"

#include <stdio.h>


#define MAX_BYTE_SIZE 64
#define MAX_STRING_SIZE 64
#define MAX_STREAM_SIZE 100

static int appHandshakeHandler(struct EXIDatabinder* appHandService, uint8_t* inStream, uint16_t sizeInStream, uint8_t* outStream, uint16_t* outStreamLength);
static void printASCIIString(uint32_t* string, uint32_t len);

int testV2GService(uint8_t* inStream, uint16_t inStreamLength, uint8_t* outStream, uint16_t* outStreamLength)
{
	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/
	uint16_t exiMsgLength;
	uint8_t errn;

	 struct EXIDatabinder appHandService;
	struct EXIService service;

	static uint8_t isHandshake = 1;

	/* BINARY memory setup */
	exi_bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	exi_string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

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

	/* Here, it is assumed the first message is always the application handshake protocol.
	 * The successor messages are 15118 charging based messages and handled by the message
	 * dispatcher. */

	if(isHandshake)
		{



			/* init the de- / serializer */
			init_appHandDeserializer(&appHandService,bytes,string,V2GTP_HEADER_LENGTH);
			init_appHandSerializer(&appHandService,bytes,string,MAX_STREAM_SIZE,V2GTP_HEADER_LENGTH);

			if(appHandshakeHandler(&appHandService, inStream,inStreamLength,outStream,outStreamLength))
			{
				return -1; /* an error occured */
			}

			isHandshake = 0; /* here: next time a charging message is expected */
		}
	else
		{


		/****************************************************************************
		 * Pass the received EXI message stream (inStream + exiMsgLength) to the    *
		 * v2g message dispatcher. 	The outStream contains the response message     *
		 * stream.  																*
		 ****************************************************************************/
		errn = messageDispatcher(&service, inStream, exiMsgLength, outStream, MAX_STREAM_SIZE, outStreamLength);


		if(errn)
		{

			/* an error occurred; in such a case the outStream contains the generic error V2G message which
			 * can be response to the EV! */

		}
	}


	/* write v2gtp header */
	write_v2gtpHeader(outStream, outStreamLength, V2GTP_EXI_TYPE);



	return 0;

}


/** Example implementation of the app handshake protocol for the EVSE side  */
static int appHandshakeHandler(struct EXIDatabinder* appHandService, uint8_t* inStream, uint16_t sizeInStream, uint8_t* outStream, uint16_t* outStreamLength)
{
	struct EXIDocumentType_appHand exiDoc;
		struct SupportedAppProtocolReq handshake;
		struct SupportedAppProtocolRes resultHandshake;
		size_t i;

		init_SupportedAppProtocolReq(&handshake);
		init_EXIDocumentType_appHand(&exiDoc);

		/* we expect a supportedAppProtocolReq */
		exiDoc.supportedAppProtocolReq = &handshake;


		if(deserialize_appHand(appHandService,inStream,sizeInStream,&exiDoc))
		{
			/* an error occured */
			return -1;
		}

		printf("EVSE side: List of application handshake protocols of the EV \n");

		for(i=0;i<handshake.arraylen.AppProtocol;i++)
		{
			printf("\tProtocol entry #=%d\n",(i+1));
			printf("\t\tProtocolNamespace=");
			printASCIIString(handshake.AppProtocol[i].ProtocolNamespace.data,handshake.AppProtocol[i].ProtocolNamespace.arraylen.data);
			printf("\t\tVersion=%d.%d\n", handshake.AppProtocol[i].VersionNumberMajor,handshake.AppProtocol[i].VersionNumberMinor);
			printf("\t\tSchemaID=%d\n", handshake.AppProtocol[i].SchemaID);
			printf("\t\tPriority=%d\n", handshake.AppProtocol[i].Priority);
		}

		/* prepare response handshake response:
		 * it is assumed, we support the 15118 1.0 version :-) */
		resultHandshake.ResponseCode=OK_SuccessfulNegotiation_responseCodeType;
		resultHandshake.SchemaID=handshake.AppProtocol[0].SchemaID; /* signal the protocol by the provided schema id*/
		resultHandshake.isused.SchemaID=1;

		/* assign the response message to the exiDoc */
		init_EXIDocumentType_appHand(&exiDoc);
		exiDoc.supportedAppProtocolRes=&resultHandshake;
		exiDoc.isused.supportedAppProtocolRes=1;

		if(serialize_appHand(appHandService, outStream,outStreamLength, &exiDoc))
		{
			return -1;
		}


		return 0;
	}

static void printASCIIString(uint32_t* string, uint32_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%c",(char)string[i]);
	}
	printf("\n");
}


