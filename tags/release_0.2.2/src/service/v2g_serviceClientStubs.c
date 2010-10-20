

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

 
 #include "v2g_serviceDataTypes.h"
 #include "v2g_serviceClientStubs.h"
 #include "v2g_serviceDataSerializiation.h"
 #include "v2g_serviceClientDataTransmitter.h"
 #include "EXITypes.h"
 #include "EXIDecoder.h"
 #include "EXIEncoder.h"
 

static int deserializeMessage(struct v2gService* service);
 
/* call sessionSetup  */
int call_sessionSetup(struct v2gService* service, struct HeaderType* header, struct SessionSetupReqType* params, struct SessionSetupResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.SessionSetupReq = *params;
	service->v2gMsg.Body.isused.SessionSetupReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.SessionSetupRes;
 		
 	
	return 0;
}	

/* call serviceDiscovery  */
int call_serviceDiscovery(struct v2gService* service, struct HeaderType* header, struct ServiceDiscoveryReqType* params, struct ServiceDiscoveryResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.ServiceDiscoveryReq = *params;
	service->v2gMsg.Body.isused.ServiceDiscoveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.ServiceDiscoveryRes;
 		
 	
	return 0;
}	

/* call selectedServicePayment  */
int call_selectedServicePayment(struct v2gService* service, struct HeaderType* header, struct ServicePaymentSelectionReqType* params, struct ServicePaymentSelectionResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.ServicePaymentSelectionReq = *params;
	service->v2gMsg.Body.isused.ServicePaymentSelectionReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.ServicePaymentSelectionRes;
 		
 	
	return 0;
}	

/* call paymentDetails  */
int call_paymentDetails(struct v2gService* service, struct HeaderType* header, struct PaymentDetailsReqType* params, struct PaymentDetailsResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.PaymentDetailsReq = *params;
	service->v2gMsg.Body.isused.PaymentDetailsReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.PaymentDetailsRes;
 		
 	
	return 0;
}	

/* call powerDiscovery  */
int call_powerDiscovery(struct v2gService* service, struct HeaderType* header, struct PowerDiscoveryReqType* params, struct PowerDiscoveryResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.PowerDiscoveryReq = *params;
	service->v2gMsg.Body.isused.PowerDiscoveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.PowerDiscoveryRes;
 		
 	
	return 0;
}	

/* call lineLock  */
int call_lineLock(struct v2gService* service, struct HeaderType* header, struct LineLockReqType* params, struct LineLockResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.LineLockReq = *params;
	service->v2gMsg.Body.isused.LineLockReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.LineLockRes;
 		
 	
	return 0;
}	

/* call powerDelivery  */
int call_powerDelivery(struct v2gService* service, struct HeaderType* header, struct PowerDeliveryReqType* params, struct PowerDeliveryResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.PowerDeliveryReq = *params;
	service->v2gMsg.Body.isused.PowerDeliveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.PowerDeliveryRes;
 		
 	
	return 0;
}	

/* call meteringStatus  */
int call_meteringStatus(struct v2gService* service, struct HeaderType* header, struct MeteringStatusResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.isused.MeteringStatusReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.MeteringStatusRes;
 		
 	
	return 0;
}	

/* call meteringReceipt  */
int call_meteringReceipt(struct v2gService* service, struct HeaderType* header, struct MeteringReceiptReqType* params, struct MeteringReceiptResType* result)
{
	size_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = 0;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = 0;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* assign data to service data structure */
 	service->v2gMsg.Header = *header;
	service->v2gMsg.Body.MeteringReceiptReq = *params;
	service->v2gMsg.Body.isused.MeteringReceiptReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service)<0)
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	if(serviceDataTransmitter(service->outStream.data, *(service->outStream.pos), service->inStream.data)<0) 
 	{
		return -1;
 	}
 	
 	

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}
 	*result = service->v2gMsg.Body.MeteringReceiptRes;
 		
 	
	return 0;
}	

 

 /**
 * Deserialize an element value of the EXI stream and assign it to the
 * service data structure 
 */
static int deserializeElementCharacter(struct v2gService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 47: /*ResponseCode*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[2] == 50)
						{ 
							service->v2gMsg.Body.ServiceDiscoveryRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 55)
						{ 
							service->v2gMsg.Body.ServicePaymentSelectionRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 35)
						{ 
							service->v2gMsg.Body.PaymentDetailsRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 39)
						{ 
							service->v2gMsg.Body.PowerDeliveryRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 19)
						{ 
							service->v2gMsg.Body.MeteringReceiptRes.ResponseCode=service->val.enumeration;
							
						} else if(service->idPath.id[1] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.ResponseCode=service->val.enumeration;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 3: /*EVSEID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Body.SessionSetupRes.EVSEID.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Body.SessionSetupRes.EVSEID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 63: /*TCurrent*/
					if(service->val.type == INTEGER_64) 
					{
							service->v2gMsg.Body.SessionSetupRes.TCurrent=service->val.int64;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 16: /*MeteringAuthPubKey*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Body.ServicePaymentSelectionRes.MeteringAuthPubKey.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Body.ServicePaymentSelectionRes.MeteringAuthPubKey.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.ServicePaymentSelectionRes.isused.MeteringAuthPubKey=1;
				break;
				case 5: /*EVSEMaxPhases*/
					if(service->val.type == INTEGER_16) 
					{
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEMaxPhases=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 9: /*EnergyProvider*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PowerDiscoveryRes.EnergyProvider.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PowerDiscoveryRes.EnergyProvider.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.PowerDiscoveryRes.isused.EnergyProvider=1;
				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 35: /*SessionID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Header.SessionInformation.SessionID.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Header.SessionInformation.SessionID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 33: /*ServiceSessionID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Header.SessionInformation.ServiceSessionID.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Header.SessionInformation.ServiceSessionID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Header.SessionInformation.isused.ServiceSessionID=1;
				break;
				case 25: /*ProtocolVersion*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Header.SessionInformation.ProtocolVersion.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Header.SessionInformation.ProtocolVersion.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Header.SessionInformation.isused.ProtocolVersion=1;
				break;
				case 13: /*FaultCode*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Header.Notification.FaultCode=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Header.Notification.isused.FaultCode=1;
				break;
				case 14: /*FaultMsg*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Header.Notification.FaultMsg.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Header.Notification.FaultMsg.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Header.Notification.isused.FaultMsg=1;
				break;
				case 12: /*FatalError*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.FatalError=service->val.boolean;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.FatalError=service->val.boolean;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.FatalError=service->val.boolean;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.FatalError=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 7: /*EVSEStandby*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.EVSEStandby=service->val.boolean;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.EVSEStandby=service->val.boolean;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.EVSEStandby=service->val.boolean;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.EVSEStandby=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 4: /*ConnectorLocked*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.ConnectorLocked=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 24: /*PowerSwitchClosed*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 26: /*RCD*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.RCD=service->val.boolean;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.RCD=service->val.boolean;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.RCD=service->val.boolean;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.RCD=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 37: /*ShutDownTime*/
					if(service->val.type == INTEGER_64) 
					{
						 if(service->idPath.id[2] == 61)
						{ 
							service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ShutDownTime=service->val.int64;
							
						} else if(service->idPath.id[2] == 43)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEStatus.ShutDownTime=service->val.int64;
							
						} else if(service->idPath.id[2] == 13)
						{ 
							service->v2gMsg.Body.LineLockRes.EVSEStatus.ShutDownTime=service->val.int64;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEStatus.ShutDownTime=service->val.int64;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 29: /*ServiceID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceID.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 31: /*ServiceName*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceName.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceName.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceName=1;
				break;
				case 34: /*ServiceType*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceType=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceType=1;
				break;
				case 32: /*ServiceScope*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceScope.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceScope.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceScope=1;
				break;
				case 21: /*Multiplier*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[3] == 2)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPower.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 29)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxVoltage.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 30)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMinVoltage.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 8)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEVoltage.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 4)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEIMax.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 6)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEMaxPower.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 25)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.PCurrent.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 37)
						{ 
							service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryMaxPower.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterReading.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[7] == 47)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Multiplier=service->val.enumeration;
							
						} else if(service->idPath.id[6] == 6)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Multiplier=service->val.enumeration;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 50: /*Unit*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[3] == 2)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPower.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 29)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxVoltage.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 30)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMinVoltage.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 8)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEVoltage.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 4)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEIMax.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[3] == 6)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEMaxPower.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 25)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.PCurrent.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[2] == 37)
						{ 
							service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryMaxPower.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterReading.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[7] == 47)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Unit=service->val.enumeration;
							
						} else if(service->idPath.id[6] == 6)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Unit=service->val.enumeration;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 51: /*Value*/
					if(service->val.type == INTEGER_64) 
					{
						 if(service->idPath.id[3] == 2)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPower.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 29)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxVoltage.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 30)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMinVoltage.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 8)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEVoltage.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 4)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.EVSEIMax.Value=service->val.int64;
							
						} else if(service->idPath.id[3] == 6)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.EVSEMaxPower.Value=service->val.int64;
							
						} else if(service->idPath.id[2] == 25)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.PCurrent.Value=service->val.int64;
							
						} else if(service->idPath.id[2] == 37)
						{ 
							service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryMaxPower.Value=service->val.int64;
							
						} else if(service->idPath.id[1] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterReading.Value=service->val.int64;
							
						} else if(service->idPath.id[7] == 47)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Value=service->val.int64;
							
						} else if(service->idPath.id[6] == 6)
						{ 
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Value=service->val.int64;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 48: /*TariffStart*/
					if(service->val.type == UNSIGNED_INTEGER_32) 
					{
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffStart=service->val.uint32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 46: /*TariffID*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffID=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 41: /*TariffDescription*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffDescription.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffDescription.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].isused.TariffDescription=1;
				break;
				case 18: /*MeterPubKey*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterPubKey.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterPubKey.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterPubKey=1;
				break;
				case 20: /*MeterStatus*/
					if(service->val.type == INTEGER_16) 
					{
						 if(service->idPath.id[2] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterStatus=service->val.int32;
							
						} else if(service->idPath.id[1] == 17)
						{ 
							service->v2gMsg.Body.MeteringReceiptReq.MeterInfo.MeterStatus=service->val.int32;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterStatus=1;
				break;
				case 38: /*TMeter*/
					if(service->val.type == INTEGER_64) 
					{
						 if(service->idPath.id[2] == 23)
						{ 
							service->v2gMsg.Body.MeteringStatusRes.MeterInfo.TMeter=service->val.int64;
							
						} else if(service->idPath.id[1] == 17)
						{ 
							service->v2gMsg.Body.MeteringReceiptReq.MeterInfo.TMeter=service->val.int64;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.TMeter=1;
				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
	
	} /* close switch(service->eqn.namespaceURI) */
	return 0;
}
 
/**
 * Deserialize an element of the EXI stream
 * @return 0 = 0K; -1 = ERROR
 */
static int deserializeElement(struct v2gService* service)
{
	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 52:/* ServiceList */	

 					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryRes.isused.ServiceList=1;
				break;	
				case 16:/* MeteringAuthPubKey */	

 					/* is used */
					service->v2gMsg.Body.ServicePaymentSelectionRes.isused.MeteringAuthPubKey=1;
				break;	
				case 9:/* EnergyProvider */	

 					/* is used */
					service->v2gMsg.Body.PowerDiscoveryRes.isused.EnergyProvider=1;
				break;	
				case 65:/* TariffTable */	

 					/* is used */
					service->v2gMsg.Body.PowerDiscoveryRes.isused.TariffTable=1;
				break;	
				case 25:/* PCurrent */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.isused.PCurrent=1;
				break;	
				case 15:/* MeterInfo */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.isused.MeterInfo=1;
				break;	
				case 61:/* SessionSetupRes */	

 					/* is used */
					service->v2gMsg.Body.isused.SessionSetupRes=1;
				break;	
				case 50:/* ServiceDiscoveryRes */	

 					/* is used */
					service->v2gMsg.Body.isused.ServiceDiscoveryRes=1;
				break;	
				case 55:/* ServicePaymentSelectionRes */	

 					/* is used */
					service->v2gMsg.Body.isused.ServicePaymentSelectionRes=1;
				break;	
				case 35:/* PaymentDetailsRes */	

 					/* is used */
					service->v2gMsg.Body.isused.PaymentDetailsRes=1;
				break;	
				case 43:/* PowerDiscoveryRes */	

 					/* is used */
					service->v2gMsg.Body.isused.PowerDiscoveryRes=1;
				break;	
				case 13:/* LineLockRes */	

 					/* is used */
					service->v2gMsg.Body.isused.LineLockRes=1;
				break;	
				case 39:/* PowerDeliveryRes */	

 					/* is used */
					service->v2gMsg.Body.isused.PowerDeliveryRes=1;
				break;	
				case 23:/* MeteringStatusRes */	

 					/* is used */
					service->v2gMsg.Body.isused.MeteringStatusRes=1;
				break;	
				case 19:/* MeteringReceiptRes */	

 					/* is used */
					service->v2gMsg.Body.isused.MeteringReceiptRes=1;
				break;	
			}
		break;case 5:
			switch(service->eqn.localPart) {
				case 33:/* ServiceSessionID */	

 					/* is used */
					service->v2gMsg.Header.SessionInformation.isused.ServiceSessionID=1;
				break;	
				case 25:/* ProtocolVersion */	

 					/* is used */
					service->v2gMsg.Header.SessionInformation.isused.ProtocolVersion=1;
				break;	
				case 13:/* FaultCode */	

 					/* is used */
					service->v2gMsg.Header.Notification.isused.FaultCode=1;
				break;	
				case 14:/* FaultMsg */	

 					/* is used */
					service->v2gMsg.Header.Notification.isused.FaultMsg=1;
				break;	
				case 10:/* EventList */	

 					/* is used */
					service->v2gMsg.Header.Notification.isused.EventList=1;
				break;	
				case 31:/* ServiceName */	

 					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceName=1;
				break;	
				case 34:/* ServiceType */	

 					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceType=1;
				break;	
				case 32:/* ServiceScope */	

 					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceScope=1;
				break;	
				case 6:/* EPrice */	

 					/* is used */
					service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
				break;	
				case 41:/* TariffDescription */	

 					/* is used */
					service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].isused.TariffDescription=1;
				break;	
				case 16:/* MeterID */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterID=1;
				break;	
				case 18:/* MeterPubKey */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterPubKey=1;
				break;	
				case 19:/* MeterReading */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterReading=1;
				break;	
				case 20:/* MeterStatus */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterStatus=1;
				break;	
				case 38:/* TMeter */	

 					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.TMeter=1;
				break;	
			}
		break;case 6:
			switch(service->eqn.localPart) {
				case 6:/* Notification */	

 					/* is used */
					service->v2gMsg.Header.isused.Notification=1;
				break;	
			}
		break;
	}
	return 0;
}


 
 
 /** 
 * Deserialize the EXI stream
 * @return 0 = 0K; -1 = ERROR
 */
static int deserializeMessage(struct v2gService* service)
{
	int noEndOfDocument = 1; /* true */
	int errno=0;
	

	do {
			exiDecodeNextEvent(&(service->inStream), &(service->stateDecode), &(service->event));
			if (errno < 0) {
				printf("[ERROR] %d \n", errno);
				return errno;
			}

			switch (service->event) {
			case START_DOCUMENT:

				errno = exiDecodeStartDocument(&(service->inStream), &(service->stateDecode));

				break;
			case END_DOCUMENT:

				errno = exiDecodeEndDocument(&(service->inStream), &(service->stateDecode));
				noEndOfDocument = 0; /* false */
				break;
			case START_ELEMENT:
				errno = exiDecodeStartElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				service->idPath.id[service->idPath.pos++]=service->eqn.localPart;
				 
				break;
			case END_ELEMENT:

				errno = exiDecodeEndElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				service->idPath.pos--;
				 
				errno = deserializeElement(service);
				break;
			case CHARACTERS:
				/* decode */
				errno = exiDecodeCharacters(&(service->inStream), &(service->stateDecode), &(service->val));
				 
				/* assign character data to the v2g message structure */
				errno = deserializeElementCharacter(service);
				break;
			case ATTRIBUTE:
				/* decode */
				/*	errno = exiDecodeAttribute(&isStream, &stateDecode, &eqn, &val); */
				break;
			default:
				/* ERROR */
				return -1;
			}

		} while (noEndOfDocument);

	return 0;
}
 
 
 
 /* Initialize the v2g client */
 int init_v2gServiceClient(struct v2gService* service, bytes_t bytes, string_ucs_t string, uint8_t* inStream, size_t max_inStream_size, uint8_t* outStream, size_t max_outStream_size)
{

	/* init byte array */
	 service->val.binary = bytes;

	/* init string array */
	 service->val.string = string;

	 /* init input / output stream */
	 service->inStream.data=inStream;
	 service->inStream.size=max_inStream_size;

	 service->outStream.data=outStream;
	 service->outStream.size=max_outStream_size;


	return 0;
}

