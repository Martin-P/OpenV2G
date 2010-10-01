
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


#include "../codec/EXITypes.h"
#include "v2g_serviceDataTypes.h"


static  void init_SessionInformationType_SessionID(struct SessionInformationType_SessionID* type)
{
	
	type->arraylen.data=0;

}

static  void init_SessionInformationType_ServiceSessionID(struct SessionInformationType_ServiceSessionID* type)
{
	
	type->arraylen.data=0;

}

static  void init_SessionInformationType_ProtocolVersion(struct SessionInformationType_ProtocolVersion* type)
{
	
	type->arraylen.data=0;

}

static  void init_SessionInformationType(struct SessionInformationType* type)
{
	
	init_SessionInformationType_SessionID(&(type->SessionID));	
	init_SessionInformationType_ServiceSessionID(&(type->ServiceSessionID));	
	type->isused.ServiceSessionID=0;	
	init_SessionInformationType_ProtocolVersion(&(type->ProtocolVersion));	
	type->isused.ProtocolVersion=0;

}

static  void init_NotificationType_FaultMsg(struct NotificationType_FaultMsg* type)
{
	
	type->arraylen.data=0;

}

static  void init_NotificationType(struct NotificationType* type)
{
		
	type->isused.FaultCode=0;	
	init_NotificationType_FaultMsg(&(type->FaultMsg));	
	type->isused.FaultMsg=0;		
	type->isused.EventList=0;

}

static  void init_HeaderType(struct HeaderType* type)
{
	
	init_SessionInformationType(&(type->SessionInformation));	
	init_NotificationType(&(type->Notification));	
	type->isused.Notification=0;

}

static  void init_SessionSetupReqType_PEVID(struct SessionSetupReqType_PEVID* type)
{
	
	type->arraylen.data=0;

}

static  void init_SessionSetupReqType(struct SessionSetupReqType* type)
{
	
	init_SessionSetupReqType_PEVID(&(type->PEVID));	
	type->isused.PEVID=0;	

}

static  void init_SessionSetupResType_EVSEID(struct SessionSetupResType_EVSEID* type)
{
	
	type->arraylen.data=0;

}

static  void init_SessionSetupResType(struct SessionSetupResType* type)
{
		
	init_SessionSetupResType_EVSEID(&(type->EVSEID));		

}

static  void init_ServiceDiscoveryReqType_ServiceScope(struct ServiceDiscoveryReqType_ServiceScope* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServiceDiscoveryReqType(struct ServiceDiscoveryReqType* type)
{
		
	type->isused.ServiceType=0;	
	init_ServiceDiscoveryReqType_ServiceScope(&(type->ServiceScope));	
	type->isused.ServiceScope=0;

}

static  void init_ServiceDescriptionType_ServiceID(struct ServiceDescriptionType_ServiceID* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServiceDescriptionType_ServiceName(struct ServiceDescriptionType_ServiceName* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServiceDescriptionType_ServiceScope(struct ServiceDescriptionType_ServiceScope* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServiceDescriptionType(struct ServiceDescriptionType* type)
{
	
	init_ServiceDescriptionType_ServiceID(&(type->ServiceID));	
	init_ServiceDescriptionType_ServiceName(&(type->ServiceName));	
	type->isused.ServiceName=0;		
	type->isused.ServiceType=0;	
	init_ServiceDescriptionType_ServiceScope(&(type->ServiceScope));	
	type->isused.ServiceScope=0;

}

static  void init_ServiceListType(struct ServiceListType* type)
{
	
	init_ServiceDescriptionType((type->Service));
	type->arraylen.Service=0;

}

static  void init_ServiceDiscoveryResType(struct ServiceDiscoveryResType* type)
{
		
	init_ServiceListType(&(type->ServiceList));	
	type->isused.ServiceList=0;

}

static  void init_ServicePaymentSelectionReqType_PEVPubKey(struct ServicePaymentSelectionReqType_PEVPubKey* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServicePaymentSelectionReqType(struct ServicePaymentSelectionReqType* type)
{
	
	init_ServiceListType(&(type->ServiceList));	
	init_ServicePaymentSelectionReqType_PEVPubKey(&(type->PEVPubKey));

}

static  void init_ServicePaymentSelectionResType_MeteringAuthPubKey(struct ServicePaymentSelectionResType_MeteringAuthPubKey* type)
{
	
	type->arraylen.data=0;

}

static  void init_ServicePaymentSelectionResType(struct ServicePaymentSelectionResType* type)
{
		
	init_ServicePaymentSelectionResType_MeteringAuthPubKey(&(type->MeteringAuthPubKey));	
	type->isused.MeteringAuthPubKey=0;

}

static  void init_PaymentDetailsReqType_ContractID(struct PaymentDetailsReqType_ContractID* type)
{
	
	type->arraylen.data=0;

}

static  void init_PaymentDetailsReqType(struct PaymentDetailsReqType* type)
{
	
	init_PaymentDetailsReqType_ContractID(&(type->ContractID));

}

static  void init_PowerDiscoveryReqType(struct PowerDiscoveryReqType* type)
{
							

}

static  void init_PowerDiscoveryResType_EnergyProvider(struct PowerDiscoveryResType_EnergyProvider* type)
{
	
	type->arraylen.data=0;

}

static  void init_TariffTableType_Currency(struct TariffTableType_Currency* type)
{
	
	type->arraylen.data=0;

}

static  void init_TariffDescrType_TariffDescription(struct TariffDescrType_TariffDescription* type)
{
	
	type->arraylen.data=0;

}

static  void init_TariffEntryType(struct TariffEntryType* type)
{
				
	type->isused.EPrice=0;

}

static  void init_TariffEntriesType(struct TariffEntriesType* type)
{
	
	init_TariffEntryType((type->TariffEntry));
	type->arraylen.TariffEntry=0;

}

static  void init_TariffDescrType(struct TariffDescrType* type)
{
		
	init_TariffDescrType_TariffDescription(&(type->TariffDescription));	
	type->isused.TariffDescription=0;	
	init_TariffEntriesType(&(type->TariffEntries));

}

static  void init_TariffTableType(struct TariffTableType* type)
{
	
	init_TariffTableType_Currency(&(type->Currency));	
	init_TariffDescrType((type->Tariff));
	type->arraylen.Tariff=0;

}

static  void init_PowerDiscoveryResType(struct PowerDiscoveryResType* type)
{
						
	init_PowerDiscoveryResType_EnergyProvider(&(type->EnergyProvider));	
	type->isused.EnergyProvider=0;	
	init_TariffTableType(&(type->TariffTable));	
	type->isused.TariffTable=0;

}

static  void init_LineLockReqType(struct LineLockReqType* type)
{
		

}

static  void init_LineLockResType(struct LineLockResType* type)
{
		

}

static  void init_ChargingProfileType(struct ChargingProfileType* type)
{
		

}

static  void init_PowerDeliveryReqType(struct PowerDeliveryReqType* type)
{
				
	type->isused.Tariff=0;	
	init_ChargingProfileType(&(type->ChargingProfile));	
	type->isused.ChargingProfile=0;

}

static  void init_MeteringStatusResType_EVSEID(struct MeteringStatusResType_EVSEID* type)
{
	
	type->arraylen.data=0;

}

static  void init_MeterInfoType_MeterID(struct MeterInfoType_MeterID* type)
{
	
	type->arraylen.data=0;

}

static  void init_MeterInfoType_MeterPubKey(struct MeterInfoType_MeterPubKey* type)
{
	
	type->arraylen.data=0;

}

static  void init_MeterInfoType(struct MeterInfoType* type)
{
	
	init_MeterInfoType_MeterID(&(type->MeterID));	
	type->isused.MeterID=0;	
	init_MeterInfoType_MeterPubKey(&(type->MeterPubKey));	
	type->isused.MeterPubKey=0;		
	type->isused.MeterReading=0;		
	type->isused.MeterStatus=0;		
	type->isused.TMeter=0;

}

static  void init_MeteringStatusResType(struct MeteringStatusResType* type)
{
		
	init_MeteringStatusResType_EVSEID(&(type->EVSEID));					
	type->isused.PCurrent=0;	
	init_MeterInfoType(&(type->MeterInfo));	
	type->isused.MeterInfo=0;

}

static  void init_MeteringReceiptReqType_PEVID(struct MeteringReceiptReqType_PEVID* type)
{
	
	type->arraylen.data=0;

}

static  void init_MeteringReceiptReqType(struct MeteringReceiptReqType* type)
{
	
	init_MeteringReceiptReqType_PEVID(&(type->PEVID));	
	type->isused.PEVID=0;			
	type->isused.TCurrent=0;		
	init_MeterInfoType(&(type->MeterInfo));

}

static  void init_BodyType(struct BodyType* type)
{
	
	init_SessionSetupReqType(&(type->SessionSetupReq));	
	type->isused.SessionSetupReq=0;	
	init_SessionSetupResType(&(type->SessionSetupRes));	
	type->isused.SessionSetupRes=0;	
	init_ServiceDiscoveryReqType(&(type->ServiceDiscoveryReq));	
	type->isused.ServiceDiscoveryReq=0;	
	init_ServiceDiscoveryResType(&(type->ServiceDiscoveryRes));	
	type->isused.ServiceDiscoveryRes=0;	
	init_ServicePaymentSelectionReqType(&(type->ServicePaymentSelectionReq));	
	type->isused.ServicePaymentSelectionReq=0;	
	init_ServicePaymentSelectionResType(&(type->ServicePaymentSelectionRes));	
	type->isused.ServicePaymentSelectionRes=0;	
	init_PaymentDetailsReqType(&(type->PaymentDetailsReq));	
	type->isused.PaymentDetailsReq=0;		
	type->isused.PaymentDetailsRes=0;	
	init_PowerDiscoveryReqType(&(type->PowerDiscoveryReq));	
	type->isused.PowerDiscoveryReq=0;	
	init_PowerDiscoveryResType(&(type->PowerDiscoveryRes));	
	type->isused.PowerDiscoveryRes=0;	
	init_LineLockReqType(&(type->LineLockReq));	
	type->isused.LineLockReq=0;	
	init_LineLockResType(&(type->LineLockRes));	
	type->isused.LineLockRes=0;	
	init_PowerDeliveryReqType(&(type->PowerDeliveryReq));	
	type->isused.PowerDeliveryReq=0;		
	type->isused.PowerDeliveryRes=0;		
	type->isused.MeteringStatusReq=0;	
	init_MeteringStatusResType(&(type->MeteringStatusRes));	
	type->isused.MeteringStatusRes=0;	
	init_MeteringReceiptReqType(&(type->MeteringReceiptReq));	
	type->isused.MeteringReceiptReq=0;		
	type->isused.MeteringReceiptRes=0;

}
 void init_AnonType_V2G_Message(struct AnonType_V2G_Message* type)
{
	
	init_HeaderType(&(type->Header));	
	init_BodyType(&(type->Body));

}
