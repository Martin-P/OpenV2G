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
 ********************************************************************/



#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceClientStubs.h"
#include "EXITypes.h"
#include "v2gtp.h"

#include <stdio.h>

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 100


static void printErrorMessage(struct EXIService* service);
static void printDCEVSEStatus(struct DC_EVSEStatusType* status);
static void printACEVSEStatus(struct AC_EVSEStatusType* status);
static void printASCIIString(uint32_t* string, uint32_t len);


static int ac_charging()
{


	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */

	/* define offset variable for transport header data */
	uint16_t transportHeaderOffset;


	/* service data structure for AC*/
	struct EXIService service;
	struct MessageHeaderType v2gHeader;
	struct SessionSetupReqType sessionSetup;
	struct SessionSetupResType resultSessionSetup;
	struct ServiceDiscoveryReqType serviceDiscovery;
	struct ServiceDiscoveryResType resultServiceDiscovery;
	struct ChargeParameterDiscoveryReqType powerDiscovery;
	struct ChargeParameterDiscoveryResType resultPowerDiscovery;
	struct LineLockReqType lineLock;
	struct LineLockResType resultLineLock;
	struct PowerDeliveryReqType powerDelivery;
	struct PowerDeliveryResType resultPowerDelivery;
	struct MeteringStatusReqType meteringStatus;
	struct MeteringStatusResType resultMeteringStatus;
	struct MeteringReceiptReqType meteringReceipt;
	struct MeteringReceiptResType resultMeteringReceipt;


	struct AC_PEVStatusType pevStatus;
	struct AC_EVSEStatusType evseStatus;
	struct AC_PEVChargeParameterType pevChargeParameter;
	struct AC_EVSEChargeParameterType evseChargeParameter;
	struct AC_PEVPowerDeliveryParameterType pevPowerDelivery;


	struct FloatingValueType float_type; /* test float type*/

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/* setup offset for DoIP header (otherwise set
	 * transportHeaderOffset=0 if no transfer protocol is used)*/
	transportHeaderOffset = V2GTP_HEADER_LENGTH;


	/*******************
	 * Init V2G Client *
	 *******************/

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, transportHeaderOffset);


	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionInformation.SessionID.data[0] = 0; /* sessionID is always '0' at the beginning (the response contains the valid sessionID)*/
	v2gHeader.SessionInformation.SessionID.arraylen.data = 1; /* no session id in the initial message -> array length = 0*/
	v2gHeader.SessionInformation.ProtocolVersion.data[0]='1'; /* assign protocol version number*/
	v2gHeader.SessionInformation.ProtocolVersion.arraylen.data=1; /* array string length =1 of protocol version */
	v2gHeader.SessionInformation.isused.ProtocolVersion = 1; /* important: optional elements have to be set used (=1) or not used (=0) */
	v2gHeader.SessionInformation.isused.ServiceSessionID = 0; /* service session is not used */
	v2gHeader.isused.Notification=0; /* no notification */
	v2gHeader.isused.Security=0; /* no security */

	/* setup sessionSetup parameter */
	sessionSetup.isused.PEVID=1; /*  PEVID is transported */
	sessionSetup.PEVID.arraylen.data=1;
	sessionSetup.PEVID.data[0]=10;


	printf("PEV: call EVSE sessionSetup\n");

	/*********************
	 * Call sessionSetup *
	 *********************/
	if(call_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\tHeader SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printf("\tTCurrent=%d\n",resultSessionSetup.TCurrent);
	}


	/*******************************************
	 * Setup data for serviceDiscovery *
	 *******************************************/

	serviceDiscovery.isused.ServiceType=1;
	serviceDiscovery.ServiceType = 	PEVRechargeCharge_serviceCategoryType;
	serviceDiscovery.isused.ServiceScope=0;


	printf("PEV: call EVSE serviceDiscovery\n");

	/*************************
	 * Call serviceDiscovery *
	 *************************/
	if(call_serviceDiscovery(&service,&v2gHeader, &serviceDiscovery,&resultServiceDiscovery))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\t Header SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\t ResponseCode=%d\n",resultServiceDiscovery.ResponseCode);
		printf("\t ServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceTag.ServiceID.data[0]);
		printf("\t PaymentOption=%d\n",	resultServiceDiscovery.PaymentOptions.PaymentOption[0]);
		printf("\t EnergyTransferType=%d\n",	resultServiceDiscovery.ChargeService.EnergyTransferType);
	}


	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	powerDiscovery.PEVRequestedEnergyTransferType = AC_three_phase_core_PEVRequestedEnergyTransferType;

	/* setup PEVStatus */
	pevStatus.ConnectorLocked = 1;
	pevStatus.PEVStandby = 1;

	pevChargeParameter.AC_PEVStatus = pevStatus;


	float_type.Multiplier = 0;
	float_type.Unit = W_unitSymbolType;
	float_type.Value = 100;

	pevChargeParameter.EAmount = float_type;

	pevChargeParameter.EoC = 89;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 200;

	pevChargeParameter.PEVMaxCurrent= float_type;

	pevChargeParameter.PEVMaxPhases= 3;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 300;

	pevChargeParameter.PEVMaxPower= float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 400;

	pevChargeParameter.PEVMaxVoltage=float_type;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 500;

	pevChargeParameter.PEVMinCurrent=float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 600;

	pevChargeParameter.PEVMinVoltage = float_type;

	powerDiscovery.AC_PEVChargeParameter = &pevChargeParameter;
	powerDiscovery.isused.AC_PEVChargeParameter = 1; /* we use here DC based charging parameters */
	powerDiscovery.isused.DC_PEVChargeParameter = 0;


	resultPowerDiscovery.AC_EVSEChargeParameter = &evseChargeParameter; /* we expect DC-based parameters from the evse*/

	/*********************************
	 * Call chargeParameterDiscovery *
	 *********************************/
	printf("\nPEV: call EVSE chargeParameterDiscovery\n");

	if(call_chargeParameterDiscovery(&service,&v2gHeader,&powerDiscovery,&resultPowerDiscovery))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("PEV: received response message from EVSE\n");
		printf("\t\t Header SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printACEVSEStatus(&(resultPowerDiscovery.AC_EVSEChargeParameter->AC_EVSEStatus));

		printf("\t EVSEMaxCurrent=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxCurrent.Value);
		printf("\t EVSEMaxPhases=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxPhases);
		printf("\t EVSEMaxVoltage=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxVoltage.Value);
		printf("\t EVSEMinimumCurrentLimit=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMinCurrent.Value);

		printf("\t EVSEMinVoltage=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMinVoltage.Value);

	}



	/*********************************
	 * Setup data for lineLock *
	 *********************************/

	lineLock.AC_PEVStatus = pevStatus;
	lineLock.ReqLockStatus = 1;

	/***********************
	 * Call lineLock *
	 ***********************/
	printf("\nPEV: call EVSE lineLock\n");

	if(call_lineLock(&service,&v2gHeader,&lineLock,&resultLineLock))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultLineLock.ResponseCode);
		printACEVSEStatus(&resultLineLock.AC_EVSEStatus);

	}



	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	powerDelivery.ReqSwitchStatus = 1;
	powerDelivery.isused.Tariff = 0;
	powerDelivery.isused.ChargingProfile= 0;

	powerDelivery.isused.DC_PEVPowerDeliveryParameter=0;
	powerDelivery.isused.AC_PEVPowerDeliveryParameter=1;
	pevPowerDelivery.AC_PEVStatus = pevStatus;


	powerDelivery.AC_PEVPowerDeliveryParameter = &pevPowerDelivery;

	resultPowerDelivery.AC_EVSEStatus = &evseStatus; /* we expect the AC-based EVSE status */

	/***********************
	 * Call powerDelivery *
	 ***********************/
	printf("\nPEV: call EVSE powerDelivery\n");

	if(call_powerDelivery(&service,&v2gHeader,&powerDelivery,&resultPowerDelivery))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPowerDelivery.ResponseCode);
		printACEVSEStatus(&evseStatus);
	}





	/********************
	 * Call meterStatus *
	 ********************/

	meteringStatus.AC_PEVStatus = &pevStatus;
	meteringStatus.isused.AC_PEVStatus=1;
	meteringStatus.isused.DC_PEVStatus=0;

	resultMeteringStatus.AC_EVSEStatus = &evseStatus;

	printf("\nPEV: call EVSE meterStatus\n");

	if(call_meteringStatus(&service,&v2gHeader,&meteringStatus,&resultMeteringStatus))
	{
		printErrorMessage(&service);
	}
	else
	{

		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printACEVSEStatus(resultMeteringStatus.AC_EVSEStatus);
		printf("\tEVSEID=%d\n",resultMeteringStatus.EVSEID.data[0]);
		printf("\tEVSEMaxPower=%d\n",resultMeteringStatus.EVSEMaxPower.Value);
		printf("\tisused.MeterInfo=%d\n",		resultMeteringStatus.isused.MeterInfo);
		printf("\t\tMeterInfo.MeterID=%d\n",		resultMeteringStatus.MeterInfo.MeterID.data[0]);
		printf("\t\tMeterInfo.MeterReading.Value=%d\n",		resultMeteringStatus.MeterInfo.MeterReading.Value);
		printf("\t\tMeterInfo.MeterStatus=%d\n",		resultMeteringStatus.MeterInfo.MeterStatus);
	}



	/*********************************
	 * Setup data for meteringReceipt *
	 *********************************/

	meteringReceipt.PEVID.arraylen.data=1;
	meteringReceipt.PEVID.data[0]=10;
	meteringReceipt.isused.PEVID=1;

	meteringReceipt.AC_PEVStatus = &pevStatus;
	meteringReceipt.isused.AC_PEVStatus =1;
	meteringReceipt.isused.DC_PEVStatus =0;
	meteringReceipt.TCurrent = 12345;
	meteringReceipt.isused.TCurrent = 1;
	meteringReceipt.Tariff = 12;
	meteringReceipt.MeterInfo.MeterStatus = 2;
	meteringReceipt.MeterInfo.isused.MeterStatus = 1;


	meteringReceipt.MeterInfo.MeterID.arraylen.data=1;
	meteringReceipt.MeterInfo.MeterID.data[0]=3;
	meteringReceipt.MeterInfo.isused.MeterID = 1;

	meteringReceipt.MeterInfo.MeterReading.Multiplier = 0;
	meteringReceipt.MeterInfo.MeterReading.Unit = A_unitSymbolType;
	meteringReceipt.MeterInfo.MeterReading.Value = 500;
	meteringReceipt.MeterInfo.isused.MeterReading = 1;

	meteringReceipt.MeterInfo.TMeter =123456789;
	meteringReceipt.MeterInfo.isused.TMeter = 1;


	resultMeteringReceipt.AC_EVSEStatus = &evseStatus;

	/***********************
	 * Call meteringReceipt *
	 ***********************/
	printf("\nPEV: call EVSE meteringReceipt\n");



	if(call_meteringReceipt(&service,&v2gHeader,&meteringReceipt,&resultMeteringReceipt))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultMeteringReceipt.ResponseCode);
		printACEVSEStatus(resultMeteringReceipt.AC_EVSEStatus);
	}

	return 0;
}

static int dc_charging()
{



	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */



	/* define offset variable for transport header data */
	uint16_t transportHeaderOffset;


	/* service data structure for DC*/
	struct EXIService service;
	struct MessageHeaderType v2gHeader;
	struct SessionSetupReqType sessionSetup;
	struct SessionSetupResType resultSessionSetup;
	struct ServiceDiscoveryReqType serviceDiscovery;
	struct ServiceDiscoveryResType resultServiceDiscovery;
	struct ChargeParameterDiscoveryReqType powerDiscovery;
	struct ChargeParameterDiscoveryResType resultPowerDiscovery;
	struct CableCheckReqType cableCheck;
	struct CableCheckResType resultCableCheck;
	struct PowerDeliveryReqType powerDelivery;
	struct PowerDeliveryResType resultPowerDelivery;
	struct PreChargeReqType preCharge;
	struct PreChargeResType resultPreCharge;
	struct CurrentDemandReqType currentDemand;
	struct CurrentDemandResType resultCurrentDemand;
	struct WeldingDetectionReqType weldingDetection;
	struct WeldingDetectionResType resultWeldingDetection;
	struct TerminateChargingReqType terminateCharging;
	struct TerminateChargingResType resultTerminateCharging;

	struct DC_PEVStatusType pevStatus;
	struct DC_EVSEStatusType evseStatus;
	struct DC_PEVChargeParameterType pevChargeParameter;
	struct DC_EVSEChargeParameterType evseChargeParameter;
	struct DC_PEVPowerDeliveryParameterType pevPowerDelivery;


	struct FloatingValueType float_type; /* test float type*/

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/* setup offset for DoIP header (otherwise set
	 * transportHeaderOffset=0 if no transfer protocol is used)*/
	transportHeaderOffset = V2GTP_HEADER_LENGTH;


	/*******************
	 * Init V2G Client *
	 *******************/

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, transportHeaderOffset);


	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionInformation.SessionID.data[0] = 0; /* sessionID is always '0' at the beginning (the response contains the valid sessionID)*/
	v2gHeader.SessionInformation.SessionID.arraylen.data = 1; /* no session id in the initial message -> array length = 0*/
	v2gHeader.SessionInformation.ProtocolVersion.data[0]='1'; /* assign protocol version number*/
	v2gHeader.SessionInformation.ProtocolVersion.arraylen.data=1; /* array string length =1 of protocol version */
	v2gHeader.SessionInformation.isused.ProtocolVersion = 1; /* important: optional elements have to be set used (=1) or not used (=0) */
	v2gHeader.SessionInformation.isused.ServiceSessionID = 0; /* service session is not used */
	v2gHeader.isused.Notification=0; /* no notification */
	v2gHeader.isused.Security=0; /* no security */

	/* setup sessionSetup parameter */
	sessionSetup.isused.PEVID=1; /*  PEVID is transported */
	sessionSetup.PEVID.arraylen.data=1;
	sessionSetup.PEVID.data[0]=10;


	printf("PEV: call EVSE sessionSetup\n");

	/*********************
	 * Call sessionSetup *
	 *********************/
	if(call_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\tHeader SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printf("\tTCurrent=%d\n",resultSessionSetup.TCurrent);
	}





	/*******************************************
	 * Setup data for serviceDiscovery *
	 *******************************************/

	serviceDiscovery.isused.ServiceType=1;
	serviceDiscovery.ServiceType = 	PEVRechargeCharge_serviceCategoryType;
	serviceDiscovery.isused.ServiceScope=0;


	printf("PEV: call EVSE serviceDiscovery\n");

	/*************************
	 * Call serviceDiscovery *
	 *************************/
	if(call_serviceDiscovery(&service,&v2gHeader, &serviceDiscovery,&resultServiceDiscovery))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\t Header SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\t ResponseCode=%d\n",resultServiceDiscovery.ResponseCode);
		printf("\t ServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceTag.ServiceID.data[0]);
		printf("\t PaymentOption=%d\n",	resultServiceDiscovery.PaymentOptions.PaymentOption[0]);
		printf("\t EnergyTransferType=%d\n",	resultServiceDiscovery.ChargeService.EnergyTransferType);
	}







	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	powerDiscovery.PEVRequestedEnergyTransferType = DC_core_PEVRequestedEnergyTransferType;

	/* setup PEVStatus */
	pevStatus.ConnectorLocked = 1;
	pevStatus.PEVRESSSOC = 89;
	pevStatus.PEVReady = 1;
	pevStatus.PEVStandby = 1;
	pevStatus.PEVStatusCode = PEVCabinConditioning_DC_PEVStatusCodeType;

	pevChargeParameter.DC_PEVStatus = pevStatus;


	float_type.Multiplier = 0;
	float_type.Unit = A_unitSymbolType;
	float_type.Value = 100;

	pevChargeParameter.PEVMaximumCurrentLimit = float_type;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 200;

	pevChargeParameter.PEVMaximumPowerLimit = float_type;
	pevChargeParameter.isused.PEVMaximumPowerLimit = 1;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 300;

	pevChargeParameter.PEVMaximumVoltageLimit= float_type;

	float_type.Unit = W_s_unitSymbolType;
	float_type.Value = 400;

	pevChargeParameter.PEVEnergyCapacity= float_type;
	pevChargeParameter.isused.PEVEnergyCapacity = 1;

	float_type.Unit = W_s_unitSymbolType;
	float_type.Value = 500;

	pevChargeParameter.PEVEnergyRequest= float_type;
	pevChargeParameter.isused.PEVEnergyRequest = 1;

	pevChargeParameter.FullSOC=0;
	pevChargeParameter.isused.FullSOC = 1;

	pevChargeParameter.BulkSOC=100;
	pevChargeParameter.isused.BulkSOC = 1;

	pevChargeParameter.PEVProtocolVersion = 12;

	powerDiscovery.DC_PEVChargeParameter = &pevChargeParameter;
	powerDiscovery.isused.DC_PEVChargeParameter = 1; /* we use here DC based charging parameters */
	powerDiscovery.isused.AC_PEVChargeParameter = 0;

	resultPowerDiscovery.DC_EVSEChargeParameter = &evseChargeParameter; /* we expect DC-based parameters from the evse*/

	/*********************************
	 * Call chargeParameterDiscovery *
	 *********************************/
	printf("\nPEV: call EVSE chargeParameterDiscovery\n");

	if(call_chargeParameterDiscovery(&service,&v2gHeader,&powerDiscovery,&resultPowerDiscovery))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("PEV: received response message from EVSE\n");
		printf("\t\t Header SessionID=%d\n",v2gHeader.SessionInformation.SessionID.data[0]);
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printDCEVSEStatus(&(resultPowerDiscovery.DC_EVSEChargeParameter->DC_EVSEStatus));
		printf("\tEVSEMaximumCurrentLimit=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEMaximumCurrentLimit.Value);
		printf("\tEVSEMaximumPowerLimit=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEMaximumPowerLimit.Value);
		printf("\tEVSEMaximumVoltageLimit=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEMaximumVoltageLimit.Value);
		printf("\tEVSEMinimumCurrentLimit=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEMinimumCurrentLimit.Value);

		printf("\tEVSEMinimumVoltageLimit=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEMinimumVoltageLimit.Value);
		printf("\tEVSECurrentRegulationTolerance=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSECurrentRegulationTolerance.Value);
		printf("\tEVSEPeakCurrentRipple=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEPeakCurrentRipple.Value);
		printf("\tEVSEEnergyToBeDelivered=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEEnergyToBeDelivered.Value);
		printf("\tEVSEProtocolVersion=%d\n",resultPowerDiscovery.DC_EVSEChargeParameter->EVSEProtocolVersion);
	}




	/***********************
	 * Call cableCheck     *
	 ***********************/
	printf("\nPEV: call EVSE cableCheck\n");

	cableCheck.DC_PEVStatus =pevStatus;



	if(call_cableCheck(&service,&v2gHeader,&cableCheck,&resultCableCheck))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultCableCheck.ResponseCode);
		printDCEVSEStatus(&(resultCableCheck.DC_EVSEStatus));
	}


	/***********************
	 * Call preCharge      *
	 ***********************/
	printf("\nPEV: call EVSE preCharge\n");

	preCharge.DC_PEVStatus =pevStatus;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 100;
	preCharge.PEVRESSVoltage = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 200;
	preCharge.PEVTargetVoltage = float_type;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 300;
	preCharge.PEVTargetVoltage = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 400;
	preCharge.PEVTargetVoltage = float_type;



	if(call_preCharge(&service,&v2gHeader,&preCharge,&resultPreCharge))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPreCharge.ResponseCode);
		printDCEVSEStatus(&resultPreCharge.DC_EVSEStatus);
		printf("\tVoltageOutput=%d\n",resultPreCharge.EVSEPresentVoltage.Value);
	}



		/*********************************
		 * Setup data for powerDelivery *
		 *********************************/

		powerDelivery.ReqSwitchStatus = 1;
		powerDelivery.isused.Tariff = 0;
		powerDelivery.isused.ChargingProfile= 0;

		powerDelivery.isused.DC_PEVPowerDeliveryParameter=1;
		powerDelivery.isused.AC_PEVPowerDeliveryParameter=0;
		pevPowerDelivery.DC_PEVStatus = pevStatus;
		pevPowerDelivery.BulkChargingComplete = 1;
		pevPowerDelivery.isused.BulkChargingComplete = 1;
		pevPowerDelivery.ChargingComplete = 0;

		powerDelivery.DC_PEVPowerDeliveryParameter = &pevPowerDelivery;

		resultPowerDelivery.DC_EVSEStatus = &evseStatus; /* we expect the DC-based EVSE status */

		/***********************
		 * Call powerDelivery *
		 ***********************/
		printf("\nPEV: call EVSE powerDelivery\n");

		if(call_powerDelivery(&service,&v2gHeader,&powerDelivery,&resultPowerDelivery))
		{
			printErrorMessage(&service);
		}
		else
		{

			/* show result of the answer message of EVSE sessionSetup*/
			printf("PEV: received response message from EVSE\n");
			printf("\tResponseCode=%d\n",resultPowerDelivery.ResponseCode);
			printDCEVSEStatus(resultPowerDelivery.DC_EVSEStatus);
		}





		/***********************
		 * Call currentDemand      *
		 ***********************/
		printf("\nPEV: call EVSE currentDemand\n");

		currentDemand.DC_PEVStatus = pevStatus;

		float_type.Unit = A_unitSymbolType;
		float_type.Value = 100;

		currentDemand.ChargeCurrentRequest = float_type;

		float_type.Unit = V_unitSymbolType;
		float_type.Value = 200;

		currentDemand.PEVMaximumVoltageLimit = float_type;
		currentDemand.isused.PEVMaximumVoltageLimit = 1;

		float_type.Unit = W_unitSymbolType;
		float_type.Value = 300;

		currentDemand.PEVMaximumPowerLimit = float_type;
		currentDemand.isused.PEVMaximumPowerLimit = 1;

		float_type.Unit = A_unitSymbolType;
		float_type.Value = 400;

		currentDemand.PEVMaximumCurrentLimit = float_type;
		currentDemand.isused.PEVMaximumCurrentLimit = 1;

		currentDemand.BulkChargingComplete = 1;
		currentDemand.isused.BulkChargingComplete = 1;

		currentDemand.ChargingComplete = 0;

		float_type.Unit = s_unitSymbolType;
		float_type.Value = 500;

		currentDemand.RemainingTimeToFullSoC = float_type;
		currentDemand.isused.RemainingTimeToFullSoC = 1;

		float_type.Unit = s_unitSymbolType;
		float_type.Value = 600;

		currentDemand.RemainingTimeToBulkSoC = float_type;
		currentDemand.isused.RemainingTimeToBulkSoC = 1;


		float_type.Unit = V_unitSymbolType;
		float_type.Value = 700;

		currentDemand.PEVTargetVoltage = float_type;

		float_type.Unit = A_unitSymbolType;
		float_type.Value = 800;

		currentDemand.CurrentDifferential = float_type;

		float_type.Unit = V_unitSymbolType;
		float_type.Value = 900;

		currentDemand.VoltageDifferential = float_type;


		if(call_currentDemand(&service,&v2gHeader,&currentDemand,&resultCurrentDemand))
		{
			printErrorMessage(&service);
		}
		else
		{

			/* show result of the answer message of EVSE powerDiscovery*/
			printf("PEV: received response message from EVSE\n");
			printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
			printDCEVSEStatus(&resultCurrentDemand.DC_EVSEStatus);
			printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
			printDCEVSEStatus(&(resultCurrentDemand.DC_EVSEStatus));
			printf("\t EVSEPresentVoltage=%d\n",resultCurrentDemand.EVSEPresentVoltage.Value);
			printf("\t EVSEPresentCurrent=%d\n",resultCurrentDemand.EVSEPresentCurrent.Value);
			printf("\t EVSECurrentLimitAchieved=%d\n",resultCurrentDemand.EVSECurrentLimitAchieved);
			printf("\t EVSEVoltageLimitAchieved=%d\n",resultCurrentDemand.EVSEVoltageLimitAchieved);

			printf("\t EVSEPowerLimitAchieved=%d\n",resultCurrentDemand.EVSEPowerLimitAchieved);
			printf("\t EVSEMaximumVoltageLimit=%d\n",resultCurrentDemand.EVSEMaximumVoltageLimit.Value);
			printf("\t EVSEMaximumCurrentLimit=%d\n",resultCurrentDemand.EVSEMaximumCurrentLimit.Value);
			printf("\t EVSEMaximumPowerLimit=%d\n",resultCurrentDemand.EVSEMaximumPowerLimit.Value);

		}

		/***********************
		 * Call weldingDetection     *
		 ***********************/

		printf("\nPEV: call EVSE weldingDetection\n");
		weldingDetection.DC_PEVStatus =pevStatus;

		if(call_weldingDetection(&service,&v2gHeader,&weldingDetection,&resultWeldingDetection))
		{
			printErrorMessage(&service);
		}
		else
		{

			/* show result of the answer message of EVSE powerDiscovery*/
			printf("PEV: received response message from EVSE\n");
			printf("\tResponseCode=%d\n",resultWeldingDetection.ResponseCode);
			printDCEVSEStatus(&resultWeldingDetection.DC_EVSEStatus);
			printf("\tEVSEPresentVoltage=%d\n",resultWeldingDetection.EVSEPresentVoltage.Value);
		}



		/*************************
		 * Call terminateCharging*
		 *************************/
		printf("\nPEV: call EVSE terminateCharging\n");
		terminateCharging.DC_PEVStatus =pevStatus;

		if(call_terminateCharging(&service,&v2gHeader,&terminateCharging,&resultTerminateCharging))
		{
			printErrorMessage(&service);
		}
		else
		{

			/* show result of the answer message of EVSE powerDiscovery*/
			printf("PEV: received response message from EVSE\n");
			printf("\tResponseCode=%d\n",resultTerminateCharging.ResponseCode);
			printf("\tEVSEPresentVoltage=%d\n",resultTerminateCharging.EVSEPresentVoltage.Value);
		}

		return 0;

	}



int main_service()
{
	printf("+++ Start V2G client / service example for AC charging +++\n\n");

	 ac_charging();

	printf("\n+++Terminate V2G Client / Service example for AC charging +++\n");
	printf("Please press enter for DC charging!\n");
	fflush(stdout);
	getchar();

	printf("+++ Start V2G client / service example for DC charging +++\n\n");

	dc_charging();

	printf("\n+++Terminate V2G client / service example for DC charging +++");

	return 0;
}

static void printACEVSEStatus(struct AC_EVSEStatusType* status)
{
	printf("\tEVSEStatus:\n\t\tConnectorLocked=%d\n",status->ConnectorLocked);
	printf("\t\tEVSEStandby=%d\n",status->EVSEStandby);
	printf("\t\tPowerSwitchClosed=%d\n",status->PowerSwitchClosed);
	printf("\t\tRCD=%d\n",status->RCD);
	printf("\t\tShutDownTime=%d\n",status->ShutDownTime);
	printf("\t\tStopCharging=%d\n",status->StopCharging);
}

static void printDCEVSEStatus(struct DC_EVSEStatusType* status)
{
	printf("\tEVSEStatus:\n\t\tEVSEStandby=%d\n",status->EVSEStandby);
	printf("\t\tEVSEStatusCode=%d\n",status->EVSEStatusCode);

}

static void printErrorMessage(struct EXIService* service)
{
	if(service->errorCode==EXI_NON_VALID_MESSAGE)
	{
		printf("PEV did not send a valid V2G message!\n");
	}
	else if(service->errorCode==EXI_SERIALIZATION_FAILED)
	{
		printf("EVSE error: Could not serialize the response message\n");
	}
}

static void printASCIIString(uint32_t* string, uint32_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%c",(char)string[i]);
	}
	printf("\n");
}


