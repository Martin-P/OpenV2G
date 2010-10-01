


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
#include "../codec/EXITypes.h"
#include "../codec/EXIDecoder.h"
#include "../codec/EXIEncoder.h"


/**
 * Assigns an element value of the EXI stream into the service data structure 
 */
static int deserializeElementCharacter(struct v2gService* service)
{

	/* SessionID */	
	 if(service->eqn.namespaceURI==5 && service->eqn.localPart==35)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Header.SessionInformation.SessionID.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Header.SessionInformation.SessionID.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
	}
	
	/* ServiceSessionID */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==33)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Header.SessionInformation.ServiceSessionID.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Header.SessionInformation.ServiceSessionID.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Header.SessionInformation.isused.ServiceSessionID=1;
	}
	
	/* ProtocolVersion */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==25)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Header.SessionInformation.ProtocolVersion.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Header.SessionInformation.ProtocolVersion.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Header.SessionInformation.isused.ProtocolVersion=1;
	}
	
	/* Event */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==9)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Header.Notification.EventList.Event=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* FaultCode */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==13)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Header.Notification.FaultCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Header.Notification.isused.FaultCode=1;
	}
	
	/* FaultMsg */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==14)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Header.Notification.FaultMsg.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Header.Notification.FaultMsg.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Header.Notification.isused.FaultMsg=1;
	}
	
	/* ConnectorLocked */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==4)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupReq.PEVStatus.ConnectorLocked=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* ChargerStandby */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==0)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupReq.PEVStatus.ChargerStandby=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* PEVID */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==26)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.SessionSetupReq.PEVID.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.SessionSetupReq.PEVID.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.SessionSetupReq.isused.PEVID=1;
	}
	
	/* FatalError */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==12)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.FatalError=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* EVSEStandby */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==7)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.EVSEStandby=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* ConnectorLocked */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==4)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ConnectorLocked=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* PowerSwitchClosed */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==24)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.PowerSwitchClosed=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* RCD */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==26)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.RCD=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* ShutDownTime */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==37)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.SessionSetupRes.EVSEStatus.ShutDownTime=service->val.int64;
		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.SessionSetupRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* EVSEID */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==3)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.SessionSetupRes.EVSEID.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.SessionSetupRes.EVSEID.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
	}
	
	/* TCurrent */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==63)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.SessionSetupRes.TCurrent=service->val.int64;
		}
		else
		{
			return -1;
		}
	}
	
	/* ServiceType */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==58)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.ServiceDiscoveryReq.ServiceType=service->val.enumeration;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceType=1;
	}
	
	/* ServiceScope */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==57)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryReq.ServiceScope.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.ServiceDiscoveryReq.ServiceScope.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryReq.isused.ServiceScope=1;
	}
	
	/* ServiceID */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==29)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceID.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceID.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
	}
	
	/* ServiceName */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==31)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceName.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceName.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceName=1;
	}
	
	/* ServiceType */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==34)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceType=service->val.enumeration;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceType=1;
	}
	
	/* ServiceScope */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==32)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceScope.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].ServiceScope.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.Service[service->v2gMsg.Body.ServiceDiscoveryRes.ServiceList.arraylen.Service].isused.ServiceScope=1;
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.ServiceDiscoveryRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* PEVPubKey */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==31)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.ServicePaymentSelectionReq.PEVPubKey.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.ServicePaymentSelectionReq.PEVPubKey.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.ServicePaymentSelectionRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* MeteringAuthPubKey */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==16)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.ServicePaymentSelectionRes.MeteringAuthPubKey.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.ServicePaymentSelectionRes.MeteringAuthPubKey.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.ServicePaymentSelectionRes.isused.MeteringAuthPubKey=1;
	}
	
	/* ContractID */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==1)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PaymentDetailsReq.ContractID.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PaymentDetailsReq.ContractID.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PaymentDetailsRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* Multiplier */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==21)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Multiplier=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* Unit */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==50)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Unit=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* Value */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==51)
	{
		if(service->val.type == INTEGER_16) 
		{
			service->v2gMsg.Body.PowerDiscoveryReq.EAmount.Value=service->val.int32;
		}
		else
		{
			return -1;
		}
	}
	
	/* EoC */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==10)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.PowerDiscoveryReq.EoC=service->val.int64;
		}
		else
		{
			return -1;
		}
	}
	
	/* PEVMaxPhases */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==27)
	{
		if(service->val.type == INTEGER_16) 
		{
			service->v2gMsg.Body.PowerDiscoveryReq.PEVMaxPhases=service->val.int32;
		}
		else
		{
			return -1;
		}
	}
	
	/* TariffStart */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==48)
	{
		if(service->val.type == UNSIGNED_INTEGER_32) 
		{
			service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].TariffStart=service->val.uint32;
		}
		else
		{
			return -1;
		}
	}
	
	/* TariffID */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==46)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffID=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* TariffDescription */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==41)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffDescription.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffDescription.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].isused.TariffDescription=1;
	}
	
	/* Currency */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==5)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Currency.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Currency.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDiscoveryRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* EVSEMaxPhases */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==5)
	{
		if(service->val.type == INTEGER_16) 
		{
			service->v2gMsg.Body.PowerDiscoveryRes.EVSEMaxPhases=service->val.int32;
		}
		else
		{
			return -1;
		}
	}
	
	/* EnergyProvider */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==9)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.PowerDiscoveryRes.EnergyProvider.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.PowerDiscoveryRes.EnergyProvider.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.PowerDiscoveryRes.isused.EnergyProvider=1;
	}
	
	/* ReqLockStatus */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==45)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.LineLockReq.ReqLockStatus=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.LineLockRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* ChargingProfileEntryStart */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==2)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.PowerDeliveryReq.ChargingProfile.ChargingProfileEntryStart=service->val.int64;
		}
		else
		{
			return -1;
		}
	}
	
	/* ReqSwitchStatus */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==46)
	{
		if(service->val.type == BOOLEAN) 
		{
			service->v2gMsg.Body.PowerDeliveryReq.ReqSwitchStatus=service->val.boolean;
		}
		else
		{
			return -1;
		}
	}
	
	/* Tariff */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==64)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDeliveryReq.Tariff=service->val.enumeration;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.PowerDeliveryReq.isused.Tariff=1;
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.PowerDeliveryRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* MeterID */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==16)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterID.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterID.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterID=1;
	}
	
	/* MeterPubKey */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==18)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterPubKey.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterPubKey.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterPubKey=1;
	}
	
	/* MeterStatus */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==20)
	{
		if(service->val.type == INTEGER_16) 
		{
			service->v2gMsg.Body.MeteringStatusRes.MeterInfo.MeterStatus=service->val.int32;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterStatus=1;
	}
	
	/* TMeter */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==38)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.MeteringStatusRes.MeterInfo.TMeter=service->val.int64;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.TMeter=1;
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.MeteringStatusRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* EVSEID */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==3)
	{
		if(service->val.type == BINARY_HEX) 
		{
			/* array copy and array length assignment */
			memcpy(service->v2gMsg.Body.MeteringStatusRes.EVSEID.data, service->val.binary.data,service->val.binary.len);
			service->v2gMsg.Body.MeteringStatusRes.EVSEID.arraylen.data = service->val.binary.len;
		}
		else
		{
			return -1;
		}
	}
	
	/* TCurrent */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==63)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.MeteringStatusRes.TCurrent=service->val.int64;
		}
		else
		{
			return -1;
		}
	}
	
	/* PEVID */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==26)
	{
		if(service->val.type == STRING) 
		{
			/* string copy and string length assignment */
			memcpy(service->v2gMsg.Body.MeteringReceiptReq.PEVID.data, service->val.string.codepoints,service->val.string.len);
			service->v2gMsg.Body.MeteringReceiptReq.PEVID.arraylen.data = service->val.string.len;

		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringReceiptReq.isused.PEVID=1;
	}
	
	/* TCurrent */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==63)
	{
		if(service->val.type == INTEGER_64) 
		{
			service->v2gMsg.Body.MeteringReceiptReq.TCurrent=service->val.int64;
		}
		else
		{
			return -1;
		}
		/* is used */
		service->v2gMsg.Body.MeteringReceiptReq.isused.TCurrent=1;
	}
	
	/* Tariff */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==64)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.MeteringReceiptReq.Tariff=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	/* ResponseCode */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==47)
	{
		if(service->val.type == ENUMERATION) 
		{
			service->v2gMsg.Body.MeteringReceiptRes.ResponseCode=service->val.enumeration;
		}
		else
		{
			return -1;
		}
	}
	
	return 0;
}

/**
 * Depending on the current EXI event a message element is deserialized or a
 * defined service method is called in here
 */
static int deserializeElementOrServiceCall(struct v2gService* service)
{

	/* EventList */	
	 if(service->eqn.namespaceURI==5 && service->eqn.localPart==10)
	{
 		/* is used */
		service->v2gMsg.Header.Notification.isused.EventList=1;
		
	}
	
	/* Notification */	
	else  if(service->eqn.namespaceURI==6 && service->eqn.localPart==6)
	{
 		/* is used */
		service->v2gMsg.Header.isused.Notification=1;
		
	}
	
	/* ServiceList */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==52)
	{
 		/* is used */
		service->v2gMsg.Body.ServiceDiscoveryRes.isused.ServiceList=1;
		
	}
	
	/* EPrice */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==6)
	{
 		/* is used */
		service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.TariffEntry[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.Tariff[service->v2gMsg.Body.PowerDiscoveryRes.TariffTable.arraylen.Tariff].TariffEntries.arraylen.TariffEntry].isused.EPrice=1;
		
	}
	
	/* TariffTable */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==65)
	{
 		/* is used */
		service->v2gMsg.Body.PowerDiscoveryRes.isused.TariffTable=1;
		
	}
	
	/* ChargingProfile */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==0)
	{
 		/* is used */
		service->v2gMsg.Body.PowerDeliveryReq.isused.ChargingProfile=1;
		
	}
	
	/* MeterReading */	
	else  if(service->eqn.namespaceURI==5 && service->eqn.localPart==19)
	{
 		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.MeterInfo.isused.MeterReading=1;
		
	}
	
	/* PCurrent */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==25)
	{
 		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.isused.PCurrent=1;
		
	}
	
	/* MeterInfo */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==15)
	{
 		/* is used */
		service->v2gMsg.Body.MeteringStatusRes.isused.MeterInfo=1;
		
	}
	
	/* SessionSetupReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==59)
	{
 		
		/* service call */
		sessionSetup(&(service->v2gMsg.Body.SessionSetupReq), &(service->v2gMsg.Body.SessionSetupRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.SessionSetupRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* SessionSetupRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==61)
	{
 		/* is used */
		service->v2gMsg.Body.isused.SessionSetupRes=1;
		
	}
	
	/* ServiceDiscoveryReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==48)
	{
 		
		/* service call */
		serviceDiscovery(&(service->v2gMsg.Body.ServiceDiscoveryReq), &(service->v2gMsg.Body.ServiceDiscoveryRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.ServiceDiscoveryRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* ServiceDiscoveryRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==50)
	{
 		/* is used */
		service->v2gMsg.Body.isused.ServiceDiscoveryRes=1;
		
	}
	
	/* ServicePaymentSelectionReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==53)
	{
 		
		/* service call */
		selectedServicePayment(&(service->v2gMsg.Body.ServicePaymentSelectionReq), &(service->v2gMsg.Body.ServicePaymentSelectionRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.ServicePaymentSelectionRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* ServicePaymentSelectionRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==55)
	{
 		/* is used */
		service->v2gMsg.Body.isused.ServicePaymentSelectionRes=1;
		
	}
	
	/* PaymentDetailsReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==33)
	{
 		
		/* service call */
		paymentDetails(&(service->v2gMsg.Body.PaymentDetailsReq), &(service->v2gMsg.Body.PaymentDetailsRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.PaymentDetailsRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* PaymentDetailsRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==35)
	{
 		/* is used */
		service->v2gMsg.Body.isused.PaymentDetailsRes=1;
		
	}
	
	/* PowerDiscoveryReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==41)
	{
 		
		/* service call */
		powerDiscovery(&(service->v2gMsg.Body.PowerDiscoveryReq), &(service->v2gMsg.Body.PowerDiscoveryRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.PowerDiscoveryRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* PowerDiscoveryRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==43)
	{
 		/* is used */
		service->v2gMsg.Body.isused.PowerDiscoveryRes=1;
		
	}
	
	/* LineLockReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==11)
	{
 		
		/* service call */
		lineLock(&(service->v2gMsg.Body.LineLockReq), &(service->v2gMsg.Body.LineLockRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.LineLockRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* LineLockRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==13)
	{
 		/* is used */
		service->v2gMsg.Body.isused.LineLockRes=1;
		
	}
	
	/* PowerDeliveryReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==37)
	{
 		
		/* service call */
		powerDelivery(&(service->v2gMsg.Body.PowerDeliveryReq), &(service->v2gMsg.Body.PowerDeliveryRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.PowerDeliveryRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* PowerDeliveryRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==39)
	{
 		/* is used */
		service->v2gMsg.Body.isused.PowerDeliveryRes=1;
		
	}
	
	/* MeteringStatusReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==21)
	{
 		
		/* service call */
		meteringStatus(&(service->v2gMsg.Body.MeteringStatusReq), &(service->v2gMsg.Body.MeteringStatusRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.MeteringStatusRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* MeteringStatusRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==23)
	{
 		/* is used */
		service->v2gMsg.Body.isused.MeteringStatusRes=1;
		
	}
	
	/* MeteringReceiptReq */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==17)
	{
 		
		/* service call */
		meteringReceipt(&(service->v2gMsg.Body.MeteringReceiptReq), &(service->v2gMsg.Body.MeteringReceiptRes));
				
		/* signalize the response message */
		service->v2gMsg.Body.isused.MeteringReceiptRes=1;
		
		/* marshall the response data */
		serialize_message(service); 
				
				
			
		
	}
	
	/* MeteringReceiptRes */	
	else  if(service->eqn.namespaceURI==4 && service->eqn.localPart==19)
	{
 		/* is used */
		service->v2gMsg.Body.isused.MeteringReceiptRes=1;
		
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
	int errno;
#ifdef DEBUG
	const char * localName;
	const char * namespaceURI;
#endif

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
				 
				break;
			case END_ELEMENT:

				errno = exiDecodeEndElement(&(service->inStream), &(service->stateDecode), &(service->eqn));
				errno = deserializeElementOrServiceCall(service);
				 
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
