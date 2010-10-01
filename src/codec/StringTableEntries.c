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
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.2
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
  "ChargingProfile",  "ContractID",  "EAmount",  "EVSEID",  "EVSEIMax",
  "EVSEMaxPhases",  "EVSEMaxPower",  "EVSEStatus",  "EVSEVoltage",  "EnergyProvider",
  "EoC",  "LineLockReq",  "LineLockReqType",  "LineLockRes",  "LineLockResType",
  "MeterInfo",  "MeteringAuthPubKey",  "MeteringReceiptReq",  "MeteringReceiptReqType",  "MeteringReceiptRes",
  "MeteringReceiptResType",  "MeteringStatusReq",  "MeteringStatusReqType",  "MeteringStatusRes",  "MeteringStatusResType",
  "PCurrent",  "PEVID",  "PEVMaxPhases",  "PEVMaxPower",  "PEVMaxVoltage",
  "PEVMinVoltage",  "PEVPubKey",  "PEVStatus",  "PaymentDetailsReq",  "PaymentDetailsReqType",
  "PaymentDetailsRes",  "PaymentDetailsResType",  "PowerDeliveryReq",  "PowerDeliveryReqType",  "PowerDeliveryRes",
  "PowerDeliveryResType",  "PowerDiscoveryReq",  "PowerDiscoveryReqType",  "PowerDiscoveryRes",  "PowerDiscoveryResType",
  "ReqLockStatus",  "ReqSwitchStatus",  "ResponseCode",  "ServiceDiscoveryReq",  "ServiceDiscoveryReqType",
  "ServiceDiscoveryRes",  "ServiceDiscoveryResType",  "ServiceList",  "ServicePaymentSelectionReq",  "ServicePaymentSelectionReqType",
  "ServicePaymentSelectionRes",  "ServicePaymentSelectionResType",  "ServiceScope",  "ServiceType",  "SessionSetupReq",
  "SessionSetupReqType",  "SessionSetupRes",  "SessionSetupResType",  "TCurrent",  "Tariff",
  "TariffTable"
};
/* localName entries for URI id = 5 */
const char * localNames5[] = {
  "ChargerStandby",  "ChargingProfileEntryMaxPower",  "ChargingProfileEntryStart",  "ChargingProfileType",  "ConnectorLocked",
  "Currency",  "EPrice",  "EVSEStandby",  "EVSEStatusType",  "Event",
  "EventList",  "EventListType",  "FatalError",  "FaultCode",  "FaultMsg",
  "FloatingValueType",  "MeterID",  "MeterInfoType",  "MeterPubKey",  "MeterReading",
  "MeterStatus",  "Multiplier",  "NotificationType",  "PEVStatusType",  "PowerSwitchClosed",
  "ProtocolVersion",  "RCD",  "Service",  "ServiceDescriptionType",  "ServiceID",
  "ServiceListType",  "ServiceName",  "ServiceScope",  "ServiceSessionID",  "ServiceType",
  "SessionID",  "SessionInformationType",  "ShutDownTime",  "TMeter",  "Tariff",
  "TariffDescrType",  "TariffDescription",  "TariffEntries",  "TariffEntriesType",  "TariffEntry",
  "TariffEntryType",  "TariffID",  "TariffPMax",  "TariffStart",  "TariffTableType",
  "Unit",  "Value",  "contractIDType",  "currencyType",  "energyProviderType",
  "eventEntryType",  "evseIDType",  "fatalErrorType",  "faultCodeType",  "lockStatusType",
  "maxPhasesType",  "meterIDType",  "meterStatusType",  "paymentOptionListType",  "paymentOptionType",
  "pevIDType",  "protocolVersionType",  "pubKeyType",  "rcdType",  "responseCode_LineLockType",
  "responseCode_MeteringReceiptType",  "responseCode_MeteringStatusType",  "responseCode_PaymentDetailsType",  "responseCode_PowerDeliveryType",  "responseCode_PowerDiscoveryType",
  "responseCode_ServiceDiscoveryType",  "responseCode_ServicePaymentSelectionType",  "responseCode_SessionSetupType",  "serviceDetailsType",  "serviceIDType",
  "serviceNameType",  "serviceScopeType",  "serviceTypeType",  "sessionIDType",  "standbyType",
  "switchStatusType",  "tariffDescriptionType",  "tariffIDType",  "tariffStartType",  "timeType",
  "unitMultiplierType",  "unitSymbolType"
};
/* localName entries for URI id = 6 */
const char * localNames6[] = {
  "Body",  "BodyBaseType",  "BodyElement",  "BodyType",  "Header",
  "HeaderType",  "Notification",  "SessionInformation",  "V2G_Message"
};
struct exiPartition localNamePartitions[7] = {
 { 0, localNames0 },
 { 4, localNames1 },
 { 2, localNames2 },
 { 46, localNames3 },
 { 66, localNames4 },
 { 92, localNames5 },
 { 9, localNames6 }
};
const char * uris[] = {
  "",  "http://www.w3.org/XML/1998/namespace",  "http://www.w3.org/2001/XMLSchema-instance",  "http://www.w3.org/2001/XMLSchema",  "urn:iso:15118:2:2010:MsgBody",  "urn:iso:15118:2:2010:MsgDataTypes",  "urn:iso:15118:2:2010:MsgDef"
};
struct exiStringTable stringTable = { 7, uris, localNamePartitions };




#endif

