
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



#ifdef __cplusplus
extern "C" {
#endif

#ifndef SERVICEDATATYPES_H
#define SERVICEDATATYPES_H

#include "EXITypes.h"


	

enum faultCodeType
{
	ParsingError_faultCodeType, 
	V2GProtocolVersionNotSupported_faultCodeType, 
	UnknownError_faultCodeType

}; 

enum eventEntryType
{
	InitiateSessionSetup_eventEntryType, 
	InitiateServiceDiscovery_eventEntryType, 
	InitiatePowerDiscovery_eventEntryType, 
	InitiateLineLock_eventEntryType, 
	InitiatePowerDelivery_eventEntryType, 
	InitiateInitiateMeteringStatus_eventEntryType

}; 

enum responseCode_SessionSetupType
{
	OK_SessionSetup_responseCode_SessionSetupType, 
	OK_NewSessionEstablished_responseCode_SessionSetupType, 
	OK_OldSessionJoined_responseCode_SessionSetupType, 
	FAILED_UnknownSession_responseCode_SessionSetupType, 
	FAILED_SessionEstablishmentError_responseCode_SessionSetupType, 
	FAILED_UnknownError_InSessionSetup_responseCode_SessionSetupType

}; 

enum serviceTypeType
{
	PEV_Recharge_serviceTypeType, 
	Remote_Customer_Support_serviceTypeType, 
	Internet_serviceTypeType, 
	Other_serviceTypeType

}; 

enum responseCode_ServiceDiscoveryType
{
	OK_ServiceDiscovery_responseCode_ServiceDiscoveryType, 
	FAILED_NoServicesOfThisType_responseCode_ServiceDiscoveryType, 
	FAILED_NoServicesInThisScope_responseCode_ServiceDiscoveryType, 
	FAILED_NoServicesOfThisTypeScope_responseCode_ServiceDiscoveryType, 
	FAILED_NoServicesFound_responseCode_ServiceDiscoveryType, 
	FAILED_UnknownError_InServiceDiscovery_responseCode_ServiceDiscoveryType

}; 

enum responseCode_ServicePaymentSelectionType
{
	OK_ServicePaymentSelection_responseCode_ServicePaymentSelectionType, 
	FAILED_ServiceSelectionInvalid_responseCode_ServicePaymentSelectionType, 
	FAILED_PaymentSelectionInvalid_responseCode_ServicePaymentSelectionType, 
	FAILED_UnknownError_InServicePaymentSelection_responseCode_ServicePaymentSelectionType

}; 

enum responseCode_PaymentDetailsType
{
	OK_PaymentDetails_responseCode_PaymentDetailsType, 
	FAILED_PaymentDetailsInvalid_responseCode_PaymentDetailsType, 
	FAILED_UnknownError_responseCode_PaymentDetailsType

}; 

enum unitMultiplierType
{
	d_unitMultiplierType, 
	c_unitMultiplierType, 
	m_unitMultiplierType, 
	micro_unitMultiplierType, 
	n_unitMultiplierType, 
	p_unitMultiplierType, 
	k_unitMultiplierType, 
	M_unitMultiplierType, 
	G_unitMultiplierType, 
	T_unitMultiplierType, 
	none_unitMultiplierType

}; 

enum unitSymbolType
{
	A_unitSymbolType, 
	deg_unitSymbolType, 
	F_unitSymbolType, 
	g_unitSymbolType, 
	h_unitSymbolType, 
	J_unitSymbolType, 
	J_s_unitSymbolType, 
	kg_J_unitSymbolType, 
	min_unitSymbolType, 
	N_unitSymbolType, 
	ohm_unitSymbolType, 
	s_unitSymbolType, 
	S_unitSymbolType, 
	s_1_unitSymbolType, 
	V_unitSymbolType, 
	V_VAr_unitSymbolType, 
	VA_unitSymbolType, 
	VAh_unitSymbolType, 
	VAr_unitSymbolType, 
	VArh_unitSymbolType, 
	W_unitSymbolType, 
	W_Hz_unitSymbolType, 
	W_s_unitSymbolType, 
	Wh_unitSymbolType, 
	Ah_unitSymbolType

}; 

enum responseCode_PowerDiscoveryType
{
	OK_PowerDiscovery_responseCode_PowerDiscoveryType, 
	FAILED_UnknownError_InPowerDiscovery_responseCode_PowerDiscoveryType

}; 

enum tariffIDType
{
	Standard_charge_tariffIDType, 
	Fast_charge_tariffIDType, 
	Green_charge_tariffIDType, 
	Grid_friendly_charge_tariffIDType, 
	Freely_parameterisable_charge_tariffIDType, 
	Charge_under_reserve_tariffIDType

}; 

enum responseCode_LineLockType
{
	OK_LineLock_responseCode_LineLockType, 
	FAILED_LineLockNotApplied_responseCode_LineLockType, 
	FAILED_UnknownError_InLineLock_responseCode_LineLockType

}; 

enum responseCode_PowerDeliveryType
{
	OK_PowerDelivery_responseCode_PowerDeliveryType, 
	FAILED_PowerDeliveryNotApplied_responseCode_PowerDeliveryType, 
	FAILED_TariffSelectionInvalid_responseCode_PowerDeliveryType, 
	FAILED_ChargingProfileInvalid_responseCode_PowerDeliveryType, 
	FAILED_UnknownError_InPowerDelivery_responseCode_PowerDeliveryType

}; 

enum responseCode_MeteringStatusType
{
	OK_MeteringStatus_responseCode_MeteringStatusType, 
	FAILED_UnknownError_InMeteringStatus_responseCode_MeteringStatusType

}; 

enum responseCode_MeteringReceiptType
{
	OK_MeteringReceipt_responseCode_MeteringReceiptType, 
	FAILED_UnknownError_MeteringReceipt_responseCode_MeteringReceiptType

}; 




struct arraylen_SessionInformationType_SessionID
{
	size_t data;


};

struct SessionInformationType_SessionID
{
	uint8_t data[8];
	struct arraylen_SessionInformationType_SessionID arraylen;

};

struct arraylen_SessionInformationType_ServiceSessionID
{
	size_t data;


};

struct SessionInformationType_ServiceSessionID
{
	uint8_t data[8];
	struct arraylen_SessionInformationType_ServiceSessionID arraylen;

};

struct selection_SessionInformationType
{
	unsigned int ServiceSessionID:1;
	unsigned int ProtocolVersion:1;


};

struct arraylen_SessionInformationType_ProtocolVersion
{
	size_t data;


};

struct SessionInformationType_ProtocolVersion
{
	uint32_t data[5];
	struct arraylen_SessionInformationType_ProtocolVersion arraylen;

};

struct SessionInformationType
{
	struct SessionInformationType_SessionID SessionID;
	struct SessionInformationType_ServiceSessionID ServiceSessionID;
	struct SessionInformationType_ProtocolVersion ProtocolVersion;
	struct selection_SessionInformationType isused;

};

struct selection_NotificationType
{
	unsigned int FaultCode:1;
	unsigned int FaultMsg:1;
	unsigned int EventList:1;


};

struct arraylen_NotificationType_FaultMsg
{
	size_t data;


};

struct NotificationType_FaultMsg
{
	uint32_t data[256];
	struct arraylen_NotificationType_FaultMsg arraylen;

};

struct EventListType
{
	enum eventEntryType Event;


};

struct NotificationType
{
	enum faultCodeType FaultCode;
	struct NotificationType_FaultMsg FaultMsg;
	struct EventListType EventList;
	struct selection_NotificationType isused;

};

struct selection_HeaderType
{
	unsigned int Notification:1;


};

struct HeaderType
{
	struct SessionInformationType SessionInformation;
	struct NotificationType Notification;
	struct selection_HeaderType isused;

};

struct arraylen_SessionSetupReqType_PEVID
{
	size_t data;


};

struct SessionSetupReqType_PEVID
{
	uint32_t data[32];
	struct arraylen_SessionSetupReqType_PEVID arraylen;

};

struct selection_SessionSetupReqType
{
	unsigned int PEVID:1;


};

struct PEVStatusType
{
	int ConnectorLocked;
	int ChargerStandby;


};

struct SessionSetupReqType
{
	struct SessionSetupReqType_PEVID PEVID;
	struct PEVStatusType PEVStatus;
	struct selection_SessionSetupReqType isused;

};

struct selection_BodyType
{
	unsigned int SessionSetupReq:1;
	unsigned int SessionSetupRes:1;
	unsigned int ServiceDiscoveryReq:1;
	unsigned int ServiceDiscoveryRes:1;
	unsigned int ServicePaymentSelectionReq:1;
	unsigned int ServicePaymentSelectionRes:1;
	unsigned int PaymentDetailsReq:1;
	unsigned int PaymentDetailsRes:1;
	unsigned int PowerDiscoveryReq:1;
	unsigned int PowerDiscoveryRes:1;
	unsigned int LineLockReq:1;
	unsigned int LineLockRes:1;
	unsigned int PowerDeliveryReq:1;
	unsigned int PowerDeliveryRes:1;
	unsigned int MeteringStatusReq:1;
	unsigned int MeteringStatusRes:1;
	unsigned int MeteringReceiptReq:1;
	unsigned int MeteringReceiptRes:1;


};

struct arraylen_SessionSetupResType_EVSEID
{
	size_t data;


};

struct SessionSetupResType_EVSEID
{
	uint8_t data[32];
	struct arraylen_SessionSetupResType_EVSEID arraylen;

};

struct EVSEStatusType
{
	int FatalError;
	int EVSEStandby;
	int ConnectorLocked;
	int PowerSwitchClosed;
	int RCD;
	int32_t ShutDownTime;


};

struct SessionSetupResType
{
	enum responseCode_SessionSetupType ResponseCode;
	struct SessionSetupResType_EVSEID EVSEID;
	struct EVSEStatusType EVSEStatus;
	int32_t TCurrent;


};

struct selection_ServiceDiscoveryReqType
{
	unsigned int ServiceType:1;
	unsigned int ServiceScope:1;


};

struct arraylen_ServiceDiscoveryReqType_ServiceScope
{
	size_t data;


};

struct ServiceDiscoveryReqType_ServiceScope
{
	uint32_t data[20];
	struct arraylen_ServiceDiscoveryReqType_ServiceScope arraylen;

};

struct ServiceDiscoveryReqType
{
	enum serviceTypeType ServiceType;
	struct ServiceDiscoveryReqType_ServiceScope ServiceScope;
	struct selection_ServiceDiscoveryReqType isused;

};

struct arraylen_ServiceDescriptionType_ServiceID
{
	size_t data;


};

struct ServiceDescriptionType_ServiceID
{
	uint8_t data[8];
	struct arraylen_ServiceDescriptionType_ServiceID arraylen;

};

struct arraylen_ServiceDescriptionType_ServiceName
{
	size_t data;


};

struct ServiceDescriptionType_ServiceName
{
	uint32_t data[20];
	struct arraylen_ServiceDescriptionType_ServiceName arraylen;

};

struct selection_ServiceDescriptionType
{
	unsigned int ServiceName:1;
	unsigned int ServiceType:1;
	unsigned int ServiceScope:1;


};

struct arraylen_ServiceDescriptionType_ServiceScope
{
	size_t data;


};

struct ServiceDescriptionType_ServiceScope
{
	uint32_t data[20];
	struct arraylen_ServiceDescriptionType_ServiceScope arraylen;

};

struct ServiceDescriptionType
{
	struct ServiceDescriptionType_ServiceID ServiceID;
	struct ServiceDescriptionType_ServiceName ServiceName;
	enum serviceTypeType ServiceType;
	struct ServiceDescriptionType_ServiceScope ServiceScope;
	struct selection_ServiceDescriptionType isused;

};

struct arraylen_ServiceListType
{
	size_t Service;


};

struct ServiceListType
{
	struct ServiceDescriptionType Service[8];
	struct arraylen_ServiceListType arraylen;

};

struct selection_ServiceDiscoveryResType
{
	unsigned int ServiceList:1;


};

struct ServiceDiscoveryResType
{
	enum responseCode_ServiceDiscoveryType ResponseCode;
	struct ServiceListType ServiceList;
	struct selection_ServiceDiscoveryResType isused;

};

struct ServicePaymentSelectionReqType
{
	struct ServiceListType ServiceList;


};

struct ServicePaymentSelectionResType
{
	enum responseCode_ServicePaymentSelectionType ResponseCode;


};

struct arraylen_PaymentDetailsReqType_ContractID
{
	size_t data;


};

struct PaymentDetailsReqType_ContractID
{
	uint32_t data[128];
	struct arraylen_PaymentDetailsReqType_ContractID arraylen;

};

struct PaymentDetailsReqType
{
	struct PaymentDetailsReqType_ContractID ContractID;


};

struct PaymentDetailsResType
{
	enum responseCode_PaymentDetailsType ResponseCode;


};

struct FloatingValueType
{
	enum unitMultiplierType Multiplier;
	enum unitSymbolType Unit;
	int32_t Value;


};

struct PowerDiscoveryReqType
{
	struct PEVStatusType PEVStatus;
	int32_t EoC;
	struct FloatingValueType EAmount;
	struct FloatingValueType PEVMaxPower;
	int16_t PEVMaxPhases;
	struct FloatingValueType PEVMaxVoltage;
	struct FloatingValueType PEVMinVoltage;


};

struct arraylen_PowerDiscoveryResType_EnergyProvider
{
	size_t data;


};

struct PowerDiscoveryResType_EnergyProvider
{
	uint32_t data[20];
	struct arraylen_PowerDiscoveryResType_EnergyProvider arraylen;

};

struct selection_PowerDiscoveryResType
{
	unsigned int EnergyProvider:1;
	unsigned int TariffTable:1;


};

struct arraylen_TariffTableType_Currency
{
	size_t data;


};

struct TariffTableType_Currency
{
	uint32_t data[3];
	struct arraylen_TariffTableType_Currency arraylen;

};

struct arraylen_TariffDescrType_TariffDescription
{
	size_t data;


};

struct TariffDescrType_TariffDescription
{
	uint32_t data[32];
	struct arraylen_TariffDescrType_TariffDescription arraylen;

};

struct selection_TariffDescrType
{
	unsigned int TariffDescription:1;


};

struct selection_TariffEntryType
{
	unsigned int EPrice:1;


};

struct TariffEntryType
{
	uint32_t TariffStart;
	struct FloatingValueType TariffPMax;
	struct FloatingValueType EPrice;
	struct selection_TariffEntryType isused;

};

struct arraylen_TariffEntriesType
{
	size_t TariffEntry;


};

struct TariffEntriesType
{
	struct TariffEntryType TariffEntry[8];
	struct arraylen_TariffEntriesType arraylen;

};

struct TariffDescrType
{
	enum tariffIDType TariffID;
	struct TariffDescrType_TariffDescription TariffDescription;
	struct TariffEntriesType TariffEntries;
	struct selection_TariffDescrType isused;

};

struct arraylen_TariffTableType
{
	size_t Tariff;


};

struct TariffTableType
{
	struct TariffTableType_Currency Currency;
	struct TariffDescrType Tariff[6];
	struct arraylen_TariffTableType arraylen;

};

struct PowerDiscoveryResType
{
	enum responseCode_PowerDiscoveryType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEVoltage;
	struct FloatingValueType EVSEIMax;
	int16_t EVSEMaxPhases;
	struct PowerDiscoveryResType_EnergyProvider EnergyProvider;
	struct TariffTableType TariffTable;
	struct selection_PowerDiscoveryResType isused;

};

struct LineLockReqType
{
	struct PEVStatusType PEVStatus;
	int ReqLockStatus;


};

struct LineLockResType
{
	enum responseCode_LineLockType ResponseCode;
	struct EVSEStatusType EVSEStatus;


};

struct selection_PowerDeliveryReqType
{
	unsigned int Tariff:1;


};

struct PowerDeliveryReqType
{
	struct PEVStatusType PEVStatus;
	int ReqSwitchStatus;
	enum tariffIDType Tariff;
	struct selection_PowerDeliveryReqType isused;

};

struct PowerDeliveryResType
{
	enum responseCode_PowerDeliveryType ResponseCode;


};

struct MeteringStatusReqType
{

 
	int NO_MEMBER:1;
	
};

struct arraylen_MeteringStatusResType_EVSEID
{
	size_t data;


};

struct MeteringStatusResType_EVSEID
{
	uint8_t data[32];
	struct arraylen_MeteringStatusResType_EVSEID arraylen;

};

struct selection_MeteringStatusResType
{
	unsigned int PCurrent:1;
	unsigned int MeterInfo:1;


};

struct arraylen_MeterInfoType_MeterID
{
	size_t data;


};

struct MeterInfoType_MeterID
{
	uint32_t data[32];
	struct arraylen_MeterInfoType_MeterID arraylen;

};

struct selection_MeterInfoType
{
	unsigned int MeterID:1;
	unsigned int MeterReading:1;
	unsigned int MeterStatus:1;
	unsigned int TMeter:1;


};

struct MeterInfoType
{
	struct MeterInfoType_MeterID MeterID;
	struct FloatingValueType MeterReading;
	int16_t MeterStatus;
	int32_t TMeter;
	struct selection_MeterInfoType isused;

};

struct MeteringStatusResType
{
	enum responseCode_MeteringStatusType ResponseCode;
	struct MeteringStatusResType_EVSEID EVSEID;
	struct EVSEStatusType EVSEStatus;
	int32_t TCurrent;
	struct FloatingValueType EVSEMaxPower;
	struct FloatingValueType PCurrent;
	struct MeterInfoType MeterInfo;
	struct selection_MeteringStatusResType isused;

};

struct arraylen_MeteringReceiptReqType_PEVID
{
	size_t data;


};

struct MeteringReceiptReqType_PEVID
{
	uint32_t data[32];
	struct arraylen_MeteringReceiptReqType_PEVID arraylen;

};

struct selection_MeteringReceiptReqType
{
	unsigned int PEVID:1;
	unsigned int TCurrent:1;


};

struct MeteringReceiptReqType
{
	struct MeteringReceiptReqType_PEVID PEVID;
	struct PEVStatusType PEVStatus;
	int32_t TCurrent;
	enum tariffIDType Tariff;
	struct MeterInfoType MeterInfo;
	struct selection_MeteringReceiptReqType isused;

};

struct MeteringReceiptResType
{
	enum responseCode_MeteringReceiptType ResponseCode;


};

struct BodyType
{
	struct SessionSetupReqType* SessionSetupReq;
	struct SessionSetupResType* SessionSetupRes;
	struct ServiceDiscoveryReqType* ServiceDiscoveryReq;
	struct ServiceDiscoveryResType* ServiceDiscoveryRes;
	struct ServicePaymentSelectionReqType* ServicePaymentSelectionReq;
	struct ServicePaymentSelectionResType* ServicePaymentSelectionRes;
	struct PaymentDetailsReqType* PaymentDetailsReq;
	struct PaymentDetailsResType* PaymentDetailsRes;
	struct PowerDiscoveryReqType* PowerDiscoveryReq;
	struct PowerDiscoveryResType* PowerDiscoveryRes;
	struct LineLockReqType* LineLockReq;
	struct LineLockResType* LineLockRes;
	struct PowerDeliveryReqType* PowerDeliveryReq;
	struct PowerDeliveryResType* PowerDeliveryRes;
	struct MeteringStatusReqType* MeteringStatusReq;
	struct MeteringStatusResType* MeteringStatusRes;
	struct MeteringReceiptReqType* MeteringReceiptReq;
	struct MeteringReceiptResType* MeteringReceiptRes;
	struct selection_BodyType isused;

};

struct AnonType_V2G_Message
{
	struct HeaderType* Header;
	struct BodyType Body;


};

struct EXIDocumentType
{
	struct AnonType_V2G_Message V2G_Message;


};

#endif

#ifdef __cplusplus
}
#endif
