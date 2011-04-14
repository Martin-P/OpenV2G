

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
 * @version 0.3.2
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
 * \brief   Calls the remote chargeParameterDiscovery method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct ChargeParameterDiscoveryReqType* Request data for the server (has to be set up before)
 * \param	result   struct ChargeParameterDiscoveryResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_chargeParameterDiscovery(struct EXIService* service, struct HeaderType* header, struct ChargeParameterDiscoveryReqType* params, struct ChargeParameterDiscoveryResType* result)
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
	service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryReq = params;
	service->exiMsg.V2G_Message.Body.isused.ChargeParameterDiscoveryReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes = result;

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
 * \brief   Calls the remote cableCheck method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct CableCheckReqType* Request data for the server (has to be set up before)
 * \param	result   struct CableCheckResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_cableCheck(struct EXIService* service, struct HeaderType* header, struct CableCheckReqType* params, struct CableCheckResType* result)
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
	service->exiMsg.V2G_Message.Body.CableCheckReq = params;
	service->exiMsg.V2G_Message.Body.isused.CableCheckReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.CableCheckRes = result;

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
 * \brief   Calls the remote preCharge method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct PreChargeReqType* Request data for the server (has to be set up before)
 * \param	result   struct PreChargeResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_preCharge(struct EXIService* service, struct HeaderType* header, struct PreChargeReqType* params, struct PreChargeResType* result)
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
	service->exiMsg.V2G_Message.Body.PreChargeReq = params;
	service->exiMsg.V2G_Message.Body.isused.PreChargeReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.PreChargeRes = result;

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
 * \brief   Calls the remote currentDemand method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct CurrentDemandReqType* Request data for the server (has to be set up before)
 * \param	result   struct CurrentDemandResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_currentDemand(struct EXIService* service, struct HeaderType* header, struct CurrentDemandReqType* params, struct CurrentDemandResType* result)
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
	service->exiMsg.V2G_Message.Body.CurrentDemandReq = params;
	service->exiMsg.V2G_Message.Body.isused.CurrentDemandReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.CurrentDemandRes = result;

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
 * \brief   Calls the remote weldingDetection method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct WeldingDetectionReqType* Request data for the server (has to be set up before)
 * \param	result   struct WeldingDetectionResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_weldingDetection(struct EXIService* service, struct HeaderType* header, struct WeldingDetectionReqType* params, struct WeldingDetectionResType* result)
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
	service->exiMsg.V2G_Message.Body.WeldingDetectionReq = params;
	service->exiMsg.V2G_Message.Body.isused.WeldingDetectionReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.WeldingDetectionRes = result;

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
 * \brief   Calls the remote terminateCharging method
 * \param	service  struct EXIService* Service data structure (has to be initialized before)
 * \param	header   struct HeaderType* Header data structure
 * \param	params   struct TerminateChargingReqType* Request data for the server (has to be set up before)
 * \param	result   struct TerminateChargingResType* Contains the response data from the server 
 * \return  0 = 0K; -1 = ERROR */
int call_terminateCharging(struct EXIService* service, struct HeaderType* header, struct TerminateChargingReqType* params, struct TerminateChargingResType* result)
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
	service->exiMsg.V2G_Message.Body.TerminateChargingReq = params;
	service->exiMsg.V2G_Message.Body.isused.TerminateChargingReq=1;
	
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
 	
 	

 	service->exiMsg.V2G_Message.Body.TerminateChargingRes = result;

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
				case 66: /*ResponseCode*/

				if(service->val.type == ENUMERATION) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 69)
						{
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 74)
						{
							service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 54)
						{
							service->exiMsg.V2G_Message.Body.PaymentDetailsRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 35)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->ResponseCode = service->val.enumeration;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->ResponseCode = service->val.enumeration;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 16: /*EVSEID*/

				if(service->val.type == BINARY_HEX) 
					{
						if( service->idPath.id[2] == 80)
						{
							memcpy(service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEID.arraylen.data = service->val.binary.len;

						} else if(service->idPath.id[2] == 39)
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
				case 82: /*TCurrent*/

				if(service->val.type == INTEGER_32) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->TCurrent = service->val.int32;

						} else if(service->idPath.id[2] == 54)
						{
							service->exiMsg.V2G_Message.Body.PaymentDetailsRes->TCurrent = service->val.int32;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->TCurrent = service->val.int32;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 18: /*EVSEMaxPhases*/

				if(service->val.type == INTEGER_16) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxPhases = service->val.int32;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 26: /*EnergyProvider*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EnergyProvider.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EnergyProvider.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->isused.EnergyProvider=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 36: /*SessionID*/

				if(service->val.type == BINARY_HEX) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Header->SessionInformation.SessionID.arraylen.data = service->val.binary.len;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 34: /*ServiceSessionID*/

				if(service->val.type == BINARY_HEX) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Header->SessionInformation.ServiceSessionID.arraylen.data = service->val.binary.len;
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ServiceSessionID=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 25: /*ProtocolVersion*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Header->SessionInformation.ProtocolVersion.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Header->SessionInformation.isused.ProtocolVersion=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 10: /*Event*/

				if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Header->Notification.EventList.Event = service->val.enumeration;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 14: /*FaultCode*/

				if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Header->Notification.FaultCode = service->val.enumeration;
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultCode=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 15: /*FaultMsg*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Header->Notification.FaultMsg.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Header->Notification.FaultMsg.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Header->Notification.isused.FaultMsg=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 13: /*FatalError*/

				if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.FatalError = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.FatalError = service->val.boolean;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 8: /*EVSEStandby*/

				if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.EVSEStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.EVSEStandby = service->val.boolean;
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
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.ConnectorLocked = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.ConnectorLocked = service->val.boolean;
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
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.PowerSwitchClosed = service->val.boolean;
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
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.RCD = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.RCD = service->val.boolean;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 38: /*ShutDownTime*/

				if(service->val.type == INTEGER_32) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.ShutDownTime = service->val.int32;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.ShutDownTime = service->val.int32;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 0: /*ChargerStandby*/

				if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.ChargerStandby = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.ChargerStandby = service->val.boolean;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 7: /*EVSEMalfunction*/

				if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.EVSEMalfunction = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.EVSEMalfunction = service->val.boolean;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 39: /*StopCharging*/

				if(service->val.type == BOOLEAN) 
					{
						if( service->idPath.id[2] == 80)
						{
							service->exiMsg.V2G_Message.Body.SessionSetupRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 30)
						{
							service->exiMsg.V2G_Message.Body.LineLockRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 58)
						{
							service->exiMsg.V2G_Message.Body.PowerDeliveryRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 39)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 2)
						{
							service->exiMsg.V2G_Message.Body.CableCheckRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEStatus.StopCharging = service->val.boolean;

						} else if(service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEStatus.StopCharging = service->val.boolean;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 30: /*ServiceID*/

				if(service->val.type == BINARY_HEX) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceID.data, service->val.binary.data,service->val.binary.len);
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceID.arraylen.data = service->val.binary.len;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 32: /*ServiceName*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceName.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceName.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceName=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 35: /*ServiceType*/

				if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceType = service->val.enumeration;
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceType=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 33: /*ServiceScope*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceScope.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceScope.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceScope=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 21: /*Multiplier*/

				if(service->val.type == INTEGER_16) 
					{
						if( service->idPath.id[3] == 20)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 22)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 17)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 21)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 41)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEPresentVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 23)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentCurrent.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEPresentVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEPresentVoltage.Multiplier = service->val.int32;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Multiplier = service->val.int32;

						} else if(service->idPath.id[7] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Multiplier = service->val.int32;

						} else if(service->idPath.id[7] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Multiplier = service->val.int32;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 52: /*Unit*/

				if(service->val.type == ENUMERATION) 
					{
						if( service->idPath.id[3] == 20)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 22)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 17)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 21)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 41)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEPresentVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 23)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentCurrent.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEPresentVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEPresentVoltage.Unit = service->val.enumeration;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Unit = service->val.enumeration;

						} else if(service->idPath.id[7] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Unit = service->val.enumeration;

						} else if(service->idPath.id[7] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Unit = service->val.enumeration;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 53: /*Value*/

				if(service->val.type == INTEGER_32) 
					{
						if( service->idPath.id[3] == 20)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 22)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 17)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMaxCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 21)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->EVSEMinCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->EVSEMaxPower.Value = service->val.int32;

						} else if(service->idPath.id[3] == 41)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->PCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 62)
						{
							service->exiMsg.V2G_Message.Body.PreChargeRes->EVSEPresentVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 12)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 23)
						{
							service->exiMsg.V2G_Message.Body.CurrentDemandRes->EVSEPresentCurrent.Value = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 92)
						{
							service->exiMsg.V2G_Message.Body.WeldingDetectionRes->EVSEPresentVoltage.Value = service->val.int32;

						} else if(service->idPath.id[3] == 24 && service->idPath.id[2] == 87)
						{
							service->exiMsg.V2G_Message.Body.TerminateChargingRes->EVSEPresentVoltage.Value = service->val.int32;

						} else if(service->idPath.id[4] == 19)
						{
							service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterReading.Value = service->val.int32;

						} else if(service->idPath.id[7] == 49)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffPMax.Value = service->val.int32;

						} else if(service->idPath.id[7] == 6)
						{
							service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].EPrice.Value = service->val.int32;
						}

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 50: /*TariffStart*/

				if(service->val.type == UNSIGNED_INTEGER_32) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffStart = service->val.uint32;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 48: /*TariffID*/

				if(service->val.type == ENUMERATION) 
					{
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffID = service->val.enumeration;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 43: /*TariffDescription*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffDescription.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffDescription.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].isused.TariffDescription=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 5: /*Currency*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Currency.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Currency.arraylen.data = service->val.string.len;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 17: /*MeterID*/

				if(service->val.type == STRING) 
					{
						memcpy(service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterID=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 20: /*MeterStatus*/

				if(service->val.type == INTEGER_16) 
					{
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.MeterStatus = service->val.int32;
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterStatus=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

				break;
				case 40: /*TMeter*/

				if(service->val.type == INTEGER_32) 
					{
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.TMeter = service->val.int32;
						service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.TMeter=1;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		

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
				case 71:/* ServiceList */	

								service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->isused.ServiceList=1;
		  
				break;	
				case 84:/* TariffTable */	

								service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->isused.TariffTable=1;
		  
				break;	
				case 41:/* PCurrent */	

								service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.PCurrent=1;
		  
				break;	
				case 32:/* MeterInfo */	

								service->exiMsg.V2G_Message.Body.MeteringStatusRes->isused.MeterInfo=1;
		  
				break;	

			}
		break;
		case 5:
			switch(service->eqn.localPart) {
				case 11:/* EventList */	

								service->exiMsg.V2G_Message.Header->Notification.isused.EventList=1;
		  
				break;	
				case 28:/* Service */	

								service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service++;
		  
				break;	
				case 6:/* EPrice */	

								service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
		  
				break;	
				case 46:/* TariffEntry */	

								service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.Tariff[service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry++;
		  
				break;	
				case 41:/* Tariff */	

								service->exiMsg.V2G_Message.Body.ChargeParameterDiscoveryRes->TariffTable.arraylen.Tariff++;
		  
				break;	
				case 19:/* MeterReading */	

								service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterReading=1;
		  
				break;	

			}
		break;
		case 7:
			switch(service->eqn.localPart) {
				case 1:/* Notification */	

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

