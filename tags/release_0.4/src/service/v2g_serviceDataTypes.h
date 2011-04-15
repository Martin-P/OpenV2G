
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

enum chargingModeType
{
	AC_charging_chargingModeType, 
	DC_charging_chargingModeType

}; 

enum unitSymbolType
{
	A_unitSymbolType, 
	deg_unitSymbolType, 
	F_unitSymbolType, 
	h_unitSymbolType, 
	min_unitSymbolType, 
	s_unitSymbolType, 
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
	Ah_unitSymbolType,
	J_unitSymbolType
}; 

enum responseCode_ChargeParameterDiscoveryType
{
	OK_responseCode_ChargeParameterDiscoveryType, 
	FAILED_BatteryNotCompatible_responseCode_ChargeParameterDiscoveryType, 
	FAILED_UnknownError_responseCode_ChargeParameterDiscoveryType

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

enum responseCode_CableCheckType
{
	OK_responseCode_CableCheckType, 
	FAILED_UnknownError_responseCode_CableCheckType

}; 

enum responseCode_PreChargeType
{
	OK_responseCode_PreChargeType, 
	FAILED_UnknownError_responseCode_PreChargeType

}; 

enum responseCode_CurrentDemandType
{
	OK_responseCode_CurrentDemandType, 
	FAILED_UnknownError_responseCode_CurrentDemandType

}; 

enum responseCode_WeldingDetectionType
{
	OK_responseCode_WeldingDetectionType, 
	FAILED_UnknownError_responseCode_WeldingDetectionType

}; 

enum responseCode_TerminateChargingType
{
	OK_responseCode_TerminateChargingType, 
	FAILED_UnknownError_responseCode_TerminateChargingType

}; 




struct arraylen_sessionIDType
{
	size_t data;


};

struct sessionIDType
{
	uint8_t data[8];
	struct arraylen_sessionIDType arraylen;

};

struct selection_SessionInformationType
{
	unsigned int ServiceSessionID:1;
	unsigned int ProtocolVersion:1;


};

struct arraylen_protocolVersionType
{
	size_t data;


};

struct protocolVersionType
{
	uint32_t data[5];
	struct arraylen_protocolVersionType arraylen;

};

struct SessionInformationType
{
	struct sessionIDType SessionID;
	struct sessionIDType ServiceSessionID;
	struct protocolVersionType ProtocolVersion;
	struct selection_SessionInformationType isused;

};

struct selection_NotificationType
{
	unsigned int FaultCode:1;
	unsigned int FaultMsg:1;
	unsigned int EventList:1;


};

struct arraylen_service_string
{
	size_t data;


};

struct service_string
{
	uint32_t data[256];
	struct arraylen_service_string arraylen;

};

struct EventListType
{
	enum eventEntryType Event;


};

struct NotificationType
{
	enum faultCodeType FaultCode;
	struct service_string FaultMsg;
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

struct arraylen_pevIDType
{
	size_t data;


};

struct pevIDType
{
	uint32_t data[32];
	struct arraylen_pevIDType arraylen;

};

struct selection_SessionSetupReqType
{
	unsigned int PEVID:1;


};

struct PEVStatusType
{
	int ConnectorLocked;
	int ChargerStandby;
	int ReadyToCharge;


};

struct SessionSetupReqType
{
	struct pevIDType PEVID;
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
	unsigned int ChargeParameterDiscoveryReq:1;
	unsigned int ChargeParameterDiscoveryRes:1;
	unsigned int LineLockReq:1;
	unsigned int LineLockRes:1;
	unsigned int PowerDeliveryReq:1;
	unsigned int PowerDeliveryRes:1;
	unsigned int MeteringStatusReq:1;
	unsigned int MeteringStatusRes:1;
	unsigned int MeteringReceiptReq:1;
	unsigned int MeteringReceiptRes:1;
	unsigned int CableCheckReq:1;
	unsigned int CableCheckRes:1;
	unsigned int PreChargeReq:1;
	unsigned int PreChargeRes:1;
	unsigned int CurrentDemandReq:1;
	unsigned int CurrentDemandRes:1;
	unsigned int WeldingDetectionReq:1;
	unsigned int WeldingDetectionRes:1;
	unsigned int TerminateChargingReq:1;
	unsigned int TerminateChargingRes:1;


};

struct arraylen_evseIDType
{
	size_t data;


};

struct evseIDType
{
	uint8_t data[32];
	struct arraylen_evseIDType arraylen;

};

struct EVSEStatusType
{
	int FatalError;
	int EVSEStandby;
	int ConnectorLocked;
	int PowerSwitchClosed;
	int RCD;
	int32_t ShutDownTime;
	int ChargerStandby;
	int EVSEMalfunction;
	int StopCharging;


};

struct SessionSetupResType
{
	enum responseCode_SessionSetupType ResponseCode;
	struct evseIDType EVSEID;
	struct EVSEStatusType EVSEStatus;
	int32_t TCurrent;


};

struct selection_ServiceDiscoveryReqType
{
	unsigned int ServiceType:1;
	unsigned int ServiceScope:1;


};

struct arraylen_serviceScopeType
{
	size_t data;


};

struct serviceScopeType
{
	uint32_t data[20];
	struct arraylen_serviceScopeType arraylen;

};

struct ServiceDiscoveryReqType
{
	enum serviceTypeType ServiceType;
	struct serviceScopeType ServiceScope;
	struct selection_ServiceDiscoveryReqType isused;

};

struct arraylen_serviceIDType
{
	size_t data;


};

struct serviceIDType
{
	uint8_t data[8];
	struct arraylen_serviceIDType arraylen;

};

struct arraylen_serviceNameType
{
	size_t data;


};

struct serviceNameType
{
	uint32_t data[20];
	struct arraylen_serviceNameType arraylen;

};

struct selection_ServiceDescriptionType
{
	unsigned int ServiceName:1;
	unsigned int ServiceType:1;
	unsigned int ServiceScope:1;


};

struct ServiceDescriptionType
{
	struct serviceIDType ServiceID;
	struct serviceNameType ServiceName;
	enum serviceTypeType ServiceType;
	struct serviceScopeType ServiceScope;
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

struct arraylen_contractIDType
{
	size_t data;


};

struct contractIDType
{
	uint32_t data[128];
	struct arraylen_contractIDType arraylen;

};

struct PaymentDetailsReqType
{
	struct contractIDType ContractID;


};

struct PaymentDetailsResType
{
	enum responseCode_PaymentDetailsType ResponseCode;
	int32_t TCurrent;


};

struct FloatingValueType
{
	int16_t Multiplier;
	enum unitSymbolType Unit;
	int32_t Value;


};

struct ChargeParameterDiscoveryReqType
{
	struct PEVStatusType PEVStatus;
	enum chargingModeType ChargingMode;
	int32_t EoC;
	struct FloatingValueType EAmount;
	struct FloatingValueType PEVMaxPower;
	int16_t PEVMaxPhases;
	struct FloatingValueType PEVMaxVoltage;
	struct FloatingValueType PEVMinVoltage;
	struct FloatingValueType PEVMaxCurrent;
	struct FloatingValueType PEVMinCurrent;


};

struct arraylen_energyProviderType
{
	size_t data;


};

struct energyProviderType
{
	uint32_t data[20];
	struct arraylen_energyProviderType arraylen;

};

struct selection_ChargeParameterDiscoveryResType
{
	unsigned int EnergyProvider:1;
	unsigned int TariffTable:1;


};

struct arraylen_currencyType
{
	size_t data;


};

struct currencyType
{
	uint32_t data[3];
	struct arraylen_currencyType arraylen;

};

struct arraylen_tariffDescriptionType
{
	size_t data;


};

struct tariffDescriptionType
{
	uint32_t data[32];
	struct arraylen_tariffDescriptionType arraylen;

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
	struct tariffDescriptionType TariffDescription;
	struct TariffEntriesType TariffEntries;
	struct selection_TariffDescrType isused;

};

struct arraylen_TariffTableType
{
	size_t Tariff;


};

struct TariffTableType
{
	struct currencyType Currency;
	struct TariffDescrType Tariff[6];
	struct arraylen_TariffTableType arraylen;

};

struct ChargeParameterDiscoveryResType
{
	enum responseCode_ChargeParameterDiscoveryType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEMaxVoltage;
	struct FloatingValueType EVSEMinVoltage;
	struct FloatingValueType EVSEMaxCurrent;
	struct FloatingValueType EVSEMinCurrent;
	int16_t EVSEMaxPhases;
	struct energyProviderType EnergyProvider;
	struct TariffTableType TariffTable;
	struct selection_ChargeParameterDiscoveryResType isused;

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
	struct EVSEStatusType EVSEStatus;


};

struct MeteringStatusReqType
{

 
	int NO_MEMBER:1;
	
};

struct selection_MeteringStatusResType
{
	unsigned int PCurrent:1;
	unsigned int MeterInfo:1;


};

struct arraylen_meterIDType
{
	size_t data;


};

struct meterIDType
{
	uint32_t data[32];
	struct arraylen_meterIDType arraylen;

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
	struct meterIDType MeterID;
	struct FloatingValueType MeterReading;
	int16_t MeterStatus;
	int32_t TMeter;
	struct selection_MeterInfoType isused;

};

struct MeteringStatusResType
{
	enum responseCode_MeteringStatusType ResponseCode;
	struct evseIDType EVSEID;
	struct EVSEStatusType EVSEStatus;
	int32_t TCurrent;
	struct FloatingValueType EVSEMaxPower;
	struct FloatingValueType PCurrent;
	struct MeterInfoType MeterInfo;
	struct selection_MeteringStatusResType isused;

};

struct selection_MeteringReceiptReqType
{
	unsigned int PEVID:1;
	unsigned int TCurrent:1;


};

struct MeteringReceiptReqType
{
	struct pevIDType PEVID;
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

struct CableCheckReqType
{
	struct PEVStatusType PEVStatus;


};

struct CableCheckResType
{
	enum responseCode_CableCheckType ResponseCode;
	struct EVSEStatusType EVSEStatus;


};

struct PreChargeReqType
{
	struct PEVStatusType PEVStatus;
	struct FloatingValueType PEVTargetVoltage;
	struct FloatingValueType PEVDemandCurrent;
	struct FloatingValueType VoltageDifferential;


};

struct PreChargeResType
{
	enum responseCode_PreChargeType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;


};

struct CurrentDemandReqType
{
	struct PEVStatusType PEVStatus;
	struct FloatingValueType PEVTargetVoltage;
	struct FloatingValueType PEVDemandCurrent;
	struct FloatingValueType CurrentDifferential;
	struct FloatingValueType VoltageDifferential;


};

struct CurrentDemandResType
{
	enum responseCode_CurrentDemandType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;
	struct FloatingValueType EVSEPresentCurrent;


};

struct WeldingDetectionReqType
{
	struct PEVStatusType PEVStatus;


};

struct WeldingDetectionResType
{
	enum responseCode_WeldingDetectionType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;


};

struct TerminateChargingReqType
{
	struct PEVStatusType PEVStatus;


};

struct TerminateChargingResType
{
	enum responseCode_TerminateChargingType ResponseCode;
	struct EVSEStatusType EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;


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
	struct ChargeParameterDiscoveryReqType* ChargeParameterDiscoveryReq;
	struct ChargeParameterDiscoveryResType* ChargeParameterDiscoveryRes;
	struct LineLockReqType* LineLockReq;
	struct LineLockResType* LineLockRes;
	struct PowerDeliveryReqType* PowerDeliveryReq;
	struct PowerDeliveryResType* PowerDeliveryRes;
	struct MeteringStatusReqType* MeteringStatusReq;
	struct MeteringStatusResType* MeteringStatusRes;
	struct MeteringReceiptReqType* MeteringReceiptReq;
	struct MeteringReceiptResType* MeteringReceiptRes;
	struct CableCheckReqType* CableCheckReq;
	struct CableCheckResType* CableCheckRes;
	struct PreChargeReqType* PreChargeReq;
	struct PreChargeResType* PreChargeRes;
	struct CurrentDemandReqType* CurrentDemandReq;
	struct CurrentDemandResType* CurrentDemandRes;
	struct WeldingDetectionReqType* WeldingDetectionReq;
	struct WeldingDetectionResType* WeldingDetectionRes;
	struct TerminateChargingReqType* TerminateChargingReq;
	struct TerminateChargingResType* TerminateChargingRes;
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
