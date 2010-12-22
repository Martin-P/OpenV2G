


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


#include "v2g_service.h"
#include "v2g_serviceDispatcher.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceDataTypes.c"
#include "v2g_serviceMethods.h"
#include "v2g_serviceDataSerialization.c"
#include "EXITypes.h"
#include "EXIDecoder.h"
#include "EXIEncoder.h"


static int deserializeMessage(struct EXIService* service);

/**
 * Deserialize an element value of the EXI stream and assign it to the
 * service data structure 
 */
static int deserializeElementCharacter(struct EXIService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 24: /*PEVID*/
		
				if(service->val.type == STRING) 
				{
					if(service->idPath.id[2] == 56)
					{
						/* string copy and string length assignment */
						memcpy(service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.SessionSetupReq->isused.PEVID=1;
					}
					else
					{
						/* string copy and string length assignment */
						memcpy(service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVID.arraylen.data = service->val.string.len;
						service->exiMsg.V2G_Message.Body.MeteringReceiptReq->isused.PEVID=1;
					}
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 55: /*ServiceType*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[1] == 0)
						{ 
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceType=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceType=1;
							
							
						} else if(service->idPath.id[1] == 0)
						{ 
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].ServiceType=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.Service[service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes->ServiceList.arraylen.Service].isused.ServiceType=1;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceType=1;*/
				break;
				case 54: /*ServiceScope*/
		
				if(service->val.type == STRING) 
				{
					/* string copy and string length assignment */
					memcpy(service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceScope.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
					service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->ServiceScope.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceScope=1;*/
				break;
				case 0: /*ContractID*/
		
				if(service->val.type == STRING) 
				{
					/* string copy and string length assignment */
					memcpy(service->exiMsg.V2G_Message.Body.PaymentDetailsReq->ContractID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
					service->exiMsg.V2G_Message.Body.PaymentDetailsReq->ContractID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 9: /*EoC*/
					if(service->val.type == INTEGER_32) 
					{
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->EoC=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 25: /*PEVMaxPhases*/
					if(service->val.type == INTEGER_16) 
					{
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxPhases=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 42: /*ReqLockStatus*/
					if(service->val.type == BOOLEAN) 
					{
							service->exiMsg.V2G_Message.Body.LineLockReq->ReqLockStatus=service->val.boolean;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 43: /*ReqSwitchStatus*/
					if(service->val.type == BOOLEAN) 
					{
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->ReqSwitchStatus=service->val.boolean;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 61: /*Tariff*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[2] == 34)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->Tariff=service->val.enumeration;
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->isused.Tariff=1;
							
							
						} else if(service->idPath.id[2] == 15)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->Tariff=service->val.enumeration;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.PowerDeliveryReq->isused.Tariff=1;*/
				break;
				case 60: /*TCurrent*/
					if(service->val.type == INTEGER_32) 
					{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->TCurrent=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.MeteringReceiptReq->isused.TCurrent=1;*/
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
					/*service->exiMsg.V2G_Message.Header->SessionInformation.isused.ServiceSessionID=1;*/
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
					/*service->exiMsg.V2G_Message.Header->SessionInformation.isused.ProtocolVersion=1;*/
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
					/*service->exiMsg.V2G_Message.Header->Notification.isused.FaultCode=1;*/
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
					/*service->exiMsg.V2G_Message.Header->Notification.isused.FaultMsg=1;*/
				break;
				case 4: /*ConnectorLocked*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 56)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 38)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 10)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockReq->PEVStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 34)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->PEVStatus.ConnectorLocked=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 15)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVStatus.ConnectorLocked=service->val.boolean;
							
							
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
						 if(service->idPath.id[2] == 56)
						{ 
							service->exiMsg.V2G_Message.Body.SessionSetupReq->PEVStatus.ChargerStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 38)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVStatus.ChargerStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 10)
						{ 
							service->exiMsg.V2G_Message.Body.LineLockReq->PEVStatus.ChargerStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 34)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDeliveryReq->PEVStatus.ChargerStandby=service->val.boolean;
							
							
						} else if(service->idPath.id[2] == 15)
						{ 
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->PEVStatus.ChargerStandby=service->val.boolean;
							
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 20: /*Multiplier*/
					if(service->val.type == ENUMERATION) 
					{
						 if(service->idPath.id[3] == 1)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->EAmount.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 26)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxPower.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 27)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxVoltage.Multiplier=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMinVoltage.Multiplier=service->val.enumeration;
							
							
						}else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Multiplier=service->val.enumeration;

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
						 if(service->idPath.id[3] == 1)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->EAmount.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 26)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxPower.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 27)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxVoltage.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMinVoltage.Unit=service->val.enumeration;
							
							
						} else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Unit=service->val.enumeration;

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
						 if(service->idPath.id[3] == 1)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->EAmount.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 26)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxPower.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 27)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMaxVoltage.Value=service->val.int32;
							
							
						} else if(service->idPath.id[3] == 28)
						{ 
							service->exiMsg.V2G_Message.Body.PowerDiscoveryReq->PEVMinVoltage.Value=service->val.int32;
							
							
						}else if(service->idPath.id[3] == 14)
						{
							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterReading.Value=service->val.int32;

						}
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
					memcpy(service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len*sizeof(uint32_t));
					service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterID=1;*/
				break;
				case 19: /*MeterStatus*/
					if(service->val.type == INTEGER_16) 
					{

							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.MeterStatus=service->val.int32;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.MeterStatus=1;*/
				break;
				case 37: /*TMeter*/
					if(service->val.type == INTEGER_32) 
					{

							service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.TMeter=service->val.int32;

					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					/*service->exiMsg.V2G_Message.Body.MeteringStatusRes->MeterInfo.isused.TMeter=1;*/
				break;	
			} /* close switch(service->eqn.localPart) */	
		break;
	
	} /* close switch(service->eqn.namespaceURI) */
	return 0;
}

/**
 * Depending on the current EXI event a message element is deserialized or a
 * defined service method is called in here
 */
static int deserializeElementOrServiceCall(struct EXIService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 54:/* ServiceScope */	
	
 				
				/* is used */
				service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq->isused.ServiceScope=1;
				break;
				case 60:/* TCurrent */	
	
 				
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringReceiptReq->isused.TCurrent=1;
				break;
				case 56:/* SessionSetupReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					sessionSetup((service->exiMsg.V2G_Message.Body.SessionSetupReq), (service->exiMsg.V2G_Message.Body.SessionSetupRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.SessionSetupRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 45:/* ServiceDiscoveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					serviceDiscovery((service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq), (service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.ServiceDiscoveryRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 50:/* ServicePaymentSelectionReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					selectedServicePayment((service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq), (service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.ServicePaymentSelectionRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 30:/* PaymentDetailsReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					paymentDetails((service->exiMsg.V2G_Message.Body.PaymentDetailsReq), (service->exiMsg.V2G_Message.Body.PaymentDetailsRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PaymentDetailsRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 38:/* PowerDiscoveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					powerDiscovery((service->exiMsg.V2G_Message.Body.PowerDiscoveryReq), (service->exiMsg.V2G_Message.Body.PowerDiscoveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PowerDiscoveryRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 10:/* LineLockReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					lineLock((service->exiMsg.V2G_Message.Body.LineLockReq), (service->exiMsg.V2G_Message.Body.LineLockRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.LineLockRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 34:/* PowerDeliveryReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					powerDelivery((service->exiMsg.V2G_Message.Body.PowerDeliveryReq), (service->exiMsg.V2G_Message.Body.PowerDeliveryRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.PowerDeliveryRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 19:/* MeteringStatusReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					meteringStatus((service->exiMsg.V2G_Message.Body.MeteringStatusReq), (service->exiMsg.V2G_Message.Body.MeteringStatusRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.MeteringStatusRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
				case 15:/* MeteringReceiptReq */	
	
 		
			
							
					/* test, if data length is unequal to the expected payload  */
					if((service->inStream.size)!= *(service->inStream.pos))
					{
						service->errorCode = EXI_NON_VALID_MESSAGE;
						return -1;
					}			
			
					/* service call */
					meteringReceipt((service->exiMsg.V2G_Message.Body.MeteringReceiptReq), (service->exiMsg.V2G_Message.Body.MeteringReceiptRes));
							
					/* signalize the response message */
					service->exiMsg.V2G_Message.Body.isused.MeteringReceiptRes=1;
					
					/* serialize the response data */
					if(serialize_message(service))
					{
						/* serializiation error*/
						service->errorCode= EXI_SERIALIZATION_FAILED;
					} 

			
		
				break;
			}
		break;
		case 5:
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
				case 26:/* Service */	
	
				/* increment*/
				service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq->ServiceList.arraylen.Service++;
				
				break;
				case 16:/* MeterID */	
	
 				
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.MeterID=1;
				break;
				case 18:/* MeterReading */	
	
 				
				/* is used */
				service->exiMsg.V2G_Message.Body.MeteringReceiptReq->MeterInfo.isused.MeterReading=1;
				break;
			}
		break;
		case 7:
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

static int deserializeSessionSetupReqMsg(struct EXIService* service)
{
	struct SessionSetupReqType reqMsg;
	struct SessionSetupResType resMsg;
	init_SessionSetupReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.SessionSetupReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.SessionSetupRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeServiceDiscoveryReqMsg(struct EXIService* service)
{
	struct ServiceDiscoveryReqType reqMsg;
	struct ServiceDiscoveryResType resMsg;
	init_ServiceDiscoveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.ServiceDiscoveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.ServiceDiscoveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeServicePaymentSelectionReqMsg(struct EXIService* service)
{
	struct ServicePaymentSelectionReqType reqMsg;
	struct ServicePaymentSelectionResType resMsg;
	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.ServicePaymentSelectionRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePaymentDetailsReqMsg(struct EXIService* service)
{
	struct PaymentDetailsReqType reqMsg;
	struct PaymentDetailsResType resMsg;
	service->exiMsg.V2G_Message.Body.PaymentDetailsReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PaymentDetailsRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePowerDiscoveryReqMsg(struct EXIService* service)
{
	struct PowerDiscoveryReqType reqMsg;
	struct PowerDiscoveryResType resMsg;
	init_PowerDiscoveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.PowerDiscoveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PowerDiscoveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeLineLockReqMsg(struct EXIService* service)
{
	struct LineLockReqType reqMsg;
	struct LineLockResType resMsg;
	init_LineLockReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.LineLockReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.LineLockRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializePowerDeliveryReqMsg(struct EXIService* service)
{
	struct PowerDeliveryReqType reqMsg;
	struct PowerDeliveryResType resMsg;
	init_PowerDeliveryReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.PowerDeliveryReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.PowerDeliveryRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeMeteringStatusReqMsg(struct EXIService* service)
{
	struct MeteringStatusReqType reqMsg;
	struct MeteringStatusResType resMsg;
	service->exiMsg.V2G_Message.Body.MeteringStatusReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.MeteringStatusRes = &resMsg;
	
	return deserializeMessage(service);
}

static int deserializeMeteringReceiptReqMsg(struct EXIService* service)
{
	struct MeteringReceiptReqType reqMsg;
	struct MeteringReceiptResType resMsg;
	init_MeteringReceiptReqType(&reqMsg);
	
	service->exiMsg.V2G_Message.Body.MeteringReceiptReq = &reqMsg;
	service->exiMsg.V2G_Message.Body.MeteringReceiptRes = &resMsg;
	
	return deserializeMessage(service);
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
			if (returnCode) 
			{
				
				if(service->errorCode==0) 
				{
					service->errorCode= EXI_NON_VALID_MESSAGE;
				}
			
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
				 
				 /* setup the request context*/
				 if(service->eqn.localPart==56 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeSessionSetupReqMsg(service);
				   } else if(service->eqn.localPart==45 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeServiceDiscoveryReqMsg(service);
				   } else if(service->eqn.localPart==50 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeServicePaymentSelectionReqMsg(service);
				   } else if(service->eqn.localPart==30 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePaymentDetailsReqMsg(service);
				   } else if(service->eqn.localPart==38 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePowerDiscoveryReqMsg(service);
				   } else if(service->eqn.localPart==10 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeLineLockReqMsg(service);
				   } else if(service->eqn.localPart==34 && service->eqn.namespaceURI==4)
				  {
				 	return deserializePowerDeliveryReqMsg(service);
				   } else if(service->eqn.localPart==19 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeMeteringStatusReqMsg(service);
				   } else if(service->eqn.localPart==15 && service->eqn.namespaceURI==4)
				  {
				 	return deserializeMeteringReceiptReqMsg(service);
				   } 				 
				 
				 
				break;
			case END_ELEMENT:

				returnCode = exiDecodeEndElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				returnCode = deserializeElementOrServiceCall(service);
				service->idPath.pos--;
				 
				break;
			case CHARACTERS:
				/* decode */
				returnCode = exiDecodeCharacters(&(service->inStream), &(service->stateDecode), &(service->val));
				 
				/* assign data to the EXI message structure */
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


/** 
 * \brief Takes the EXI stream, invokes the called service method, and provides the response EXI stream
 * \param	service   struct EXIService* Represent the service data structure
 * \param	inStream   uint8_t* EXI in stream
 * \param	sizeInStream   uint16_t Length of the inStream
 * \param	outStream   uint8_t* Represent the out stream
 * \param	sizeOutStream   uint16_t Size of the out stream
 * \param	outStreamLength   uint16_t* Length of the stream
 * \return  0 = 0K; -1 = ERROR
 */
int messageDispatcher(struct EXIService* service, uint8_t* inStream, uint16_t sizeInStream, uint8_t* outStream, uint16_t sizeOutStream, uint16_t* outStreamLength)
{
	struct HeaderType header;	

	
	uint16_t inPos, outPos;
	
	/* assign inStream data to service EXI structure */
	inPos = service->transportHeaderOffset;
	service->inStream.data = inStream;
	service->inStream.size = sizeInStream+inPos;
	service->inStream.pos = &inPos;
	service->inStream.buffer=0;
	service->inStream.capacity=0;

	
	/* assign outStream data to service EXI structure */
	outPos=service->transportHeaderOffset;
	service->outStream.data = outStream;
	service->outStream.size = sizeOutStream;
	service->outStream.pos = &outPos;
	service->outStream.buffer=0;
	service->outStream.capacity=8;
	
	/* clear error code */
	service->errorCode = 0;
	
	/* init EXI decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));
	
	/* init EXI encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init uniqueID stack */
	service->idPath.pos=0;

	init_HeaderType(&header);
	service->exiMsg.V2G_Message.Header = &header;	

	/* init EXI message */
	init_EXIDocumentType(&(service->exiMsg));

	/* deserialize the input stream and call the corresponding service */
	if(deserializeMessage(service))
	{
		return -1; /* something went wrong */
	}

	/* determine payload size (without transport offset) */	
	outPos -= service->transportHeaderOffset;
	*outStreamLength = outPos;

	
	return 0;
}

/** 
 * \brief Init the v2g service data structure
 * \param	service   struct EXIService* Service data structure
 * \param	bytes   bytes_t setted up byte data structure
 * \param	string_ucs_t   setted up string data structure
 * \param	transportHeaderOffset uint16_t Transport protocol offset
 * \return  0 = 0K; -1 = ERROR
 */
int init_v2gservice(struct EXIService* service, bytes_t bytes, string_ucs_t string, uint16_t transportHeaderOffset)
{

	/* init byte array */
	 service->val.binary = bytes;

	/* init string array */
	 service->val.string = string;

	/* init offset for transport protocoll */
	 service->transportHeaderOffset=transportHeaderOffset;

	return 0;
}
