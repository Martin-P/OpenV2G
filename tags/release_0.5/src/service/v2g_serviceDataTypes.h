
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
 * @version 0.5
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
	ParsingError_faultCodeType, 
	V2GProtocolVersionNotSupported_faultCodeType, 
	NoTLSRootCertificatAvailable_faultCodeType, 
	UnknownError_faultCodeType

}; 

enum responseCodeType
{
	OK_responseCodeType, 
	FAILED_UnknownError_responseCodeType, 
	OK_NewSessionEstablished_responseCodeType, 
	OK_OldSessionJoined_responseCodeType, 
	FAILED_UnknownSession_responseCodeType, 
	FAILED_SessionEstablishmentError_responseCodeType, 
	FAILED_NoServicesOfThisType_responseCodeType, 
	FAILED_NoServicesInThisScope_responseCodeType, 
	FAILED_NoServicesOfThisTypeScope_responseCodeType, 
	FAILED_NoServicesFound_responseCodeType, 
	FAILED_ServiceSelectionInvalid_responseCodeType, 
	FAILED_PaymentSelectionInvalid_responseCodeType, 
	FAILED_PaymentDetailsInvalid_responseCodeType, 
	OK_CertificateExpiresSoon_responseCodeType, 
	FAILED_CertificateExpired_responseCodeType, 
	FAILED_CertificateRevoked_responseCodeType, 
	FAILED_NoRootCertificate_responseCodeType, 
	FAILED_CertificateCryptoError_responseCodeType, 
	FAILED_SignatureError_responseCodeType, 
	FAILED_NetworkError_responseCodeType, 
	FAILED_ServerNotFoundError_responseCodeType, 
	FAILED_TimeOut_responseCodeType, 
	FAILED_NoCertificateAvailable_responseCodeType, 
	FAILED_ContractCanceled_responseCodeType, 
	FAILED_BatteryNotCompatible_responseCodeType, 
	FAILED_LineLockNotApplied_responseCodeType, 
	FAILED_PowerDeliveryNotApplied_responseCodeType, 
	FAILED_TariffSelectionInvalid_responseCodeType, 
	FAILED_ChargingProfileInvalid_responseCodeType, 
	FAILED_EVSEPresentVoltageToLow_responseCodeType, 
	FAILED_NotReady_responseCodeType, 
	FAILED_PrepaidLimitsExceeded_responseCodeType, 
	FAILED_ChargingSystemIncompatibility_responseCodeType, 
	FAILED_EVSE_Malfunction_responseCodeType, 
	NoData_responseCodeType

}; 

enum serviceCategoryType
{
	PEVRechargeCharge_serviceCategoryType, 
	RemoteCustomerSupportRCS_serviceCategoryType, 
	Internet_serviceCategoryType, 
	ContractCertificateUpdate_serviceCategoryType, 
	ContractCertificateInstalation_serviceCategoryType, 
	OtherCustom_serviceCategoryType

}; 

enum paymentOptionType
{
	Contract_paymentOptionType, 
	ExternalPayment_paymentOptionType

}; 

enum EVSESupportedEnergyTransferType
{
	AC_single_phase_core_EVSESupportedEnergyTransferType, 
	AC_three_phase_core_EVSESupportedEnergyTransferType, 
	DC_core_EVSESupportedEnergyTransferType, 
	DC_extended_EVSESupportedEnergyTransferType, 
	DC_combo_core_EVSESupportedEnergyTransferType, 
	DC_dual_EVSESupportedEnergyTransferType, 
	AC_core_DC_extended_EVSESupportedEnergyTransferType, 
	AC_single_DC_core_EVSESupportedEnergyTransferType, 
	AC_single_phase_three_phase_core_DC_extended_EVSESupportedEnergyTransferType, 
	Reserved_9_EVSESupportedEnergyTransferType, 
	Reserved_A_EVSESupportedEnergyTransferType, 
	Reserved_B_EVSESupportedEnergyTransferType, 
	Reserved_C_EVSESupportedEnergyTransferType, 
	Reserved_D_EVSESupportedEnergyTransferType, 
	Reserved_E_EVSESupportedEnergyTransferType, 
	Undetermined_EVSESupportedEnergyTransferType

}; 

enum PEVRequestedEnergyTransferType
{
	AC_single_phase_core_PEVRequestedEnergyTransferType, 
	AC_three_phase_core_PEVRequestedEnergyTransferType, 
	DC_core_PEVRequestedEnergyTransferType, 
	DC_extended_PEVRequestedEnergyTransferType, 
	DC_combo_core_PEVRequestedEnergyTransferType, 
	DC_unique_PEVRequestedEnergyTransferType, 
	DC_reverse_PEVRequestedEnergyTransferType, 
	AC_reverse_PEVRequestedEnergyTransferType, 
	Reserved_8_PEVRequestedEnergyTransferType, 
	Reserved_9_PEVRequestedEnergyTransferType, 
	Reserved_A_PEVRequestedEnergyTransferType, 
	Reserved_B_PEVRequestedEnergyTransferType, 
	Reserved_C_PEVRequestedEnergyTransferType, 
	Reserved_D_PEVRequestedEnergyTransferType, 
	Reserved_E_PEVRequestedEnergyTransferType, 
	Undetermined_PEVRequestedEnergyTransferType

}; 

enum unitSymbolType
{
	h_unitSymbolType, 
	m_unitSymbolType, 
	s_unitSymbolType, 
	A_unitSymbolType, 
	Ah_unitSymbolType, 
	V_unitSymbolType, 
	VA_unitSymbolType, 
	W_unitSymbolType, 
	W_s_unitSymbolType, 
	Wh_unitSymbolType

}; 

enum DC_PEVStatusCodeType
{
	PEVNotReady_DC_PEVStatusCodeType, 
	PEVEnergyTransfer_DC_PEVStatusCodeType, 
	FAILED_RESSTemperatureInhibit_DC_PEVStatusCodeType, 
	FAILED_PEVShiftPosition_DC_PEVStatusCodeType, 
	FAILED_ChargerConnectorLockFault_DC_PEVStatusCodeType, 
	PEVCabinConditioning_DC_PEVStatusCodeType, 
	PEVRESSConditioning_DC_PEVStatusCodeType, 
	FAILED_PEVRESSMalfunction_DC_PEVStatusCodeType, 
	FAILED_ChargingCurrentdifferential_DC_PEVStatusCodeType, 
	FAILED_ChargingVoltageOutOfRange_DC_PEVStatusCodeType, 
	Reserved_A_DC_PEVStatusCodeType, 
	Reserved_B_DC_PEVStatusCodeType, 
	Reserved_C_DC_PEVStatusCodeType, 
	FAILED_ChargingSystemIncompatibility_DC_PEVStatusCodeType, 
	NoData_DC_PEVStatusCodeType

}; 

enum currencyType
{
	AED_currencyType, 
	AFN_currencyType, 
	ALL_currencyType, 
	AMD_currencyType, 
	ANG_currencyType, 
	AOA_currencyType, 
	ARS_currencyType, 
	AUD_currencyType, 
	AWG_currencyType, 
	AZN_currencyType, 
	BAM_currencyType, 
	BBD_currencyType, 
	BDT_currencyType, 
	BGN_currencyType, 
	BHD_currencyType, 
	BIF_currencyType, 
	BMD_currencyType, 
	BND_currencyType, 
	BOB_currencyType, 
	BRL_currencyType, 
	BSD_currencyType, 
	BTN_currencyType, 
	BWP_currencyType, 
	BYR_currencyType, 
	BZD_currencyType, 
	CAD_currencyType, 
	CDF_currencyType, 
	CHF_currencyType, 
	CLP_currencyType, 
	CNY_currencyType, 
	COP_currencyType, 
	CRC_currencyType, 
	CUP_currencyType, 
	CVE_currencyType, 
	CZK_currencyType, 
	DJF_currencyType, 
	DKK_currencyType, 
	DOP_currencyType, 
	DZD_currencyType, 
	EEK_currencyType, 
	EGP_currencyType, 
	ERN_currencyType, 
	ETB_currencyType, 
	EUR_currencyType, 
	FJD_currencyType, 
	FKP_currencyType, 
	GBP_currencyType, 
	GEL_currencyType, 
	GHS_currencyType, 
	GIP_currencyType, 
	GMD_currencyType, 
	GNF_currencyType, 
	GTQ_currencyType, 
	GYD_currencyType, 
	GWP_currencyType, 
	HKD_currencyType, 
	HNL_currencyType, 
	HRK_currencyType, 
	HTG_currencyType, 
	HUF_currencyType, 
	IDR_currencyType, 
	ILS_currencyType, 
	INR_currencyType, 
	IQD_currencyType, 
	IRR_currencyType, 
	ISK_currencyType, 
	JMD_currencyType, 
	JOD_currencyType, 
	JPY_currencyType, 
	KES_currencyType, 
	KGS_currencyType, 
	KHR_currencyType, 
	KMF_currencyType, 
	KPW_currencyType, 
	KRW_currencyType, 
	KWD_currencyType, 
	KYD_currencyType, 
	KZT_currencyType, 
	LAK_currencyType, 
	LBP_currencyType, 
	LKR_currencyType, 
	LRD_currencyType, 
	LSL_currencyType, 
	LTL_currencyType, 
	LVL_currencyType, 
	LYD_currencyType, 
	MAD_currencyType, 
	MDL_currencyType, 
	MGA_currencyType, 
	MKD_currencyType, 
	MMK_currencyType, 
	MNT_currencyType, 
	MOP_currencyType, 
	MRO_currencyType, 
	MUR_currencyType, 
	MVR_currencyType, 
	MWK_currencyType, 
	MXN_currencyType, 
	MYR_currencyType, 
	MZN_currencyType, 
	NAD_currencyType, 
	NGN_currencyType, 
	NIO_currencyType, 
	NOK_currencyType, 
	NPR_currencyType, 
	NZD_currencyType, 
	OMR_currencyType, 
	PAB_currencyType, 
	PEN_currencyType, 
	PGK_currencyType, 
	PHP_currencyType, 
	PKR_currencyType, 
	PLN_currencyType, 
	PYG_currencyType, 
	QAR_currencyType, 
	RON_currencyType, 
	RSD_currencyType, 
	RUB_currencyType, 
	RWF_currencyType, 
	SAR_currencyType, 
	SBD_currencyType, 
	SCR_currencyType, 
	SDG_currencyType, 
	SEK_currencyType, 
	SGD_currencyType, 
	SHP_currencyType, 
	SKK_currencyType, 
	SLL_currencyType, 
	SOS_currencyType, 
	SRD_currencyType, 
	STD_currencyType, 
	SVC_currencyType, 
	SYP_currencyType, 
	SZL_currencyType, 
	THB_currencyType, 
	TJS_currencyType, 
	TMM_currencyType, 
	TND_currencyType, 
	TOP_currencyType, 
	TRY_currencyType, 
	TTD_currencyType, 
	TWD_currencyType, 
	TZS_currencyType, 
	UAH_currencyType, 
	UGX_currencyType, 
	USD_currencyType, 
	UYU_currencyType, 
	UZS_currencyType, 
	VEF_currencyType, 
	VND_currencyType, 
	VUV_currencyType, 
	WST_currencyType, 
	XAF_currencyType, 
	XAG_currencyType, 
	XAU_currencyType, 
	XCD_currencyType, 
	XDR_currencyType, 
	XOF_currencyType, 
	XPD_currencyType, 
	XPF_currencyType, 
	XPT_currencyType, 
	XXX_currencyType, 
	YER_currencyType, 
	ZAR_currencyType, 
	ZMK_currencyType, 
	ZWR_currencyType

}; 

enum tariffDescriptionType
{
	Standard_charge_tariffDescriptionType, 
	Fast_charge_tariffDescriptionType, 
	Green_charge_tariffDescriptionType, 
	Grid_friendly_charge_tariffDescriptionType, 
	Freely_parameterisable_charge_tariffDescriptionType, 
	Charge_under_reserve_tariffDescriptionType

}; 

enum DC_EVSEStatusCodeType
{
	EVSE_Shutdown_DC_EVSEStatusCodeType, 
	UtilityInterruptEvent_DC_EVSEStatusCodeType, 
	IsolationMonitoringInternal_DC_EVSEStatusCodeType, 
	IsolationMonitoringActive_DC_EVSEStatusCodeType, 
	EVSE_EmergencyShutdown_DC_EVSEStatusCodeType, 
	Reserved_8_DC_EVSEStatusCodeType, 
	Reserved_9_DC_EVSEStatusCodeType, 
	Reserved_A_DC_EVSEStatusCodeType, 
	Reserved_B_DC_EVSEStatusCodeType, 
	Reserved_C_DC_EVSEStatusCodeType

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

struct NotificationType
{
	enum faultCodeType FaultCode;
	struct faultMsgType FaultMsg;
	struct selection_NotificationType isused;

};

struct selection_MessageHeaderType
{
	unsigned int Notification:1;
	unsigned int Security:1;


};

struct arraylen_service_string
{
	size_t data;


};

struct service_string
{
	uint32_t data[128];
	struct arraylen_service_string arraylen;

};

struct CanonicalizationMethodType
{
	struct service_string attr_Algorithm;


};

struct SignatureMethodType
{
	struct service_string attr_Algorithm;


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
	struct DigestMethodType DigestMethod;
	struct DigestValueType DigestValue;
	struct service_string attr_URI;



};


struct SignedInfoType
{
	struct CanonicalizationMethodType CanonicalizationMethod;
	struct SignatureMethodType SignatureMethod;
	struct ReferenceType Reference;

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
	struct X509DataType X509Data;
	struct service_string attr_Id;


};

struct selection_SignatureType
{
	unsigned int KeyInfo:1;


};

struct SignatureType
{
	struct SignedInfoType SignedInfo;
	struct SignatureValueType SignatureValue;
	struct KeyInfoType KeyInfo;
	struct service_string attr_Id;
	struct selection_SignatureType isused;

};

struct selection_SecurityType
{
	unsigned int Signature:1;


};

struct SecurityType
{
	struct SignatureType* Signature;
	struct selection_SecurityType isused;

};

struct MessageHeaderType
{
	struct SessionInformationType SessionInformation;
	struct NotificationType Notification;
	struct SecurityType Security;
	struct selection_MessageHeaderType isused;

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

struct SessionSetupReqType
{
	struct pevIDType PEVID;
	struct selection_SessionSetupReqType isused;

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
	unsigned int MeteringStatusReq:1;
	unsigned int MeteringStatusRes:1;
	unsigned int MeteringReceiptReq:1;
	unsigned int MeteringReceiptRes:1;
	unsigned int CertificateUpdateReq:1;
	unsigned int CertificateUpdateRes:1;
	unsigned int CertificateInstallationReq:1;
	unsigned int CertificateInstallationRes:1;
	unsigned int LineLockReq:1;
	unsigned int LineLockRes:1;
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

struct SessionSetupResType
{
	enum responseCodeType ResponseCode;
	struct evseIDType EVSEID;
	int32_t TCurrent;


};

struct arraylen_serviceScopeType
{
	size_t data;


};

struct serviceScopeType
{
	uint32_t data[64];
	struct arraylen_serviceScopeType arraylen;

};

struct selection_ServiceDiscoveryReqType
{
	unsigned int ServiceScope:1;
	unsigned int ServiceType:1;


};

struct ServiceDiscoveryReqType
{
	struct serviceScopeType ServiceScope;
	enum serviceCategoryType ServiceType;
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
	uint32_t data[32];
	struct arraylen_serviceNameType arraylen;

};

struct selection_ServiceTagType
{
	unsigned int ServiceName:1;
	unsigned int ServiceCategory:1;
	unsigned int ServiceScope:1;


};

struct ServiceTagType
{
	struct serviceIDType ServiceID;
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

struct arraylen_ServiceTagListType
{
	size_t Service;


};

struct ServiceTagListType
{
	struct ServiceTagType Service[32];
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
	struct serviceIDType ServiceID;


};

struct selection_ServiceDetailResType
{
	unsigned int ServiceCharge:1;
	unsigned int ServiceCertificate:1;
	unsigned int ServiceCustom:1;
	unsigned int ServiceRCS:1;
	unsigned int ServiceInternet:1;


};

struct ServiceCertificateType
{
	struct ServiceTagType ServiceTag;
	int FreeService;
	int CertificateInstall;
	int CertificateUpdate;


};

struct ServiceDetailsType
{

 
	int NO_MEMBER:1;
	
};

struct ServiceCustomType
{
	struct ServiceTagType ServiceTag;
	int FreeService;
	struct ServiceDetailsType ServiceDetails;


};

struct ServiceRCSType
{
	struct ServiceTagType ServiceTag;
	int FreeService;
	struct ServiceDetailsType ServiceDetails;


};

struct ServiceInternetType
{
	struct ServiceTagType ServiceTag;
	int FreeService;
	struct ServiceDetailsType ServiceDetails;


};

struct ServiceDetailResType
{
	enum responseCodeType ResponseCode;
	struct ServiceTagType ServiceTag;
	struct PaymentOptionsType PaymentOptions;
	struct ServiceChargeType* ServiceCharge;
	struct ServiceCertificateType* ServiceCertificate;
	struct ServiceCustomType* ServiceCustom;
	struct ServiceRCSType* ServiceRCS;
	struct ServiceInternetType* ServiceInternet;
	struct selection_ServiceDetailResType isused;

};

struct ServicePaymentSelectionReqType
{
	enum paymentOptionType SelectedPaymentOption;
	struct ServiceTagListType ServiceList;


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
	uint32_t data[64];
	struct arraylen_contractIDType arraylen;

};

struct arraylen_certificateType
{
	size_t data;


};

struct certificateType
{
	uint8_t data[128];
	struct arraylen_certificateType arraylen;

};

struct arraylen_SubCertificatesType
{
	size_t Certificate;


};

struct SubCertificatesType
{
	struct certificateType Certificate[5];
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
	uint32_t data[128];
	struct arraylen_genChallengeType arraylen;

};

struct PaymentDetailsResType
{
	enum responseCodeType ResponseCode;
	struct genChallengeType GenChallenge;
	int32_t TCurrent;


};

struct ContractAuthenticationReqType
{
	struct genChallengeType GenChallenge;


};

struct ContractAuthenticationResType
{
	enum responseCodeType ResponseCode;


};

struct AC_PEVStatusType
{
	int ConnectorLocked;
	int PEVStandby;


};

struct FloatingValueType
{
	int8_t Multiplier;
	enum unitSymbolType Unit;
	int16_t Value;


};

struct AC_PEVChargeParameterType
{
	struct AC_PEVStatusType AC_PEVStatus;
	int32_t EoC;
	struct FloatingValueType EAmount;
	struct FloatingValueType PEVMaxPower;
	int8_t PEVMaxPhases;
	struct FloatingValueType PEVMaxVoltage;
	struct FloatingValueType PEVMinVoltage;
	struct FloatingValueType PEVMaxCurrent;
	struct FloatingValueType PEVMinCurrent;


};

struct selection_ChargeParameterDiscoveryReqType
{
	unsigned int AC_PEVChargeParameter:1;
	unsigned int DC_PEVChargeParameter:1;


};

struct DC_PEVStatusType
{
	int PEVStandby;
	int ConnectorLocked;
	int PEVReady;
	enum DC_PEVStatusCodeType PEVStatusCode;
	int8_t PEVRESSSOC;


};

struct selection_DC_PEVChargeParameterType
{
	unsigned int PEVMaximumPowerLimit:1;
	unsigned int PEVEnergyCapacity:1;
	unsigned int PEVEnergyRequest:1;
	unsigned int FullSOC:1;
	unsigned int BulkSOC:1;


};

struct DC_PEVChargeParameterType
{
	struct DC_PEVStatusType DC_PEVStatus;
	struct FloatingValueType PEVMaximumCurrentLimit;
	struct FloatingValueType PEVMaximumPowerLimit;
	struct FloatingValueType PEVMaximumVoltageLimit;
	struct FloatingValueType PEVEnergyCapacity;
	struct FloatingValueType PEVEnergyRequest;
	int8_t FullSOC;
	int8_t BulkSOC;
	int8_t PEVProtocolVersion;
	struct selection_DC_PEVChargeParameterType isused;

};

struct ChargeParameterDiscoveryReqType
{
	enum PEVRequestedEnergyTransferType PEVRequestedEnergyTransferType;
	struct AC_PEVChargeParameterType* AC_PEVChargeParameter;
	struct DC_PEVChargeParameterType* DC_PEVChargeParameter;
	struct selection_ChargeParameterDiscoveryReqType isused;

};

struct arraylen_energyProviderType
{
	size_t data;


};

struct energyProviderType
{
	uint32_t data[64];
	struct arraylen_energyProviderType arraylen;

};

struct selection_ChargeParameterDiscoveryResType
{
	unsigned int EnergyProvider:1;
	unsigned int TariffTable:1;
	unsigned int AC_EVSEChargeParameter:1;
	unsigned int DC_EVSEChargeParameter:1;


};

struct selection_TariffDescrType
{
	unsigned int TariffDescription:1;


};

struct arraylen_ePriceType
{
	size_t data;


};

struct ePriceType
{
	uint32_t data[128];
	struct arraylen_ePriceType arraylen;

};

struct selection_TariffEntryType
{
	unsigned int EPrice:1;


};

struct TariffEntryType
{
	uint32_t TariffStart;
	int16_t TariffPMax;
	struct ePriceType EPrice;
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
	int16_t TariffID;
	enum tariffDescriptionType TariffDescription;
	struct TariffEntriesType TariffEntries;
	struct selection_TariffDescrType isused;

};

struct arraylen_TariffTableType
{
	size_t Tariff;


};

struct TariffTableType
{
	enum currencyType Currency;
	struct TariffDescrType Tariff[6];
	enum unitSymbolType EPriceUnit;
	int8_t EPriceMultiplier;
	struct arraylen_TariffTableType arraylen;

};

struct AC_EVSEStatusType
{
	int EVSEStandby;
	int ConnectorLocked;
	int PowerSwitchClosed;
	int RCD;
	int32_t ShutDownTime;
	int StopCharging;


};

struct AC_EVSEChargeParameterType
{
	struct AC_EVSEStatusType AC_EVSEStatus;
	struct FloatingValueType EVSEMaxVoltage;
	struct FloatingValueType EVSEMinVoltage;
	struct FloatingValueType EVSEMaxCurrent;
	struct FloatingValueType EVSEMinCurrent;
	int8_t EVSEMaxPhases;


};

struct DC_EVSEStatusType
{
	int EVSEStandby;
	enum DC_EVSEStatusCodeType EVSEStatusCode;


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
	struct FloatingValueType EVSEMaximumCurrentLimit;
	struct FloatingValueType EVSEMaximumPowerLimit;
	struct FloatingValueType EVSEMaximumVoltageLimit;
	struct FloatingValueType EVSEMinimumCurrentLimit;
	struct FloatingValueType EVSEMinimumVoltageLimit;
	struct FloatingValueType EVSECurrentRegulationTolerance;
	struct FloatingValueType EVSEPeakCurrentRipple;
	struct FloatingValueType EVSEEnergyToBeDelivered;
	int8_t EVSEProtocolVersion;
	struct selection_DC_EVSEChargeParameterType isused;

};

struct ChargeParameterDiscoveryResType
{
	enum responseCodeType ResponseCode;
	struct energyProviderType EnergyProvider;
	struct TariffTableType TariffTable;
	struct AC_EVSEChargeParameterType* AC_EVSEChargeParameter;
	struct DC_EVSEChargeParameterType* DC_EVSEChargeParameter;
	struct selection_ChargeParameterDiscoveryResType isused;

};

struct selection_PowerDeliveryReqType
{
	unsigned int Tariff:1;
	unsigned int ChargingProfile:1;
	unsigned int AC_PEVPowerDeliveryParameter:1;
	unsigned int DC_PEVPowerDeliveryParameter:1;


};

struct ProfileEntryType
{
	int32_t ChargingProfileEntryStart;
	int16_t ChargingProfileEntryMaxPower;


};

struct arraylen_ChargingProfileType
{
	size_t ProfileEntry;


};

struct ChargingProfileType
{
	struct ProfileEntryType ProfileEntry[128];
	struct arraylen_ChargingProfileType arraylen;

};

struct AC_PEVPowerDeliveryParameterType
{
	struct AC_PEVStatusType AC_PEVStatus;


};

struct selection_DC_PEVPowerDeliveryParameterType
{
	unsigned int BulkChargingComplete:1;


};

struct DC_PEVPowerDeliveryParameterType
{
	struct DC_PEVStatusType DC_PEVStatus;
	int BulkChargingComplete;
	int ChargingComplete;
	struct selection_DC_PEVPowerDeliveryParameterType isused;

};

struct PowerDeliveryReqType
{
	int16_t Tariff;
	struct ChargingProfileType ChargingProfile;
	int ReqSwitchStatus;
	struct AC_PEVPowerDeliveryParameterType* AC_PEVPowerDeliveryParameter;
	struct DC_PEVPowerDeliveryParameterType* DC_PEVPowerDeliveryParameter;
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

struct selection_MeteringStatusReqType
{
	unsigned int AC_PEVStatus:1;
	unsigned int DC_PEVStatus:1;


};

struct MeteringStatusReqType
{
	struct AC_PEVStatusType* AC_PEVStatus;
	struct DC_PEVStatusType* DC_PEVStatus;
	struct selection_MeteringStatusReqType isused;

};

struct selection_MeteringStatusResType
{
	unsigned int PCurrent:1;
	unsigned int MeterInfo:1;
	unsigned int AC_EVSEStatus:1;
	unsigned int DC_EVSEStatus:1;


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
	unsigned int MeterPubKey:1;
	unsigned int MeterReading:1;
	unsigned int SigMeterReading:1;
	unsigned int MeterStatus:1;
	unsigned int TMeter:1;


};

struct arraylen_pubKeyType
{
	size_t data;


};

struct pubKeyType
{
	uint8_t data[128];
	struct arraylen_pubKeyType arraylen;

};

struct AnyType
{

 
	int NO_MEMBER:1;
	
};

struct MeterInfoType
{
	struct meterIDType MeterID;
	struct pubKeyType MeterPubKey;
	struct FloatingValueType MeterReading;
	struct AnyType SigMeterReading;
	int16_t MeterStatus;
	int32_t TMeter;
	struct selection_MeterInfoType isused;

};

struct MeteringStatusResType
{
	enum responseCodeType ResponseCode;
	struct evseIDType EVSEID;
	int32_t TCurrent;
	struct FloatingValueType EVSEMaxPower;
	struct FloatingValueType PCurrent;
	struct MeterInfoType MeterInfo;
	struct AC_EVSEStatusType* AC_EVSEStatus;
	struct DC_EVSEStatusType* DC_EVSEStatus;
	struct selection_MeteringStatusResType isused;

};

struct selection_MeteringReceiptReqType
{
	unsigned int PEVID:1;
	unsigned int TCurrent:1;
	unsigned int AC_PEVStatus:1;
	unsigned int DC_PEVStatus:1;


};

struct arraylen_meterSignatureType
{
	size_t data;


};

struct meterSignatureType
{
	uint8_t data[128];
	struct arraylen_meterSignatureType arraylen;

};

struct MeteringReceiptReqType
{
	struct pevIDType PEVID;
	struct evseIDType EVSEID;
	struct sessionIDType SessionID;
	struct MeterInfoType MeterInfo;
	int32_t TCurrent;
	int16_t Tariff;
	struct meterSignatureType ReceiptSignature;
	struct AC_PEVStatusType* AC_PEVStatus;
	struct DC_PEVStatusType* DC_PEVStatus;
	struct selection_MeteringReceiptReqType isused;

};

struct selection_MeteringReceiptResType
{
	unsigned int AC_EVSEStatus:1;
	unsigned int DC_EVSEStatus:1;


};

struct MeteringReceiptResType
{
	enum responseCodeType ResponseCode;
	struct AC_EVSEStatusType* AC_EVSEStatus;
	struct DC_EVSEStatusType* DC_EVSEStatus;
	struct selection_MeteringReceiptResType isused;

};

struct CertificateUpdateReqType
{
	struct CertificateChainType ContractSignatureCertChain;
	struct certificateType ContractEncryptionCert;
	struct contractIDType ContractID;


};

struct arraylen_signaturePrivateKeyType
{
	size_t data;


};

struct signaturePrivateKeyType
{
	uint8_t data[128];
	struct arraylen_signaturePrivateKeyType arraylen;

};

struct arraylen_encryptionPrivateKeyType
{
	size_t data;


};

struct encryptionPrivateKeyType
{
	uint8_t data[128];
	struct arraylen_encryptionPrivateKeyType arraylen;

};

struct CertificateUpdateResType
{
	enum responseCodeType ResponseCode;
	struct CertificateChainType ContractSignatureCertChain;
	struct signaturePrivateKeyType ContractSignaturePrivateKey;
	struct CertificateChainType ContractEncryptionCertChain;
	struct encryptionPrivateKeyType ContractEncryptionPrivateKey;
	struct contractIDType ContractID;
	int8_t RetryCounter;


};

struct CertificateInstallationReqType
{
	struct certificateType OEMProvisioningCert;


};

struct CertificateInstallationResType
{
	enum responseCodeType ResponseCode;
	struct CertificateChainType ContractSignatureCertChain;
	struct pubKeyType ContractSignaturePrivateKey;
	struct CertificateChainType ContractEncryptionCertChain;
	struct encryptionPrivateKeyType ContractEncryptionPrivateKey;
	struct contractIDType ContractID;


};

struct LineLockReqType
{
	struct AC_PEVStatusType AC_PEVStatus;
	int ReqLockStatus;


};

struct LineLockResType
{
	enum responseCodeType ResponseCode;
	struct AC_EVSEStatusType AC_EVSEStatus;


};

struct CableCheckReqType
{
	struct DC_PEVStatusType DC_PEVStatus;


};

struct CableCheckResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;


};

struct PreChargeReqType
{
	struct DC_PEVStatusType DC_PEVStatus;
	struct FloatingValueType PEVRESSVoltage;
	struct FloatingValueType PEVTargetVoltage;
	struct FloatingValueType PEVDemandCurrent;
	struct FloatingValueType VoltageDifferential;


};

struct PreChargeResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;


};

struct selection_CurrentDemandReqType
{
	unsigned int PEVMaximumVoltageLimit:1;
	unsigned int PEVMaximumCurrentLimit:1;
	unsigned int PEVMaximumPowerLimit:1;
	unsigned int BulkChargingComplete:1;
	unsigned int RemainingTimeToFullSoC:1;
	unsigned int RemainingTimeToBulkSoC:1;


};

struct CurrentDemandReqType
{
	struct DC_PEVStatusType DC_PEVStatus;
	struct FloatingValueType ChargeCurrentRequest;
	struct FloatingValueType PEVMaximumVoltageLimit;
	struct FloatingValueType PEVMaximumCurrentLimit;
	struct FloatingValueType PEVMaximumPowerLimit;
	int BulkChargingComplete;
	int ChargingComplete;
	struct FloatingValueType RemainingTimeToFullSoC;
	struct FloatingValueType RemainingTimeToBulkSoC;
	struct FloatingValueType PEVTargetVoltage;
	struct FloatingValueType CurrentDifferential;
	struct FloatingValueType VoltageDifferential;
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
	struct FloatingValueType EVSEPresentVoltage;
	struct FloatingValueType EVSEPresentCurrent;
	int EVSECurrentLimitAchieved;
	int EVSEVoltageLimitAchieved;
	int EVSEPowerLimitAchieved;
	struct FloatingValueType EVSEMaximumVoltageLimit;
	struct FloatingValueType EVSEMaximumCurrentLimit;
	struct FloatingValueType EVSEMaximumPowerLimit;
	struct selection_CurrentDemandResType isused;

};

struct WeldingDetectionReqType
{
	struct DC_PEVStatusType DC_PEVStatus;


};

struct WeldingDetectionResType
{
	enum responseCodeType ResponseCode;
	struct DC_EVSEStatusType DC_EVSEStatus;
	struct FloatingValueType EVSEPresentVoltage;


};

struct TerminateChargingReqType
{
	struct DC_PEVStatusType DC_PEVStatus;


};

struct TerminateChargingResType
{
	enum responseCodeType ResponseCode;
	struct FloatingValueType EVSEPresentVoltage;


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
	struct MeteringStatusReqType* MeteringStatusReq;
	struct MeteringStatusResType* MeteringStatusRes;
	struct MeteringReceiptReqType* MeteringReceiptReq;
	struct MeteringReceiptResType* MeteringReceiptRes;
	struct CertificateUpdateReqType* CertificateUpdateReq;
	struct CertificateUpdateResType* CertificateUpdateRes;
	struct CertificateInstallationReqType* CertificateInstallationReq;
	struct CertificateInstallationResType* CertificateInstallationRes;
	struct LineLockReqType* LineLockReq;
	struct LineLockResType* LineLockRes;
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
	struct MessageHeaderType* Header;
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