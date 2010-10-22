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
 * @version 0.2.2
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/



#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceClientStubs.h"
#include "EXITypes.h"

#include <stdio.h>

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 60

int main_service(int argc, char *argv[])
{

	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */

	/* service data structure */
	struct v2gService service;
	struct HeaderType v2gHeader;
	struct SessionSetupReqType sessionSetup;
	struct SessionSetupResType resultSessionSetup;
/*	struct PowerDiscoveryReqType powerDiscovery;
	struct PowerDiscoveryResType resultPowerDiscovery;
*/

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };



	printf("+++Start V2G Client / Service Example+++\n\n");

	/*******************
	 * Init V2G Client *
	 *******************/

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE);

	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionInformation.SessionID.arraylen.data = 0; /* no session id in the initial message -> array length = 0*/
	v2gHeader.SessionInformation.ProtocolVersion.data[0]='1'; /* assign protocol version number*/
	v2gHeader.SessionInformation.ProtocolVersion.arraylen.data=1; /* array string length =1 of protocol version */
	v2gHeader.SessionInformation.isused.ProtocolVersion = 1; /* important: signalize, protocol version is used */
	v2gHeader.isused.Notification=0; /* no notification */

	/* setup sessionSetup parameters */
	sessionSetup.isused.PEVID=1; /* no PEVID is transported */
	sessionSetup.PEVStatus.ChargerStandby=1; /* charger standby = true */
	sessionSetup.PEVStatus.ConnectorLocked=0; /* connector locked = false */


	printf("PEV: call EVSE sessionSetup\n");
	/*********************
	 * Call sessionSetup *
	 *********************/
	call_sessionSetup(&service,&v2gHeader,&sessionSetup,&resultSessionSetup);

	/* show results of the answer message of EVSE sessionSetup*/
	printf("PEV: received response message from EVSE\n");
	printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
	printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
	printf("\tEVSEStatus:\n\t\tConnectorLocked=%d\n",resultSessionSetup.EVSEStatus.ConnectorLocked);
	printf("\t\tEVSEStandby=%d\n",resultSessionSetup.EVSEStatus.EVSEStandby);
	printf("\t\tFatalError=%d\n",resultSessionSetup.EVSEStatus.FatalError);
	printf("\t\tPowerSwitchClosed=%d\n",resultSessionSetup.EVSEStatus.PowerSwitchClosed);
	printf("\t\tRCD=%d\n",resultSessionSetup.EVSEStatus.RCD);
	printf("\t\tShutDownTime=%lld\n",resultSessionSetup.EVSEStatus.ShutDownTime);
	printf("\tTCurrent=%lld\n",resultSessionSetup.TCurrent);

	printf("\n+++Terminate V2G Client / Service Example+++");

	return 0;
}

