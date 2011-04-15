

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
 * @version 0.3.1
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

 
 #include "v2g_serviceDataTypes.h"
  #include "v2g_serviceDataTypes.c"
 #include "v2g_serviceClientStubs.h"
 #include "v2g_serviceDataSerialization.c"
 #include "v2g_serviceClientDataTransmitter.h"
 #include "EXITypes.h"
 #include "EXIDecoder.h"
 #include "EXIEncoder.h"
 

static int deserializeMessage(struct EXIService* service);
 
/** 
 * \brief   Calls the remote sessionSetup method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct SessionSetupReqType* Request data for the server (has to be set up before)
 * \param	result   struct SessionSetupResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_sessionSetup(struct EXIService* service, struct HeaderType* header, struct SessionSetupReqType* params, struct SessionSetupResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.SessionSetupReq = params;
	service->exiMsg.V2G_Message.Body.isused.SessionSetupReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.SessionSetupRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote serviceDiscovery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct ServiceDiscoveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct ServiceDiscoveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_serviceDiscovery(struct EXIService* service, struct HeaderType* header, struct ServiceDiscoveryReqType* params, struct ServiceDiscoveryResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq = params;
	service->exiMsg.V2G_Message.Body.isused.ServiceDiscoveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote selectedServicePayment method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct ServicePaymentSelectionReqType* Request data for the server (has to be set up before)
 * \param	result   struct ServicePaymentSelectionResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_selectedServicePayment(struct EXIService* service, struct HeaderType* header, struct ServicePaymentSelectionReqType* params, struct ServicePaymentSelectionResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq = params;
	service->exiMsg.V2G_Message.Body.isused.ServicePaymentSelectionReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote paymentDetails method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PaymentDetailsReqType* Request data for the server (has to be set up before)
 * \param	result   struct PaymentDetailsResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_paymentDetails(struct EXIService* service, struct HeaderType* header, struct PaymentDetailsReqType* params, struct PaymentDetailsResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.PaymentDetailsReq = params;
	service->exiMsg.V2G_Message.Body.isused.PaymentDetailsReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.PaymentDetailsRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote powerDiscovery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PowerDiscoveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct PowerDiscoveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_powerDiscovery(struct EXIService* service, struct HeaderType* header, struct PowerDiscoveryReqType* params, struct PowerDiscoveryResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.PowerDiscoveryReq = params;
	service->exiMsg.V2G_Message.Body.isused.PowerDiscoveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.PowerDiscoveryRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote lineLock method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct LineLockReqType* Request data for the server (has to be set up before)
 * \param	result   struct LineLockResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_lineLock(struct EXIService* service, struct HeaderType* header, struct LineLockReqType* params, struct LineLockResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.LineLockReq = params;
	service->exiMsg.V2G_Message.Body.isused.LineLockReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.LineLockRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote powerDelivery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PowerDeliveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct PowerDeliveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_powerDelivery(struct EXIService* service, struct HeaderType* header, struct PowerDeliveryReqType* params, struct PowerDeliveryResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.PowerDeliveryReq = params;
	service->exiMsg.V2G_Message.Body.isused.PowerDeliveryReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.PowerDeliveryRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote meteringStatus method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
  * \param	result   struct MeteringStatusResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_meteringStatus(struct EXIService* service, struct HeaderType* header, struct MeteringStatusResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.isused.MeteringStatusReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.MeteringStatusRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

/** 
 * \brief   Calls the remote meteringReceipt method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct MeteringReceiptReqType* Request data for the server (has to be set up before)
 * \param	result   struct MeteringReceiptResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_meteringReceipt(struct EXIService* service, struct HeaderType* header, struct MeteringReceiptReqType* params, struct MeteringReceiptResType* result)
{
	uint16_t posEncode, posDecode;
	
	/* init uniqueID stack */
	service->idPath.pos=0;
	
	/* init outStream data structure */
	posEncode = service->transportHeaderOffset;
	service->outStream.pos = &posEncode;
	service->outStream.buffer = 0;
	service->outStream.capacity = 8;
	
	/* init encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init inStream data structure */
	posDecode = service->transportHeaderOffset;
	service->inStream.pos = &posDecode;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	


	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));
	

	
	/* assign data to service data structure */
 	service->exiMsg.V2G_Message.Header = header;
	service->exiMsg.V2G_Message.Body.MeteringReceiptReq = params;
	service->exiMsg.V2G_Message.Body.isused.MeteringReceiptReq=1;
	
	/* encode data to exi stream*/
	if(serialize_message(service))
	{ 
	
		return -1;
	}
 
 	/* send data to server and wait for the response message */
 	service->errorCode=serviceDataTransmitter(service->outStream.data, (*(service->outStream.pos)-service->transportHeaderOffset), service->inStream.data);
 	if(service->errorCode) 
 	{
		return -1;
 	}
 	
 	

 	service->exiMsg.V2G_Message.Body.MeteringReceiptRes = result;

	/* init decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));

	/* deserilize the response message */
 	if(deserializeMessage(service)<0)
 	{
 	 
 		return -1;
 	}

 		
 	
	return 0;
}	

 

 /**
 * Deserialize an element value of the EXI stream and assign it to the
 * service data structure 
 */
static int deserializeElementCharacter(struct EXIService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 44: /*ResponseCode*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 47)
						{ 
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 52)
						{ 
							service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 32)
						{ 
							service->exiMsg.V2G_Message.Body.PaymentDetailsRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 36)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->ResponseCode=service->val.enumeration;
							
							
						} else if(service->idPath.id[2] == 17)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringReceiptRes->ResponseCode=service->val.enumeration;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 2: /*EVSEID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					if(service->idPath.id[2]==58)
					{
						/* array copy and array length assignment */
						memcpy(service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEID.arraylen.data = service->val.binary.len;
					}
					else
					{
						memcpy(service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEID.arraylen.data = service->val.binary.len;

					}
				}
				else
				{
					return -1; /* wrong data type */
				}
		
				break;
				case 60: /*TCurrent*/
					if(service->val.type == INTEGER_32) 
					{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->TCurrent=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 4: /*EVSEMaxPhases*/
					if(service->val.type == INTEGER_16) 
					{
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEMaxPhases=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 8: /*EnergyProvider*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EnergyProvider.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EnergyProvider.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->isused.EnergyProvider=1;
				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 34: /*SessionID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.data, service->val.binary.data,service->val.binary.len);
					service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 32: /*ServiceSessionID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.data, service->val.binary.data,service->val.binary.len);
					service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Header->SessionInformation.isused.ServiceSessionID=1;
				break;
				case 24: /*ProtocolVersion*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Header->SessionInformation.isused.ProtocolVersion=1;
				break;
				case 9: /*Event*/
					if(service->val.type == ENUMERATION) 
					{
							service->exiMsg.V2G_Message.Header->Notification.EventList.Event=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 13: /*FaultCode*/
					if(service->val.type == ENUMERATION) 
					{
							service->exiMsg.V2G_Message.Header->Notification.FaultCode=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Header->Notification.isused.FaultCode=1;
				break;
				case 14: /*FaultMsg*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Header->Notification.FaultMsg.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Header->Notification.FaultMsg.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Header->Notification.isused.FaultMsg=1;
				break;
				case 12: /*FatalError*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.FatalError=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.FatalError=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.FatalError=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.FatalError=service->val.boolean;
							
							
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
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.EVSEStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.EVSEStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.EVSEStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.EVSEStandby=service->val.boolean;
							
							
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
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.ConnectorLocked=service->val.boolean;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 23: /*PowerSwitchClosed*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.PowerSwitchClosed=service->val.boolean;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 25: /*RCD*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.RCD=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.RCD=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.RCD=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.RCD=service->val.boolean;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 36: /*ShutDownTime*/
					if(service->val.type == INTEGER_32) 
					{
						 if(service->idPath.id[2] == 58)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.ShutDownTime=service->val.int32;
							
							
						} else if(service->idPath.id[2] == 40)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEStatus.ShutDownTime=service->val.int32;
							
							
						} else if(service->idPath.id[2] == 12)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.ShutDownTime=service->val.int32;
							
							
						} else if(service->idPath.id[2] == 21)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.ShutDownTime=service->val.int32;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 28: /*ServiceID*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceID.data, service->val.binary.data,service->val.binary.len);
					service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceID.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 30: /*ServiceName*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceName.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceName.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceName=1;
				break;
				case 33: /*ServiceType*/
					if(service->val.type == ENUMERATION) 
					{
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceType=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceType=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceType=1;
				break;
				case 31: /*ServiceScope*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceScope.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceScope.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceScope=1;
				break;
				case 20: /*Multiplier*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[3] == 7)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEVoltage.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 3)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEIMax.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 5)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 23)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Multiplier=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.PCurrent=1;
							
							
						} else if(service->idPath.id[1] == 0)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Multiplier=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterReading=1;
							
							
						} else if(service->idPath.id[7] == 46)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[7] == 6)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Multiplier=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 49: /*Unit*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[3] == 7)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEVoltage.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 3)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEIMax.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 5)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 23)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Unit=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.PCurrent=1;
							
							
						} else if(service->idPath.id[1] == 0)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Unit=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterReading=1;
							
							
						} else if(service->idPath.id[7] == 46)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[7] == 6)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Unit=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 50: /*Value*/
					if(service->val.type == INTEGER_32) 
					{
						 if(service->idPath.id[3] == 7)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEVoltage.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 3)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->EVSEIMax.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 5)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 23)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Value=service->val.int32;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.PCurrent=1;
							
							
						} else if(service->idPath.id[1] == 0)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Value=service->val.int32;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterReading=1;
							
							
						} else if(service->idPath.id[7] == 46)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Value=service->val.int32;
							
							
						} else if(service->idPath.id[7] == 6)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Value=service->val.int32;
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 47: /*TariffStart*/
					if(service->val.type == UNSIGNED_INTEGER_32) 
					{
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffStart=service->val.uint32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 45: /*TariffID*/
					if(service->val.type == ENUMERATION) 
					{
							service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffID=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 40: /*TariffDescription*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffDescription.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffDescription.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].isused.TariffDescription=1;
				break;
				case 5: /*Currency*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Currency.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Currency.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 16: /*MeterID*/
		
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
			service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterID=1;
				break;
				case 19: /*MeterStatus*/
					if(service->val.type == INTEGER_16) 
					{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterStatus=service->val.int32;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.MeterInfo=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterStatus=1;
				break;
				case 37: /*TMeter*/
					if(service->val.type == INTEGER_32) 
					{

							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.TMeter=service->val.int32;
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.MeterInfo=1;
							

					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.TMeter=1;
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
static int deserializeElement(struct EXIService* service)
{
	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 49:/* ServiceList */	

						/* is used */
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->isused.ServiceList=1;			  
				break;	
				case 8:/* EnergyProvider */	

						/* is used */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->isused.EnergyProvider=1;			  
				break;	
				case 62:/* TariffTable */	

						/* is used */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->isused.TariffTable=1;			  
				break;	
				case 23:/* PCurrent */	

						/* is used */
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.PCurrent=1;			  
				break;	
				case 14:/* MeterInfo */	

						/* is used */
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.MeterInfo=1;			  
				break;	
				case 58:/* SessionSetupRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.SessionSetupRes=1;			  
				break;	
				case 47:/* ServiceDiscoveryRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.ServiceDiscoveryRes=1;			  
				break;	
				case 52:/* ServicePaymentSelectionRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.ServicePaymentSelectionRes=1;			  
				break;	
				case 32:/* PaymentDetailsRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.PaymentDetailsRes=1;			  
				break;	
				case 40:/* PowerDiscoveryRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.PowerDiscoveryRes=1;			  
				break;	
				case 12:/* LineLockRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.LineLockRes=1;			  
				break;	
				case 36:/* PowerDeliveryRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.PowerDeliveryRes=1;			  
				break;	
				case 21:/* MeteringStatusRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.MeteringStatusRes=1;			  
				break;	
				case 17:/* MeteringReceiptRes */	

						/* is used */
						service->exiMsg.V2G_Message.Body.isused.MeteringReceiptRes=1;			  
				break;	
			}
		break;case 5:
			switch(service->eqn.localPart) {
				case 32:/* ServiceSessionID */	

						/* is used */
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ServiceSessionID=1;			  
				break;	
				case 24:/* ProtocolVersion */	

						/* is used */
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ProtocolVersion=1;			  
				break;	
				case 13:/* FaultCode */	

						/* is used */
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultCode=1;			  
				break;	
				case 14:/* FaultMsg */	

						/* is used */
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultMsg=1;			  
				break;	
				case 10:/* EventList */	

						/* is used */
						service->exiMsg.V2G_Message.Header->Notification.isused.EventList=1;			  
				break;	
				case 30:/* ServiceName */	

						/* is used */
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceName=1;			  
				break;	
				case 31:/* ServiceScope */	

						/* is used */
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceScope=1;			  
				break;	
				case 26:/* Service */	

					 	/* increment */
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service++;			  
				break;	
				case 6:/* EPrice */	

						/* is used */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;			  
				break;	
				case 43:/* TariffEntry */	

					 	/* increment */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry++;			  
				break;	
				case 40:/* TariffDescription */	

						/* is used */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff].isused.TariffDescription=1;			  
				break;	
				case 38:/* Tariff */	

					 	/* increment */
						service->exiMsg.V2G_Message.Body.PowerDiscoveryRes->TariffTable.arraylen.Tariff++;			  
				break;	
				case 16:/* MeterID */	

						/* is used */
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterID=1;			  
				break;	
				case 18:/* MeterReading */	

						/* is used */
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterReading=1;			  
				break;	
			}
		break;case 7:
			switch(service->eqn.localPart) {
				case 1:/* Notification */	

						/* is used */
						service->exiMsg.V2G_Message.Header->isused.Notification=1;			  
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
static int deserializeMessage(struct EXIService* service)
{
	int noEndOfDocument = 1; /* true */
	int returnCode=0;
	

	do {
			exiDecodeNextEvent(&(service->inStream), &(service->stateDecode), &(service->event));
			if (returnCode < 0) {
				printf("[ERROR] %d \n", returnCode);
				return returnCode;
			}

			switch (service->event) {
			case START_DOCUMENT:

				returnCode = exiDecodeStartDocument(&(service->inStream), &(service->stateDecode));

				break;
			case END_DOCUMENT:

				returnCode = exiDecodeEndDocument(&(service->inStream), &(service->stateDecode));
				noEndOfDocument = 0; /* false */
				break;
			case START_ELEMENT:
				returnCode = exiDecodeStartElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				service->idPath.id[service->idPath.pos++]=service->eqn.localPart;
				 
				break;
			case END_ELEMENT:

				returnCode = exiDecodeEndElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				service->idPath.pos--;
				 
				returnCode = deserializeElement(service);
				break;
			case CHARACTERS:
				/* decode */
				returnCode = exiDecodeCharacters(&(service->inStream), &(service->stateDecode), &(service->val));
				 
				/* assign character data to the v2g message structure */
				returnCode = deserializeElementCharacter(service);
				break;
			case ATTRIBUTE:
				/* decode */
				/*	returnCode = exiDecodeAttribute(&isStream, &stateDecode, &eqn, &val); */
				break;
			default:
				/* ERROR */
				return -1;
			}

		} while (noEndOfDocument);

	return 0;
}
 
 
 
 /* Initialize the v2g client */
int init_v2gServiceClient(struct EXIService* service, bytes_t bytes, string_ucs_t string, uint8_t* inStream, size_t max_inStream_size, uint8_t* outStream, size_t max_outStream_size, uint16_t transportHeaderOffset)
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

	/* init offset for transport protocoll */
	 service->transportHeaderOffset=transportHeaderOffset;

	return 0;
}

