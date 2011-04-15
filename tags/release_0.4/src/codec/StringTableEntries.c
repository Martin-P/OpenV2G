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
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.4
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifndef STRING_TABLE_ENTRIES_C
#define STRING_TABLE_ENTRIES_C

#include "StringTableEntries.h"


/* ==================================== */
/* String Table Population */

/* localName entries for URI id = 0 */
const char * localNames0[] = {
 NULL 
};
/* localName entries for URI id = 1 */
const char * localNames1[] = {
  "base",  "id",  "lang",  "space"
};
/* localName entries for URI id = 2 */
const char * localNames2[] = {
  "nil",  "type"
};
/* localName entries for URI id = 3 */
const char * localNames3[] = {
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
const char * localNames4[] = {
  "CableCheckReq",  "CableCheckReqType",  "CableCheckRes",  "CableCheckResType",  "ChargeParameterDiscoveryReq",
  "ChargeParameterDiscoveryReqType",  "ChargeParameterDiscoveryRes",  "ChargeParameterDiscoveryResType",  "ChargingMode",  "ContractID",
  "CurrentDemandReq",  "CurrentDemandReqType",  "CurrentDemandRes",  "CurrentDemandResType",  "CurrentDifferential",
  "EAmount",  "EVSEID",  "EVSEMaxCurrent",  "EVSEMaxPhases",  "EVSEMaxPower",
  "EVSEMaxVoltage",  "EVSEMinCurrent",  "EVSEMinVoltage",  "EVSEPresentCurrent",  "EVSEPresentVoltage",
  "EVSEStatus",  "EnergyProvider",  "EoC",  "LineLockReq",  "LineLockReqType",
  "LineLockRes",  "LineLockResType",  "MeterInfo",  "MeteringReceiptReq",  "MeteringReceiptReqType",
  "MeteringReceiptRes",  "MeteringReceiptResType",  "MeteringStatusReq",  "MeteringStatusReqType",  "MeteringStatusRes",
  "MeteringStatusResType",  "PCurrent",  "PEVDemandCurrent",  "PEVID",  "PEVMaxCurrent",
  "PEVMaxPhases",  "PEVMaxPower",  "PEVMaxVoltage",  "PEVMinCurrent",  "PEVMinVoltage",
  "PEVStatus",  "PEVTargetVoltage",  "PaymentDetailsReq",  "PaymentDetailsReqType",  "PaymentDetailsRes",
  "PaymentDetailsResType",  "PowerDeliveryReq",  "PowerDeliveryReqType",  "PowerDeliveryRes",  "PowerDeliveryResType",
  "PreChargeReq",  "PreChargeReqType",  "PreChargeRes",  "PreChargeResType",  "ReqLockStatus",
  "ReqSwitchStatus",  "ResponseCode",  "ServiceDiscoveryReq",  "ServiceDiscoveryReqType",  "ServiceDiscoveryRes",
  "ServiceDiscoveryResType",  "ServiceList",  "ServicePaymentSelectionReq",  "ServicePaymentSelectionReqType",  "ServicePaymentSelectionRes",
  "ServicePaymentSelectionResType",  "ServiceScope",  "ServiceType",  "SessionSetupReq",  "SessionSetupReqType",
  "SessionSetupRes",  "SessionSetupResType",  "TCurrent",  "Tariff",  "TariffTable",
  "TerminateChargingReq",  "TerminateChargingReqType",  "TerminateChargingRes",  "TerminateChargingResType",  "VoltageDifferential",
  "WeldingDetectionReq",  "WeldingDetectionReqType",  "WeldingDetectionRes",  "WeldingDetectionResType"
};
/* localName entries for URI id = 5 */
const char * localNames5[] = {
  "ChargerStandby",  "ChargingProfileEntryMaxPower",  "ChargingProfileEntryStart",  "ChargingProfileType",  "ConnectorLocked",
  "Currency",  "EPrice",  "EVSEMalfunction",  "EVSEStandby",  "EVSEStatusType",
  "Event",  "EventList",  "EventListType",  "FatalError",  "FaultCode",
  "FaultMsg",  "FloatingValueType",  "MeterID",  "MeterInfoType",  "MeterReading",
  "MeterStatus",  "Multiplier",  "NotificationType",  "PEVStatusType",  "PowerSwitchClosed",
  "ProtocolVersion",  "RCD",  "ReadyToCharge",  "Service",  "ServiceDescriptionType",
  "ServiceID",  "ServiceListType",  "ServiceName",  "ServiceScope",  "ServiceSessionID",
  "ServiceType",  "SessionID",  "SessionInformationType",  "ShutDownTime",  "StopCharging",
  "TMeter",  "Tariff",  "TariffDescrType",  "TariffDescription",  "TariffEntries",
  "TariffEntriesType",  "TariffEntry",  "TariffEntryType",  "TariffID",  "TariffPMax",
  "TariffStart",  "TariffTableType",  "Unit",  "Value",  "chargingModeType",
  "contractIDType",  "currencyType",  "energyProviderType",  "eventEntryType",  "evseIDType",
  "fatalErrorType",  "faultCodeType",  "lockStatusType",  "maxPhasesType",  "meterIDType",
  "meterStatusType",  "paymentOptionListType",  "paymentOptionType",  "pevIDType",  "protocolVersionType",
  "pubKeyType",  "rcdType",  "responseCode_CableCheckType",  "responseCode_ChargeParameterDiscoveryType",  "responseCode_CurrentDemandType",
  "responseCode_LineLockType",  "responseCode_MeteringReceiptType",  "responseCode_MeteringStatusType",  "responseCode_PaymentDetailsType",  "responseCode_PowerDeliveryType",
  "responseCode_PreChargeType",  "responseCode_ServiceDiscoveryType",  "responseCode_ServicePaymentSelectionType",  "responseCode_SessionSetupType",  "responseCode_TerminateChargingType",
  "responseCode_WeldingDetectionType",  "serviceDetailsType",  "serviceIDType",  "serviceNameType",  "serviceScopeType",
  "serviceTypeType",  "sessionIDType",  "standbyType",  "switchStatusType",  "tariffDescriptionType",
  "tariffIDType",  "tariffStartType",  "timeType",  "unitMultiplierType",  "unitSymbolType"

};
/* localName entries for URI id = 6 */
const char * localNames6[] = {
  "Body",  "BodyBaseType",  "BodyElement",  "BodyType",  "Header",
  "V2G_Message"
};
/* localName entries for URI id = 7 */
const char * localNames7[] = {
  "HeaderType",  "Notification",  "SessionInformation"
};
struct exiPartition localNamePartitions[8] = {
 { 0, localNames0 },
 { 4, localNames1 },
 { 2, localNames2 },
 { 46, localNames3 },
 { 94, localNames4 },
 { 100, localNames5 },
 { 6, localNames6 },
 { 3, localNames7 }
};
const char * uris[] = {
  "",  "http://www.w3.org/XML/1998/namespace",  "http://www.w3.org/2001/XMLSchema-instance",  "http://www.w3.org/2001/XMLSchema",  "urn:iso:15118:2:2010:eval1.0:MsgBody",  "urn:iso:15118:2:2010:eval1.0:MsgDataTypes",  "urn:iso:15118:2:2010:eval1.0:MsgDef",  "urn:iso:15118:2:2010:eval1.0:MsgHeader"
};
struct exiStringTable stringTable = { 8, uris, localNamePartitions };




#endif

