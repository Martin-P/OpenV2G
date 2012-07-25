
/*
 * Copyright (C) 2007-2012 Siemens AG
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
 * @version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXISeGen</p>
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
	ParsingError_faultCodeType=0, 
	NoTLSRootCertificatAvailable_faultCodeType=1, 
	UnknownError_faultCodeType=2

}; 

enum responseCodeType
{
	OK_responseCodeType=0, 
	OK_NewSessionEstablished_responseCodeType=1, 
	OK_OldSessionJoined_responseCodeType=2, 
	OK_CertificateExpiresSoon_responseCodeType=3, 
	FAILED_responseCodeType=4, 
	FAILED_SequenceError_responseCodeType=5, 
	FAILED_ServiceIDInvalid_responseCodeType=6, 
	FAILED_UnknownSession_responseCodeType=7, 
	FAILED_ServiceSelectionInvalid_responseCodeType=8, 
	FAILED_PaymentSelectionInvalid_responseCodeType=9, 
	FAILED_CertificateExpired_responseCodeType=10, 
	FAILED_SignatureError_responseCodeType=11, 
	FAILED_NoCertificateAvailable_responseCodeType=12, 
	FAILED_CertChainError_responseCodeType=13, 
	FAILED_ChallengeInvalid_responseCodeType=14, 
	FAILED_ContractCanceled_responseCodeType=15, 
	FAILED_WrongChargeParameter_responseCodeType=16, 
	FAILED_PowerDeliveryNotApplied_responseCodeType=17, 
	FAILED_TariffSelectionInvalid_responseCodeType=18, 
	FAILED_ChargingProfileInvalid_responseCodeType=19, 
	FAILED_EVSEPresentVoltageToLow_responseCodeType=20, 
	FAILED_MeteringSignatureNotValid_responseCodeType=21, 
	FAILED_WrongEnergyTransferType_responseCodeType=22

}; 

enum serviceCategoryType
{
	EVCharging_serviceCategoryType=0, 
	Internet_serviceCategoryType=1, 
	ContractCertificate_serviceCategoryType=2, 
	OtherCustom_serviceCategoryType=3

}; 

enum paymentOptionType
{
	Contract_paymentOptionType=0, 
	ExternalPayment_paymentOptionType=1

}; 

enum EVSESupportedEnergyTransferType
{
	AC_single_phase_core_EVSESupportedEnergyTransferType=0, 
	AC_three_phase_core_EVSESupportedEnergyTransferType=1, 
	DC_core_EVSESupportedEnergyTransferType=2, 
	DC_extended_EVSESupportedEnergyTransferType=3, 
	DC_combo_core_EVSESupportedEnergyTransferType=4, 
	DC_dual_EVSESupportedEnergyTransferType=5, 
	AC_core1p_DC_extended_EVSESupportedEnergyTransferType=6, 
	AC_single_DC_core_EVSESupportedEnergyTransferType=7, 
	AC_single_phase_three_phase_core_DC_extended_EVSESupportedEnergyTransferType=8, 
	AC_core3p_DC_extended_EVSESupportedEnergyTransferType=9

}; 

enum unitSymbolType
{
	h_unitSymbolType=0, 
	m_unitSymbolType=1, 
	s_unitSymbolType=2, 
	A_unitSymbolType=3, 
	Ah_unitSymbolType=4, 
	V_unitSymbolType=5, 
	VA_unitSymbolType=6, 
	W_unitSymbolType=7, 
	W_s_unitSymbolType=8, 
	Wh_unitSymbolType=9

}; 

enum EVSEProcessingType
{
	Finished_EVSEProcessingType=0, 
	Ongoing_EVSEProcessingType=1

}; 

enum EVRequestedEnergyTransferType
{
	AC_single_phase_core_EVRequestedEnergyTransferType=0, 
	AC_three_phase_core_EVRequestedEnergyTransferType=1, 
	DC_core_EVRequestedEnergyTransferType=2, 
	DC_extended_EVRequestedEnergyTransferType=3, 
	DC_combo_core_EVRequestedEnergyTransferType=4, 
	DC_unique_EVRequestedEnergyTransferType=5

}; 

enum DC_EVErrorCodeType
{
	NO_ERROR_DC_EVErrorCodeType=0, 
	FAILED_RESSTemperatureInhibit_DC_EVErrorCodeType=1, 
	FAILED_EVShiftPosition_DC_EVErrorCodeType=2, 
	FAILED_ChargerConnectorLockFault_DC_EVErrorCodeType=3, 
	FAILED_EVRESSMalfunction_DC_EVErrorCodeType=4, 
	FAILED_ChargingCurrentdifferential_DC_EVErrorCodeType=5, 
	FAILED_ChargingVoltageOutOfRange_DC_EVErrorCodeType=6, 
	Reserved_A_DC_EVErrorCodeType=7, 
	Reserved_B_DC_EVErrorCodeType=8, 
	Reserved_C_DC_EVErrorCodeType=9, 
	FAILED_ChargingSystemIncompatibility_DC_EVErrorCodeType=10, 
	NoData_DC_EVErrorCodeType=11

}; 

enum costKindType
{
	relativePricePercentage_costKindType=0, 
	RenewableGenerationPercentage_costKindType=1, 
	CarbonDioxideEmission_costKindType=2

}; 

enum EVSENotificationType
{
	None_EVSENotificationType=0, 
	StopCharging_EVSENotificationType=1, 
	ReNegotiation_EVSENotificationType=2

}; 

enum isolationLevelType
{
	Invalid_isolationLevelType=0, 
	Valid_isolationLevelType=1, 
	Warning_isolationLevelType=2, 
	Fault_isolationLevelType=3

}; 

enum DC_EVSEStatusCodeType
{
	EVSE_NotReady_DC_EVSEStatusCodeType=0, 
	EVSE_Ready_DC_EVSEStatusCodeType=1, 
	EVSE_Shutdown_DC_EVSEStatusCodeType=2, 
	EVSE_UtilityInterruptEvent_DC_EVSEStatusCodeType=3, 
	EVSE_IsolationMonitoringActive_DC_EVSEStatusCodeType=4, 
	EVSE_EmergencyShutdown_DC_EVSEStatusCodeType=5, 
	EVSE_Malfunction_DC_EVSEStatusCodeType=6, 
	Reserved_8_DC_EVSEStatusCodeType=7, 
	Reserved_9_DC_EVSEStatusCodeType=8, 
	Reserved_A_DC_EVSEStatusCodeType=9, 
	Reserved_B_DC_EVSEStatusCodeType=10, 
	Reserved_C_DC_EVSEStatusCodeType=11

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

struct arraylen_faultMsgType
{
	size_t data;


};

struct faultMsgType
{
	uint32_t data[64];
	struct arraylen_faultMsgType arraylen;

};

struct selection_NotificationType
{
	unsigned int FaultMsg:1;


};

struct NotificationType
{
	enum faultCodeType FaultCode;
	struct faultMsgType FaultMsg;
	struct selection_NotificationType isused;

};

struct selection_MessageHeaderType
{
	unsigned int Notification:1;
	unsigned int Signature:1;


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

struct selection_SignatureType
{
	unsigned int attr_Id:1;
	unsigned int KeyInfo:1;


};

struct selection_SignedInfoType
{
	unsigned int attr_Id:1;


};

struct CanonicalizationMethodType
{
	struct service_string attr_Algorithm;


};

struct SignatureMethodType
{
	struct service_string attr_Algorithm;


};

struct selection_ReferenceType
{
	unsigned int attr_Id:1;
	unsigned int attr_URI:1;
	unsigned int attr_Type:1;


};

struct DigestMethodType
{
	struct service_string attr_Algorithm;


};

struct arraylen_DigestValueType
{
	size_t data;


};

struct DigestValueType
{
	uint8_t data[128];
	struct arraylen_DigestValueType arraylen;

};

struct ReferenceType
{
	struct service_string attr_Id;
	struct service_string attr_URI;
	struct service_string attr_Type;
	struct DigestMethodType DigestMethod;
	struct DigestValueType DigestValue;
	struct selection_ReferenceType isused;

};

struct arraylen_SignedInfoType
{
	size_t Reference;


};

struct SignedInfoType
{
	struct service_string attr_Id;
	struct CanonicalizationMethodType CanonicalizationMethod;
	struct SignatureMethodType SignatureMethod;
	struct ReferenceType Reference[1];
	struct selection_SignedInfoType isused;	struct arraylen_SignedInfoType arraylen;

};

struct arraylen_SignatureValueType
{
	size_t data;


};

struct SignatureValueType
{
	uint8_t data[128];
	struct arraylen_SignatureValueType arraylen;


};

struct selection_KeyInfoType
{
	unsigned int attr_Id:1;


};

struct X509IssuerSerialType
{
	struct service_string X509IssuerName;
	int64_t X509SerialNumber;


};

struct arraylen_service_byte
{
	size_t data;


};

struct service_byte
{
	uint8_t data[128];
	struct arraylen_service_byte arraylen;

};

struct X509DataType
{
	struct X509IssuerSerialType X509IssuerSerial;
	struct service_byte X509SKI;
	struct service_string X509SubjectName;
	struct service_byte X509Certificate;
	struct service_byte X509CRL;


};

struct KeyInfoType
{
	struct service_string attr_Id;
	struct X509DataType X509Data;
	struct selection_KeyInfoType isused;

};

struct SignatureType
{
	struct service_string attr_Id;
	struct SignedInfoType SignedInfo;
	struct SignatureValueType SignatureValue;
	struct KeyInfoType KeyInfo;
	struct selection_SignatureType isused;

};

struct MessageHeaderType
{
	struct sessionIDType SessionID;
	struct NotificationType Notification;
	struct SignatureType* Signature;
	struct selection_MessageHeaderType isused;

};

struct arraylen_evccIDType
{
	size_t data;


};

struct evccIDType
{
	uint8_t data[8];
	struct arraylen_evccIDType arraylen;

};

struct SessionSetupReqType
{
	struct evccIDType EVCCID;


};

struct selection_BodyType
{
	unsigned int SessionSetupReq:1;
	unsigned int SessionSetupRes:1;
	unsigned int ServiceDiscoveryReq:1;
	unsigned int ServiceDiscoveryRes:1;
	unsigned int ServiceDetailReq:1;
	unsigned int ServiceDetailRes:1;
	unsigned int ServicePaymentSelectionReq:1;
	unsigned int ServicePaymentSelectionRes:1;
	unsigned int PaymentDetailsReq:1;
	unsigned int PaymentDetailsRes:1;
	unsigned int ContractAuthenticationReq:1;
	unsigned int ContractAuthenticationRes:1;
	unsigned int ChargeParameterDiscoveryReq:1;
	unsigned int ChargeParameterDiscoveryRes:1;
	unsigned int PowerDeliveryReq:1;
	unsigned int PowerDeliveryRes:1;
	unsigned int ChargingStatusReq:1;
	unsigned int ChargingStatusRes:1;
	unsigned int MeteringReceiptReq:1;
	unsigned int MeteringReceiptRes:1;
	unsigned int SessionStopReq:1;
	unsigned int SessionStopRes:1;
	unsigned int CertificateUpdateReq:1;
	unsigned int CertificateUpdateRes:1;
	unsigned int CertificateInstallationReq:1;
	unsigned int CertificateInstallationRes:1;
	unsigned int CableCheckReq:1;
	unsigned int CableCheckRes:1;
	unsigned int PreChargeReq:1;
	unsigned int PreChargeRes:1;
	unsigned int CurrentDemandReq:1;
	unsigned int CurrentDemandRes:1;
	unsigned int WeldingDetectionReq:1;
	unsigned int WeldingDetectionRes:1;


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

struct selection_SessionSetupResType
{
	unsigned int DateTimeNow:1;


};

struct SessionSetupResType
{
	enum responseCodeType ResponseCode;
	struct evseIDType EVSEID;
	int64_t DateTimeNow;
	struct selection_SessionSetupResType isused;

};

struct arraylen_serviceScopeType
{
	size_t data;


};

struct serviceScopeType
{
	uint32_t data[32];
	struct arraylen_serviceScopeType arraylen;

};

struct selection_ServiceDiscoveryReqType
{
	unsigned int ServiceScope:1;
	unsigned int ServiceCategory:1;


};

struct ServiceDiscoveryReqType
{
	struct serviceScopeType ServiceScope;
	enum serviceCategoryType ServiceCategory;
	struct selection_ServiceDiscoveryReqType isused;

};

struct arraylen_PaymentOptionsType
{
	size_t PaymentOption;


};

struct PaymentOptionsType
{
	enum paymentOptionType PaymentOption[2];
	struct arraylen_PaymentOptionsType arraylen;

};

struct arraylen_serviceNameType
{
	size_t data;


};

struct serviceNameType
{
	uint32_t data[32];
	struct arraylen_serviceNameType arraylen;

};

struct selection_ServiceTagType
{
	unsigned int ServiceName:1;
	unsigned int ServiceScope:1;


};

struct ServiceTagType
{
	uint16_t ServiceID;
	struct serviceNameType ServiceName;
	enum serviceCategoryType ServiceCategory;
	struct serviceScopeType ServiceScope;
	struct selection_ServiceTagType isused;

};

struct ServiceChargeType
{
	struct ServiceTagType ServiceTag;
	int FreeService;
	enum EVSESupportedEnergyTransferType EnergyTransferType;


};

struct ServiceType
{
	struct ServiceTagType ServiceTag;
	int FreeService;


};

struct arraylen_ServiceTagListType
{
	size_t Service;


};

struct ServiceTagListType
{
	struct ServiceType Service[3];
	struct arraylen_ServiceTagListType arraylen;

};

struct selection_ServiceDiscoveryResType
{
	unsigned int ServiceList:1;


};

struct ServiceDiscoveryResType
{
	enum responseCodeType ResponseCode;
	struct PaymentOptionsType PaymentOptions;
	struct ServiceChargeType ChargeService;
	struct ServiceTagListType ServiceList;
	struct selection_ServiceDiscoveryResType isused;

};

struct ServiceDetailReqType
{
	uint16_t ServiceID;


};

struct selection_PhysicalValueType
{
	unsigned int Unit:1;


};

struct PhysicalValueType
{
	int8_t Multiplier;
	enum unitSymbolType Unit;
	int16_t Value;
	struct selection_PhysicalValueType isused;

};

struct ParameterType
{
	struct service_string attr_Name;
	struct service_string attr_ValueType;
	int boolValue;
	int8_t byteValue;
	int16_t shortValue;
	int32_t intValue;
	struct PhysicalValueType physicalValue;
	struct service_string stringValue;


};

struct arraylen_ParameterSetType
{
	size_t Parameter;


};

struct ParameterSetType
{
	int16_t ParameterSetID;
	struct ParameterType Parameter[2];
	struct arraylen_ParameterSetType arraylen;

};

struct arraylen_ServiceParameterListType
{
	size_t ParameterSet;


};

struct ServiceParameterListType
{
	struct ParameterSetType ParameterSet[2];
	struct arraylen_ServiceParameterListType arraylen;

};

struct selection_ServiceDetailResType
{
	unsigned int ServiceParameterList:1;


};

struct ServiceDetailResType
{
	enum responseCodeType ResponseCode;
	uint16_t ServiceID;
	struct ServiceParameterListType ServiceParameterList;
	struct selection_ServiceDetailResType isused;

};

struct selection_SelectedServiceType
{
	unsigned int ParameterSetID:1;


};

struct SelectedServiceType
{
	uint16_t ServiceID;
	int16_t ParameterSetID;
	struct selection_SelectedServiceType isused;

};

struct arraylen_SelectedServiceListType
{
	size_t SelectedService;


};

struct SelectedServiceListType
{
	struct SelectedServiceType SelectedService[2];
	struct arraylen_SelectedServiceListType arraylen;

};

struct ServicePaymentSelectionReqType
{
	enum paymentOptionType SelectedPaymentOption;
	struct SelectedServiceListType SelectedServiceList;


};

struct ServicePaymentSelectionResType
{
	enum responseCodeType ResponseCode;


};

struct arraylen_contractIDType
{
	size_t data;


};

struct contractIDType
{
	uint32_t data[24];
	struct arraylen_contractIDType arraylen;

};

struct arraylen_certificateType
{
	size_t data;


};

struct certificateType
{
	uint8_t data[1200];
	struct arraylen_certificateType arraylen;

};

struct arraylen_SubCertificatesType
{
	size_t Certificate;


};

struct SubCertificatesType
{
	struct certificateType Certificate[4];
	struct arraylen_SubCertificatesType arraylen;

};

struct selection_CertificateChainType
{
	unsigned int SubCertificates:1;


};

struct CertificateChainType
{
	struct certificateType Certificate;
	struct SubCertificatesType SubCertificates;
	struct selection_CertificateChainType isused;

};

struct PaymentDetailsReqType
{
	struct contractIDType ContractID;
	struct CertificateChainType ContractSignatureCertChain;


};

struct arraylen_genChallengeType
{
	size_t data;


};

struct genChallengeType
{
	uint32_t data[256];
	struct arraylen_genChallengeType arraylen;

};

struct PaymentDetailsResType
{
	enum responseCodeType ResponseCode;
	struct genChallengeType GenChallenge;
	int64_t DateTimeNow;


};

struct selection_ContractAuthenticationReqType
{
	unsigned int attr_Id:1;
	unsigned int GenChallenge:1;


};

struct ContractAuthenticationReqType
{
	struct service_string attr_Id;
	struct genChallengeType GenChallenge;
	struct selection_ContractAuthenticationReqType isused;

};

struct ContractAuthenticationResType
{
	enum responseCodeType ResponseCode;
	enum EVSEProcessingType EVSEProcessing;


};

struct AC_EVChargeParameterType
{
	uint32_t DepartureTime;
	struct PhysicalValueType EAmount;
	struct PhysicalValueType EVMaxVoltage;
	struct PhysicalValueType EVMaxCurrent;
	struct PhysicalValueType EVMinCurrent;


};

struct selection_ChargeParameterDiscoveryReqType
{
	unsigned int AC_EVChargeParameter:1;
	unsigned int DC_EVChargeParameter:1;


};

struct selection_DC_EVStatusType
{
	unsigned int EVCabinConditioning:1;
	unsigned int EVRESSConditioning:1;


};

struct DC_EVStatusType
{
	int EVReady;
	int EVCabinConditioning;
	int EVRESSConditioning;
	enum DC_EVErrorCodeType EVErrorCode;
	int8_t EVRESSSOC;
	struct selection_DC_EVStatusType isused;

};

struct selection_DC_EVChargeParameterType
{
	unsigned int EVMaximumPowerLimit:1;
	unsigned int EVEnergyCapacity:1;
	unsigned int EVEnergyRequest:1;
	unsigned int FullSOC:1;
	unsigned int BulkSOC:1;


};

struct DC_EVChargeParameterType
{
	struct DC_EVStatusType DC_EVStatus;
	struct PhysicalValueType EVMaximumCurrentLimit;
	struct PhysicalValueType EVMaximumPowerLimit;
	struct PhysicalValueType EVMaximumVoltageLimit;
	struct PhysicalValueType EVEnergyCapacity;
	struct PhysicalValueType EVEnergyRequest;
	int8_t FullSOC;
	int8_t BulkSOC;
	struct selection_DC_EVChargeParameterType isused;

};

struct ChargeParameterDiscoveryReqType
{
	enum EVRequestedEnergyTransferType EVRequestedEnergyTransferType;
	struct AC_EVChargeParameterType* AC_EVChargeParameter;
	struct DC_EVChargeParameterType* DC_EVChargeParameter;
	struct selection_ChargeParameterDiscoveryReqType isused;

};

struct selection_RelativeTimeIntervalType
{
	unsigned int duration:1;


};

struct RelativeTimeIntervalType
{
	uint32_t start;
	uint32_t duration;
	struct selection_RelativeTimeIntervalType isused;

};

struct PMaxScheduleEntryType
{
	struct RelativeTimeIntervalType RelativeTimeInterval;
	int16_t PMax;


};

struct arraylen_PMaxScheduleType
{
	size_t PMaxScheduleEntry;


};

struct PMaxScheduleType
{
	int16_t PMaxScheduleID;
	struct PMaxScheduleEntryType PMaxScheduleEntry[12];
	struct arraylen_PMaxScheduleType arraylen;

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

struct selection_SalesTariffType
{
	unsigned int SalesTariffDescription:1;


};

struct selection_CostType
{
	unsigned int amountMultiplier:1;


};

struct CostType
{
	enum costKindType costKind;
	uint32_t amount;
	int8_t amountMultiplier;
	struct selection_CostType isused;

};

struct selection_ConsumptionCostType
{
	unsigned int Cost:1;


};

struct arraylen_ConsumptionCostType
{
	size_t Cost;


};

struct ConsumptionCostType
{
	uint32_t startValue;
	struct CostType Cost[2];
	struct selection_ConsumptionCostType isused;	struct arraylen_ConsumptionCostType arraylen;

};

struct selection_SalesTariffEntryType
{
	unsigned int ConsumptionCost:1;


};

struct arraylen_SalesTariffEntryType
{
	size_t ConsumptionCost;


};

struct SalesTariffEntryType
{
	struct RelativeTimeIntervalType RelativeTimeInterval;
	uint8_t EPriceLevel;
	struct ConsumptionCostType ConsumptionCost[2];
	struct selection_SalesTariffEntryType isused;	struct arraylen_SalesTariffEntryType arraylen;

};

struct arraylen_SalesTariffType
{
	size_t SalesTariffEntry;


};

struct SalesTariffType
{
	struct service_string attr_Id;
	int16_t SalesTariffID;
	struct tariffDescriptionType SalesTariffDescription;
	uint8_t NumEPriceLevels;
	struct SalesTariffEntryType SalesTariffEntry[12];
	struct selection_SalesTariffType isused;
	struct arraylen_SalesTariffType arraylen;

};

struct selection_SAScheduleTupleType
{
	unsigned int SalesTariff:1;


};

struct SAScheduleTupleType
{
	int16_t SAScheduleTupleID;
	struct PMaxScheduleType PMaxSchedule;
	struct SalesTariffType* SalesTariff;
	struct selection_SAScheduleTupleType isused;

};

struct arraylen_SAScheduleListType
{
	size_t SAScheduleTuple;


};

struct SAScheduleListType
{
	struct SAScheduleTupleType SAScheduleTuple[3];
	struct arraylen_SAScheduleListType arraylen;

};

struct AC_EVSEStatusType
{
	int PowerSwitchClosed;
	int RCD;
	uint32_t NotificationMaxDelay;
	enum EVSENotificationType EVSENotification;


};

struct AC_EVSEChargeParameterType
{
	struct AC_EVSEStatusType AC_EVSEStatus;
	struct PhysicalValueType EVSEMaxVoltage;
	struct PhysicalValueType EVSEMaxCurrent;
	struct PhysicalValueType EVSEMinCurrent;


};

struct selection_ChargeParameterDiscoveryResType
{
	unsigned int AC_EVSEChargeParameter:1;
	unsigned int DC_EVSEChargeParameter:1;


};

struct selection_DC_EVSEStatusType
{
	unsigned int EVSEIsolationStatus:1;


};

struct DC_EVSEStatusType
{
	enum isolationLevelType EVSEIsolationStatus;
	enum DC_EVSEStatusCodeType EVSEStatusCode;
	uint32_t NotificationMaxDelay;
	enum EVSENotificationType EVSENotification;
	struct selection_DC_EVSEStatusType isused;

};

struct selection_DC_EVSEChargeParameterType
{
	unsigned int EVSEMaximumPowerLimit:1;
	unsigned int EVSECurrentRegulationTolerance:1;
	unsigned int EVSEEnergyToBeDelivered:1;


};

struct DC_EVSEChargeParameterType
{
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct PhysicalValueType EVSEMaximumCurrentLimit;
	struct PhysicalValueType EVSEMaximumPowerLimit;
	struct PhysicalValueType EVSEMaximumVoltageLimit;
	struct PhysicalValueType EVSEMinimumCurrentLimit;
	struct PhysicalValueType EVSEMinimumVoltageLimit;
	struct PhysicalValueType EVSECurrentRegulationTolerance;
	struct PhysicalValueType EVSEPeakCurrentRipple;
	struct PhysicalValueType EVSEEnergyToBeDelivered;
	struct selection_DC_EVSEChargeParameterType isused;

};

struct ChargeParameterDiscoveryResType
{
	enum responseCodeType ResponseCode;
	enum EVSEProcessingType EVSEProcessing;
	struct SAScheduleListType SAScheduleList;
	struct AC_EVSEChargeParameterType* AC_EVSEChargeParameter;
	struct DC_EVSEChargeParameterType* DC_EVSEChargeParameter;
	struct selection_ChargeParameterDiscoveryResType isused;

};

struct ProfileEntryType
{
	uint32_t ChargingProfileEntryStart;
	int16_t ChargingProfileEntryMaxPower;


};

struct arraylen_ChargingProfileType
{
	size_t ProfileEntry;


};

struct ChargingProfileType
{
	int16_t SAScheduleTupleID;
	struct ProfileEntryType ProfileEntry[24];
	struct arraylen_ChargingProfileType arraylen;

};

struct selection_PowerDeliveryReqType
{
	unsigned int ChargingProfile:1;
	unsigned int DC_EVPowerDeliveryParameter:1;


};

struct selection_DC_EVPowerDeliveryParameterType
{
	unsigned int BulkChargingComplete:1;


};

struct DC_EVPowerDeliveryParameterType
{
	struct DC_EVStatusType DC_EVStatus;
	int BulkChargingComplete;
	int ChargingComplete;
	struct selection_DC_EVPowerDeliveryParameterType isused;

};

struct PowerDeliveryReqType
{
	int ReadyToChargeState;
	struct ChargingProfileType ChargingProfile;
	struct DC_EVPowerDeliveryParameterType* DC_EVPowerDeliveryParameter;
	struct selection_PowerDeliveryReqType isused;

};

struct selection_PowerDeliveryResType
{
	unsigned int AC_EVSEStatus:1;
	unsigned int DC_EVSEStatus:1;


};

struct PowerDeliveryResType
{
	enum responseCodeType ResponseCode;
	struct AC_EVSEStatusType* AC_EVSEStatus;
	struct DC_EVSEStatusType* DC_EVSEStatus;
	struct selection_PowerDeliveryResType isused;

};

struct ChargingStatusReqType
{

 
	int NO_MEMBER:1;
	
};

struct selection_ChargingStatusResType
{
	unsigned int EVSEMaxCurrent:1;
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
	unsigned int MeterReading:1;
	unsigned int SigMeterReading:1;
	unsigned int MeterStatus:1;
	unsigned int TMeter:1;


};

struct arraylen_sigMeterReadingType
{
	size_t data;


};

struct sigMeterReadingType
{
	uint8_t data[32];
	struct arraylen_sigMeterReadingType arraylen;

};

struct MeterInfoType
{
	struct meterIDType MeterID;
	struct PhysicalValueType MeterReading;
	struct sigMeterReadingType SigMeterReading;
	int16_t MeterStatus;
	int64_t TMeter;
	struct selection_MeterInfoType isused;

};

struct ChargingStatusResType
{
	enum responseCodeType ResponseCode;
	struct evseIDType EVSEID;
	int16_t SAScheduleTupleID;
	struct PhysicalValueType EVSEMaxCurrent;
	struct MeterInfoType MeterInfo;
	int ReceiptRequired;
	struct AC_EVSEStatusType AC_EVSEStatus;
	struct selection_ChargingStatusResType isused;

};

struct selection_MeteringReceiptReqType
{
	unsigned int attr_Id:1;
	unsigned int SAScheduleTupleID:1;


};

struct MeteringReceiptReqType
{
	struct service_string attr_Id;
	struct sessionIDType SessionID;
	int16_t SAScheduleTupleID;
	struct MeterInfoType MeterInfo;
	struct selection_MeteringReceiptReqType isused;

};

struct MeteringReceiptResType
{
	enum responseCodeType ResponseCode;
	struct AC_EVSEStatusType AC_EVSEStatus;


};

struct SessionStopType
{

 
	int NO_MEMBER:1;
	
};

struct SessionStopResType
{
	enum responseCodeType ResponseCode;


};

struct selection_CertificateUpdateReqType
{
	unsigned int attr_Id:1;


};

struct arraylen_rootCertificateIDType
{
	size_t data;


};

struct rootCertificateIDType
{
	uint32_t data[40];
	struct arraylen_rootCertificateIDType arraylen;

};

struct arraylen_ListOfRootCertificateIDsType
{
	size_t RootCertificateID;


};

struct ListOfRootCertificateIDsType
{
	struct rootCertificateIDType RootCertificateID[20];
	struct arraylen_ListOfRootCertificateIDsType arraylen;

};

struct arraylen_dHParamsType
{
	size_t data;


};

struct dHParamsType
{
	uint8_t data[256];
	struct arraylen_dHParamsType arraylen;

};

struct CertificateUpdateReqType
{
	struct service_string attr_Id;
	struct CertificateChainType ContractSignatureCertChain;
	struct contractIDType ContractID;
	struct ListOfRootCertificateIDsType ListOfRootCertificateIDs;
	struct dHParamsType DHParams;
	struct selection_CertificateUpdateReqType isused;

};

struct arraylen_privateKeyType
{
	size_t data;


};

struct privateKeyType
{
	uint8_t data[128];
	struct arraylen_privateKeyType arraylen;

};

struct CertificateUpdateResType
{
	struct service_string attr_Id;
	enum responseCodeType ResponseCode;
	struct CertificateChainType ContractSignatureCertChain;
	struct privateKeyType ContractSignatureEncryptedPrivateKey;
	struct dHParamsType DHParams;
	struct contractIDType ContractID;
	int16_t RetryCounter;


};

struct selection_CertificateInstallationReqType
{
	unsigned int attr_Id:1;


};

struct CertificateInstallationReqType
{
	struct service_string attr_Id;
	struct certificateType OEMProvisioningCert;
	struct ListOfRootCertificateIDsType ListOfRootCertificateIDs;
	struct dHParamsType DHParams;
	struct selection_CertificateInstallationReqType isused;

};

struct CertificateInstallationResType
{
	struct service_string attr_Id;
	enum responseCodeType ResponseCode;
	struct CertificateChainType ContractSignatureCertChain;
	struct privateKeyType ContractSignatureEncryptedPrivateKey;
	struct dHParamsType DHParams;
	struct contractIDType ContractID;


};

struct CableCheckReqType
{
	struct DC_EVStatusType DC_EVStatus;


};

struct CableCheckResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	enum EVSEProcessingType EVSEProcessing;


};

struct PreChargeReqType
{
	struct DC_EVStatusType DC_EVStatus;
	struct PhysicalValueType EVTargetVoltage;
	struct PhysicalValueType EVTargetCurrent;


};

struct PreChargeResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct PhysicalValueType EVSEPresentVoltage;


};

struct selection_CurrentDemandReqType
{
	unsigned int EVMaximumVoltageLimit:1;
	unsigned int EVMaximumCurrentLimit:1;
	unsigned int EVMaximumPowerLimit:1;
	unsigned int BulkChargingComplete:1;
	unsigned int RemainingTimeToFullSoC:1;
	unsigned int RemainingTimeToBulkSoC:1;


};

struct CurrentDemandReqType
{
	struct DC_EVStatusType DC_EVStatus;
	struct PhysicalValueType EVTargetCurrent;
	struct PhysicalValueType EVMaximumVoltageLimit;
	struct PhysicalValueType EVMaximumCurrentLimit;
	struct PhysicalValueType EVMaximumPowerLimit;
	int BulkChargingComplete;
	int ChargingComplete;
	struct PhysicalValueType RemainingTimeToFullSoC;
	struct PhysicalValueType RemainingTimeToBulkSoC;
	struct PhysicalValueType EVTargetVoltage;
	struct selection_CurrentDemandReqType isused;

};

struct selection_CurrentDemandResType
{
	unsigned int EVSEMaximumVoltageLimit:1;
	unsigned int EVSEMaximumCurrentLimit:1;
	unsigned int EVSEMaximumPowerLimit:1;


};

struct CurrentDemandResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct PhysicalValueType EVSEPresentVoltage;
	struct PhysicalValueType EVSEPresentCurrent;
	int EVSECurrentLimitAchieved;
	int EVSEVoltageLimitAchieved;
	int EVSEPowerLimitAchieved;
	struct PhysicalValueType EVSEMaximumVoltageLimit;
	struct PhysicalValueType EVSEMaximumCurrentLimit;
	struct PhysicalValueType EVSEMaximumPowerLimit;
	struct selection_CurrentDemandResType isused;

};

struct WeldingDetectionReqType
{
	struct DC_EVStatusType DC_EVStatus;


};

struct WeldingDetectionResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct PhysicalValueType EVSEPresentVoltage;


};

struct BodyType
{
	struct SessionSetupReqType* SessionSetupReq;
	struct SessionSetupResType* SessionSetupRes;
	struct ServiceDiscoveryReqType* ServiceDiscoveryReq;
	struct ServiceDiscoveryResType* ServiceDiscoveryRes;
	struct ServiceDetailReqType* ServiceDetailReq;
	struct ServiceDetailResType* ServiceDetailRes;
	struct ServicePaymentSelectionReqType* ServicePaymentSelectionReq;
	struct ServicePaymentSelectionResType* ServicePaymentSelectionRes;
	struct PaymentDetailsReqType* PaymentDetailsReq;
	struct PaymentDetailsResType* PaymentDetailsRes;
	struct ContractAuthenticationReqType* ContractAuthenticationReq;
	struct ContractAuthenticationResType* ContractAuthenticationRes;
	struct ChargeParameterDiscoveryReqType* ChargeParameterDiscoveryReq;
	struct ChargeParameterDiscoveryResType* ChargeParameterDiscoveryRes;
	struct PowerDeliveryReqType* PowerDeliveryReq;
	struct PowerDeliveryResType* PowerDeliveryRes;
	struct ChargingStatusReqType* ChargingStatusReq;
	struct ChargingStatusResType* ChargingStatusRes;
	struct MeteringReceiptReqType* MeteringReceiptReq;
	struct MeteringReceiptResType* MeteringReceiptRes;
	struct SessionStopType* SessionStopReq;
	struct SessionStopResType* SessionStopRes;
	struct CertificateUpdateReqType* CertificateUpdateReq;
	struct CertificateUpdateResType* CertificateUpdateRes;
	struct CertificateInstallationReqType* CertificateInstallationReq;
	struct CertificateInstallationResType* CertificateInstallationRes;
	struct CableCheckReqType* CableCheckReq;
	struct CableCheckResType* CableCheckRes;
	struct PreChargeReqType* PreChargeReq;
	struct PreChargeResType* PreChargeRes;
	struct CurrentDemandReqType* CurrentDemandReq;
	struct CurrentDemandResType* CurrentDemandRes;
	struct WeldingDetectionReqType* WeldingDetectionReq;
	struct WeldingDetectionResType* WeldingDetectionRes;
	struct selection_BodyType isused;

};

struct AnonType_V2G_Message
{
	struct MessageHeaderType* Header;
	struct BodyType Body;


};

struct EXIDocumentType
{
	struct AnonType_V2G_Message V2G_Message;


};

/* init methods */
/*void init_EXIDocumentType(struct EXIDocumentType* type);
void init_ServiceDiscoveryResType(struct ServiceDiscoveryResType* type);
*/

#endif

#ifdef __cplusplus
}
#endif