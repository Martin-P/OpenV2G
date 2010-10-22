


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


#include "v2g_service.h"
#include "v2g_serviceDispatcher.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceMethods.h"
#include "v2g_serviceDataSerializiation.h"
#include "EXITypes.h"
#include "EXIDecoder.h"
#include "EXIEncoder.h"


/**
 * Deserialize an element value of the EXI stream and assign it to the
 * service data structure 
 */
static int deserializeElementCharacter(struct v2gService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 26: /*PEVID*/
		
				if(service->val.type == STRING) 
				{
					/* string copy and string length assignment */
					memcpy(service->v2gMsg.Body.SessionSetupReq.PEVID.data, service->val.string.codepoints,service->val.string.len);
					service->v2gMsg.Body.SessionSetupReq.PEVID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.SessionSetupReq.isused.PEVID=1;
				break;
				case 58: /*ServiceType*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Body.ServiceDiscoveryReq.ServiceType=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceType=1;
				break;
				case 57: /*ServiceScope*/
		
				if(service->val.type == STRING) 
				{
					/* string copy and string length assignment */
					memcpy(service->v2gMsg.Body.ServiceDiscoveryReq.ServiceScope.data, service->val.string.codepoints,service->val.string.len);
					service->v2gMsg.Body.ServiceDiscoveryReq.ServiceScope.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceScope=1;
				break;
				case 31: /*PEVPubKey*/
		
				if(service->val.type == BINARY_HEX) 
				{
					/* array copy and array length assignment */
					memcpy(service->v2gMsg.Body.ServicePaymentSelectionReq.PEVPubKey.data, service->val.binary.data,service->val.binary.len);
					service->v2gMsg.Body.ServicePaymentSelectionReq.PEVPubKey.arraylen.data = service->val.binary.len;
		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 1: /*ContractID*/
		
				if(service->val.type == STRING) 
				{
					/* string copy and string length assignment */
					memcpy(service->v2gMsg.Body.PaymentDetailsReq.ContractID.data, service->val.string.codepoints,service->val.string.len);
					service->v2gMsg.Body.PaymentDetailsReq.ContractID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 10: /*EoC*/
					if(service->val.type == INTEGER_64) 
					{
							service->v2gMsg.Body.PowerDiscoveryReq.EoC=service->val.int64;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 27: /*PEVMaxPhases*/
					if(service->val.type == INTEGER_16) 
					{
							service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPhases=service->val.int32;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 45: /*ReqLockStatus*/
					if(service->val.type == BOOLEAN) 
					{
							service->v2gMsg.Body.LineLockReq.ReqLockStatus=service->val.boolean;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 46: /*ReqSwitchStatus*/
					if(service->val.type == BOOLEAN) 
					{
							service->v2gMsg.Body.PowerDeliveryReq.ReqSwitchStatus=service->val.boolean;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
				break;
				case 64: /*Tariff*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Body.PowerDeliveryReq.Tariff=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.PowerDeliveryReq.isused.Tariff=1;
				break;
				case 63: /*TCurrent*/
					if(service->val.type == INTEGER_64) 
					{
							service->v2gMsg.Body.MeteringReceiptReq.TCurrent=service->val.int64;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.MeteringReceiptReq.isused.TCurrent=1;
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
				case 9: /*Event*/
					if(service->val.type == ENUMERATION) 
					{
							service->v2gMsg.Header.Notification.EventList.Event=service->val.enumeration;
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
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
				case 4: /*ConnectorLocked*/
					if(service->val.type == BOOLEAN) 
					{
						 if(service->idPath.id[2] == 59)
						{ 
							service->v2gMsg.Body.SessionSetupReq.PEVStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[2] == 41)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[2] == 11)
						{ 
							service->v2gMsg.Body.LineLockReq.PEVStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[2] == 37)
						{ 
							service->v2gMsg.Body.PowerDeliveryReq.PEVStatus.ConnectorLocked=service->val.boolean;
							
						} else if(service->idPath.id[1] == 17)
						{ 
							service->v2gMsg.Body.MeteringReceiptReq.PEVStatus.ConnectorLocked=service->val.boolean;
							
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
						 if(service->idPath.id[2] == 59)
						{ 
							service->v2gMsg.Body.SessionSetupReq.PEVStatus.ChargerStandby=service->val.boolean;
							
						} else if(service->idPath.id[2] == 41)
						{ 
							service->v2gMsg.Body.PowerDiscoveryReq.PEVStatus.ChargerStandby=service->val.boolean;
							
						} else if(service->idPath.id[2] == 11)
						{ 
							service->v2gMsg.Body.LineLockReq.PEVStatus.ChargerStandby=service->val.boolean;
							
						} else if(service->idPath.id[2] == 37)
						{ 
							service->v2gMsg.Body.PowerDeliveryReq.PEVStatus.ChargerStandby=service->val.boolean;
							
						} else if(service->idPath.id[1] == 17)
						{ 
							service->v2gMsg.Body.MeteringReceiptReq.PEVStatus.ChargerStandby=service->val.boolean;
							
						}
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
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
				case 2: /*ChargingProfileEntryStart*/
					if(service->val.type == INTEGER_64) 
					{
							service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryStart=service->val.int64;
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
					memcpy(service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len);
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterID.arraylen.data = service->val.string.len;

		
					} 
					else
					{
						return -1; /* wrong data type */
					}
		
					/* is used */
					service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterID=1;
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
 * Depending on the current EXI event a message element is deserialized or a
 * defined service method is called in here
 */
static int deserializeElementOrServiceCall(struct v2gService* service)
{

	switch(service->eqn.namespaceURI) {
		case 4:
			switch(service->eqn.localPart) {
				case 26:/* PEVID */	
	
 					service->v2gMsg.Body.SessionSetupReq.isused.PEVID=1;
					service->v2gMsg.Body.MeteringReceiptReq.isused.PEVID=1;
		
				break;
				case 58:/* ServiceType */	
	
 				
				/* is used */
				service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceType=1;
				break;
				case 57:/* ServiceScope */	
	
 				
				/* is used */
				service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceScope=1;
				break;
				case 64:/* Tariff */	
	
 				
				/* is used */
				service->v2gMsg.Body.PowerDeliveryReq.isused.Tariff=1;
				break;
				case 0:/* ChargingProfile */	
	
 				
				/* is used */
				service->v2gMsg.Body.PowerDeliveryReq.isused.ChargingProfile=1;
				break;
				case 63:/* TCurrent */	
	
 				
				/* is used */
				service->v2gMsg.Body.MeteringReceiptReq.isused.TCurrent=1;
				break;
				case 59:/* SessionSetupReq */	
	
 		
					/* service call */
					sessionSetup(&(service->v2gMsg.Body.SessionSetupReq), &(service->v2gMsg.Body.SessionSetupRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.SessionSetupRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 48:/* ServiceDiscoveryReq */	
	
 		
					/* service call */
					serviceDiscovery(&(service->v2gMsg.Body.ServiceDiscoveryReq), &(service->v2gMsg.Body.ServiceDiscoveryRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.ServiceDiscoveryRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 53:/* ServicePaymentSelectionReq */	
	
 		
					/* service call */
					selectedServicePayment(&(service->v2gMsg.Body.ServicePaymentSelectionReq), &(service->v2gMsg.Body.ServicePaymentSelectionRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.ServicePaymentSelectionRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 33:/* PaymentDetailsReq */	
	
 		
					/* service call */
					paymentDetails(&(service->v2gMsg.Body.PaymentDetailsReq), &(service->v2gMsg.Body.PaymentDetailsRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.PaymentDetailsRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 41:/* PowerDiscoveryReq */	
	
 		
					/* service call */
					powerDiscovery(&(service->v2gMsg.Body.PowerDiscoveryReq), &(service->v2gMsg.Body.PowerDiscoveryRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.PowerDiscoveryRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 11:/* LineLockReq */	
	
 		
					/* service call */
					lineLock(&(service->v2gMsg.Body.LineLockReq), &(service->v2gMsg.Body.LineLockRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.LineLockRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 37:/* PowerDeliveryReq */	
	
 		
					/* service call */
					powerDelivery(&(service->v2gMsg.Body.PowerDeliveryReq), &(service->v2gMsg.Body.PowerDeliveryRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.PowerDeliveryRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 21:/* MeteringStatusReq */	
	
 		
					/* service call */
					meteringStatus(&(service->v2gMsg.Body.MeteringStatusReq), &(service->v2gMsg.Body.MeteringStatusRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.MeteringStatusRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
				case 17:/* MeteringReceiptReq */	
	
 		
					/* service call */
					meteringReceipt(&(service->v2gMsg.Body.MeteringReceiptReq), &(service->v2gMsg.Body.MeteringReceiptRes));
							
					/* signalize the response message */
					service->v2gMsg.Body.isused.MeteringReceiptRes=1;
					
					/* serialize the response data */
					serialize_message(service); 

			
		
				break;
			}
		break;
		case 5:
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
		break;
		case 6:
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
				errno = deserializeElementOrServiceCall(service);
				service->idPath.pos--;
				 
				break;
			case CHARACTERS:
				/* decode */
				errno = exiDecodeCharacters(&(service->inStream), &(service->stateDecode), &(service->val));
				 
				/* assign data to the v2g message structure */
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


/** 
 * Takes the EXI stream, invokes the called service method, and provides the response EXI stream 
 * @return 0 = 0K; -1 = ERROR
 */
int messageDispatcher(struct v2gService* service, uint8_t* inStream, size_t sizeInStream, size_t* inPos, uint8_t* outStream, size_t sizeOutStream, size_t* outPos)
{

	int responseCode;

	/* assign inStream data to service v2g structure */
	service->inStream.data = inStream;
	service->inStream.size = sizeInStream;
	service->inStream.pos = inPos;
	service->inStream.buffer=0;
	service->inStream.capacity=0;
	
	
	
	/* assign outStream data to service v2g structure */
	service->outStream.data = outStream;
	service->outStream.size = sizeOutStream;
	service->outStream.pos = outPos;
	service->outStream.buffer=0;
	service->outStream.capacity=8;
	
	
	
	/* init EXI decoder (read header, set initial state) */
	exiInitDecoder(&(service->inStream), &(service->stateDecode));
	
	/* init EXI encoder (write header, set initial state) */
	exiInitEncoder(&(service->outStream), &(service->stateEncode));

	/* init uniqueID stack */
	service->idPath.pos=0;

	/* init v2g message */
	init_AnonType_V2G_Message(&(service->v2gMsg));

	/* deserialize the input stream and call the corresponding service */
	responseCode = deserializeMessage(service);
	
	

	if(responseCode<0)
	{
		/* an error occurred */
		return -1;
	} else if(responseCode==1)
	{
		
		return 0;
	}


	return 0;

}

/** 
 * Init the service
 * @return 0 = 0K; -1 = ERROR
 */
int init_v2gservice(struct v2gService* service, bytes_t bytes, string_ucs_t string)
{

	/* init byte array */
	 service->val.binary = bytes;

	/* init string array */
	 service->val.string = string;


	return 0;
}
