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
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 2012-01-31 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



#ifndef EXI__NAME_TABLE_ENTRIES_C
#define EXI__NAME_TABLE_ENTRIES_C

#include "NameTableEntries.h"



/* ==================================== */
/* String Table Population */

#if EXI_DEBUG == EXI_DEBUG_ON
/* localName entries for URI id = 0 */
char * localNames0[] = {
  "Algorithm",  "Encoding",  "Id",  "MimeType",  "Name",
  "Target",  "Type",  "URI",  "ValueType"
};
/* localName entries for URI id = 1 */
char * localNames1[] = {
  "base",  "id",  "lang",  "space"
};
/* localName entries for URI id = 2 */
char * localNames2[] = {
  "nil",  "type"
};
/* localName entries for URI id = 3 */
char * localNames3[] = {
  "ENTITIES",  "ENTITY",  "ID",  "IDREF",  "IDREFS",
  "NCName",  "NMTOKEN",  "NMTOKENS",  "NOTATION",  "Name",
  "QName",  "anySimpleType",  "anyType",  "anyURI",  "base64Binary",
  "boolean",  "byte",  "date",  "dateTime",  "decimal",
  "double",  "duration",  "float",  "gDay",  "gMonth",
  "gMonthDay",  "gYear",  "gYearMonth",  "hexBinary",  "int",
  "integer",  "language",  "long",  "negativeInteger",  "nonNegativeInteger",
  "nonPositiveInteger",  "normalizedString",  "positiveInteger",  "short",  "string",
  "time",  "token",  "unsignedByte",  "unsignedInt",  "unsignedLong",
  "unsignedShort"
};
/* localName entries for URI id = 4 */
char * localNames4[] = {
  "CanonicalizationMethod",  "CanonicalizationMethodType",  "CryptoBinary",  "DSAKeyValue",  "DSAKeyValueType",
  "DigestMethod",  "DigestMethodType",  "DigestValue",  "DigestValueType",  "Exponent",
  "G",  "HMACOutputLength",  "HMACOutputLengthType",  "J",  "KeyInfo",
  "KeyInfoType",  "KeyName",  "KeyValue",  "KeyValueType",  "Manifest",
  "ManifestType",  "MgmtData",  "Modulus",  "Object",  "ObjectType",
  "P",  "PGPData",  "PGPDataType",  "PGPKeyID",  "PGPKeyPacket",
  "PgenCounter",  "Q",  "RSAKeyValue",  "RSAKeyValueType",  "Reference",
  "ReferenceType",  "RetrievalMethod",  "RetrievalMethodType",  "SPKIData",  "SPKIDataType",
  "SPKISexp",  "Seed",  "Signature",  "SignatureMethod",  "SignatureMethodType",
  "SignatureProperties",  "SignaturePropertiesType",  "SignatureProperty",  "SignaturePropertyType",  "SignatureType",
  "SignatureValue",  "SignatureValueType",  "SignedInfo",  "SignedInfoType",  "Transform",
  "TransformType",  "Transforms",  "TransformsType",  "X509CRL",  "X509Certificate",
  "X509Data",  "X509DataType",  "X509IssuerName",  "X509IssuerSerial",  "X509IssuerSerialType",
  "X509SKI",  "X509SerialNumber",  "X509SubjectName",  "XPath",  "Y"

};
/* localName entries for URI id = 5 */
char * localNames5[] = {
  "AC_EVSEStatus",  "BulkChargingComplete",  "CableCheckReq",  "CableCheckReqType",  "CableCheckRes",
  "CableCheckResType",  "CertificateInstallationReq",  "CertificateInstallationReqType",  "CertificateInstallationRes",  "CertificateInstallationResType",
  "CertificateUpdateReq",  "CertificateUpdateReqType",  "CertificateUpdateRes",  "CertificateUpdateResType",  "ChargeParameterDiscoveryReq",
  "ChargeParameterDiscoveryReqType",  "ChargeParameterDiscoveryRes",  "ChargeParameterDiscoveryResType",  "ChargeService",  "ChargingComplete",
  "ChargingProfile",  "ChargingStatusReq",  "ChargingStatusReqType",  "ChargingStatusRes",  "ChargingStatusResType",
  "ContractAuthenticationReq",  "ContractAuthenticationReqType",  "ContractAuthenticationRes",  "ContractAuthenticationResType",  "ContractEncryptionEncryptedPrivateKey",
  "ContractID",  "ContractSignatureCertChain",  "ContractSignatureEncryptedPrivateKey",  "CurrentDemandReq",  "CurrentDemandReqType",
  "CurrentDemandRes",  "CurrentDemandResType",  "DC_EVSEStatus",  "DC_EVStatus",  "DHParams",
  "DateTimeNow",  "EVCCID",  "EVMaximumCurrentLimit",  "EVMaximumPowerLimit",  "EVMaximumVoltageLimit",
  "EVRequestedEnergyTransferType",  "EVSECurrentLimitAchieved",  "EVSEID",  "EVSEMaxCurrent",  "EVSEMaximumCurrentLimit",
  "EVSEMaximumPowerLimit",  "EVSEMaximumVoltageLimit",  "EVSEPowerLimitAchieved",  "EVSEPresentCurrent",  "EVSEPresentVoltage",
  "EVSEVoltageLimitAchieved",  "EVTargetCurrent",  "EVTargetVoltage",  "GenChallenge",  "ListOfRootCertificateIDs",
  "MeterInfo",  "MeteringReceiptReq",  "MeteringReceiptReqType",  "MeteringReceiptRes",  "MeteringReceiptResType",
  "OEMProvisioningCert",  "PaymentDetailsReq",  "PaymentDetailsReqType",  "PaymentDetailsRes",  "PaymentDetailsResType",
  "PaymentOptions",  "PowerDeliveryReq",  "PowerDeliveryReqType",  "PowerDeliveryRes",  "PowerDeliveryResType",
  "PreChargeReq",  "PreChargeReqType",  "PreChargeRes",  "PreChargeResType",  "ReadyToChargeState",
  "ReceiptRequired",  "RemainingTimeToBulkSoC",  "RemainingTimeToFullSoC",  "ResponseCode",  "RetryCounter",
  "SAScheduleTupleID",  "SelectedPaymentOption",  "SelectedServiceList",  "ServiceCategory",  "ServiceDetailReq",
  "ServiceDetailReqType",  "ServiceDetailRes",  "ServiceDetailResType",  "ServiceDiscoveryReq",  "ServiceDiscoveryReqType",
  "ServiceDiscoveryRes",  "ServiceDiscoveryResType",  "ServiceID",  "ServiceList",  "ServiceParameterList",
  "ServicePaymentSelectionReq",  "ServicePaymentSelectionReqType",  "ServicePaymentSelectionRes",  "ServicePaymentSelectionResType",  "ServiceScope",
  "SessionID",  "SessionSetupReq",  "SessionSetupReqType",  "SessionSetupRes",  "SessionSetupResType",
  "SessionStopReq",  "SessionStopRes",  "SessionStopResType",  "SessionStopType",  "WeldingDetectionReq",
  "WeldingDetectionReqType",  "WeldingDetectionRes",  "WeldingDetectionResType"
};
/* localName entries for URI id = 6 */
char * localNames6[] = {
  "AC_EVChargeParameter",  "AC_EVChargeParameterType",  "AC_EVSEChargeParameter",  "AC_EVSEChargeParameterType",  "AC_EVSEStatus",
  "AC_EVSEStatusType",  "BulkChargingComplete",  "BulkSOC",  "Certificate",  "CertificateChainType",
  "ChargingComplete",  "ChargingProfileEntryMaxPower",  "ChargingProfileEntryStart",  "ChargingProfileType",  "ConsumptionCost",
  "ConsumptionCostType",  "Cost",  "CostType",  "DC_EVChargeParameter",  "DC_EVChargeParameterType",
  "DC_EVErrorCodeType",  "DC_EVPowerDeliveryParameter",  "DC_EVPowerDeliveryParameterType",  "DC_EVSEChargeParameter",  "DC_EVSEChargeParameterType",
  "DC_EVSEStatus",  "DC_EVSEStatusCodeType",  "DC_EVSEStatusType",  "DC_EVStatus",  "DC_EVStatusType",
  "DepartureTime",  "EAmount",  "EPriceLevel",  "EVCabinConditioning",  "EVChargeParameter",
  "EVChargeParameterType",  "EVEnergyCapacity",  "EVEnergyRequest",  "EVErrorCode",  "EVMaxCurrent",
  "EVMaxVoltage",  "EVMaximumCurrentLimit",  "EVMaximumPowerLimit",  "EVMaximumVoltageLimit",  "EVMinCurrent",
  "EVPowerDeliveryParameter",  "EVPowerDeliveryParameterType",  "EVRESSConditioning",  "EVRESSSOC",  "EVReady",
  "EVRequestedEnergyTransferType",  "EVSEChargeParameter",  "EVSEChargeParameterType",  "EVSECurrentRegulationTolerance",  "EVSEEnergyToBeDelivered",
  "EVSEIsolationStatus",  "EVSEMaxCurrent",  "EVSEMaxVoltage",  "EVSEMaximumCurrentLimit",  "EVSEMaximumPowerLimit",
  "EVSEMaximumVoltageLimit",  "EVSEMinCurrent",  "EVSEMinimumCurrentLimit",  "EVSEMinimumVoltageLimit",  "EVSEPeakCurrentRipple",
  "EVSEStatus",  "EVSEStatusCode",  "EVSEStatusType",  "EVSESupportedEnergyTransferType",  "EVStatus",
  "EVStatusType",  "EnergyTransferType",  "Entry",  "EntryType",  "FaultCode",
  "FaultMsg",  "FreeService",  "FullSOC",  "IntervalType",  "ListOfRootCertificateIDsType",
  "MeterID",  "MeterInfoType",  "MeterReading",  "MeterStatus",  "Multiplier",
  "NotificationType",  "NumEPriceLevels",  "PMax",  "PMaxSchedule",  "PMaxScheduleEntry",
  "PMaxScheduleEntryType",  "PMaxScheduleID",  "PMaxScheduleType",  "PMaxType",  "Parameter",
  "ParameterSet",  "ParameterSetID",  "ParameterSetType",  "ParameterType",  "PaymentOption",
  "PaymentOptionsType",  "PhysicalValueType",  "PowerSwitchClosed",  "ProfileEntry",  "ProfileEntryType",
  "RCD",  "RelativeTimeInterval",  "RelativeTimeIntervalType",  "RootCertificateID",  "SAIDType",
  "SAScheduleList",  "SAScheduleListType",  "SAScheduleTuple",  "SAScheduleTupleID",  "SAScheduleTupleType",
  "SASchedules",  "SASchedulesType",  "SalesTariff",  "SalesTariffDescription",  "SalesTariffEntry",
  "SalesTariffEntryType",  "SalesTariffID",  "SalesTariffType",  "SelectedService",  "SelectedServiceListType",
  "SelectedServiceType",  "Service",  "ServiceCategory",  "ServiceCharge",  "ServiceChargeType",
  "ServiceID",  "ServiceName",  "ServiceParameterListType",  "ServiceScope",  "ServiceTag",
  "ServiceTagListType",  "ServiceTagType",  "ServiceType",  "ShutDownTime",  "SigMeterReading",
  "StopCharging",  "SubCertificates",  "SubCertificatesType",  "TMeter",  "TimeInterval",
  "Unit",  "Value",  "amount",  "amountMultiplier",  "boolValue",
  "byteValue",  "certificateType",  "contractIDType",  "costKind",  "costKindType",
  "dHParamsType",  "duration",  "evccIDType",  "evseIDType",  "faultCodeType",
  "faultMsgType",  "genChallengeType",  "intValue",  "isolationLevelType",  "meterIDType",
  "meterStatusType",  "paymentOptionType",  "percentValueType",  "physicalValue",  "privateKeyType",
  "responseCodeType",  "rootCertificateIDType",  "serviceCategoryType",  "serviceIDType",  "serviceNameType",
  "serviceScopeType",  "sessionIDType",  "shortValue",  "sigMeterReadingType",  "start",
  "startValue",  "stringValue",  "tariffDescriptionType",  "unitMultiplierType",  "unitSymbolType",
  "valueType"
};
/* localName entries for URI id = 7 */
char * localNames7[] = {
  "Body",  "BodyBaseType",  "BodyElement",  "BodyType",  "Header",
  "V2G_Message"
};
/* localName entries for URI id = 8 */
char * localNames8[] = {
  "MessageHeaderType",  "Notification",  "SessionID"
};
char * uris[] = {
  "",  "http://www.w3.org/XML/1998/namespace",  "http://www.w3.org/2001/XMLSchema-instance",  "http://www.w3.org/2001/XMLSchema",  "http://www.w3.org/2000/09/xmldsig#",  "urn:iso:15118:2:2010:MsgBody",  "urn:iso:15118:2:2010:MsgDataTypes",  "urn:iso:15118:2:2010:MsgDef",  "urn:iso:15118:2:2010:MsgHeader"
};
#endif /*EXI_DEBUG*/

#if EXI_DEBUG == EXI_DEBUG_ON
struct exiNamePartition localNamePartitions[9] = {
 { 9, localNames0 },
 { 4, localNames1 },
 { 2, localNames2 },
 { 46, localNames3 },
 { 70, localNames4 },
 { 118, localNames5 },
 { 186, localNames6 },
 { 6, localNames7 },
 { 3, localNames8 }
};
#endif /*EXI_DEBUG*/

#if EXI_DEBUG == EXI_DEBUG_OFF
static struct exiNamePartition localNamePartitions[9] = {
 { 9 },
 { 4 },
 { 2 },
 { 46 },
 { 70 },
 { 118 },
 { 186 },
 { 6 },
 { 3 }
};
#endif /*EXI_DEBUG*/


#if EXI_DEBUG == EXI_DEBUG_ON
exi_name_table_prepopulated_t exiNameTablePrepopulated = { 9, uris, localNamePartitions };
#endif /*EXI_DEBUG*/
#if EXI_DEBUG == EXI_DEBUG_OFF
exi_name_table_prepopulated_t exiNameTablePrepopulated = { 9, localNamePartitions };
#endif /*EXI_DEBUG*/




#endif
