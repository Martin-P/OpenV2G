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
 * @version 0.4
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/



#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceClientStubs.h"
#include "EXITypes.h"
#include "doIP.h"

#include <stdio.h>

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 60

static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

static void printEVSEStatus(struct EVSEStatusType* status);
static void printErrorMessage(struct EXIService* service);

static int ac_charging()
{
	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */

	/* define offset variable for transport header data */
	uint16_t transportHeaderOffset;

	/* service data structure */
	struct EXIService service;
	struct HeaderType v2gHeader;
	struct SessionSetupReqType sessionSetup;
	struct SessionSetupResType resultSessionSetup;
	struct ChargeParameterDiscoveryReqType powerDiscovery;
	struct ChargeParameterDiscoveryResType resultPowerDiscovery;
	struct LineLockReqType lineLock;
	struct LineLockResType resultLineLock;
	struct PowerDeliveryReqType powerDelivery;
	struct PowerDeliveryResType resultPowerDelivery;
	struct MeteringStatusResType resultMeteringStatus;
	struct MeteringReceiptReqType meteringReceipt;
	struct MeteringReceiptResType resultMeteringReceipt;


	struct FloatingValueType float_type; /* test float type*/


	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/* setup offset for DoIP header (otherwise set
	 * transportHeaderOffset=0 if no transfer protocol is used)*/
	transportHeaderOffset = DOIP_HEADER_LENGTH;

	/*******************
	 * Init V2G Client *
	 *******************/

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, transportHeaderOffset);

	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionInformation.SessionID.arraylen.data = 0; /* no session id in the initial message -> array length = 0*/
	v2gHeader.SessionInformation.ProtocolVersion.data[0]='1'; /* assign protocol version number*/
	v2gHeader.SessionInformation.ProtocolVersion.arraylen.data=1; /* array string length =1 of protocol version */
	v2gHeader.SessionInformation.isused.ProtocolVersion = 1; /* important: optional elements have to be set used (=1) or not used (=0) */
	v2gHeader.SessionInformation.isused.ServiceSessionID = 0; /* service session is not used */
	v2gHeader.isused.Notification=0; /* no notification */

	/* setup sessionSetup parameter */
	sessionSetup.isused.PEVID=1; /*  PEVID is transported */
	sessionSetup.PEVID.arraylen.data=1;
	sessionSetup.PEVID.data[0]=10;
	sessionSetup.PEVStatus.ChargerStandby=0; /* charger standby = true */
	sessionSetup.PEVStatus.ConnectorLocked=0; /* connector locked = false */
	sessionSetup.PEVStatus.ReadyToCharge=0; /* ReadyToCharge = false */



	printf("PEV: call EVSE sessionSetup\n");

	/*********************
	 * Call sessionSetup *
	 *********************/
	if(call_sessionSetup(&service,&v2gHeader,&sessionSetup,&resultSessionSetup))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d (OK)\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printEVSEStatus(&resultSessionSetup.EVSEStatus);
		printf("\tTCurrent=%d\n",resultSessionSetup.TCurrent);
	}


	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	powerDiscovery.PEVStatus.ChargerStandby = 1;
	powerDiscovery.PEVStatus.ConnectorLocked = 0;
	powerDiscovery.PEVStatus.ReadyToCharge=0;
	powerDiscovery.ChargingMode = AC_charging_chargingModeType;
	powerDiscovery.EoC = 12345678;

	float_type.Multiplier = 0;
	float_type.Unit = J_unitSymbolType;
	float_type.Value = 100;

	powerDiscovery.EAmount = float_type;
	powerDiscovery.PEVMaxPhases = 3;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 600;
	powerDiscovery.PEVMaxPower = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 1000;
	powerDiscovery.PEVMaxVoltage = float_type;
	float_type.Value = 200;
	powerDiscovery.PEVMinVoltage = float_type;

	/* only required for DC */
	float_type.Unit = A_unitSymbolType;
	float_type.Value = 200;
	powerDiscovery.PEVMaxCurrent = float_type;
	powerDiscovery.PEVMinCurrent = float_type;


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
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printEVSEStatus(&resultPowerDiscovery.EVSEStatus);
		printf("\tEVSEMaxVoltage=%d\n",resultPowerDiscovery.EVSEMaxVoltage.Value);
		/*printf("\tEVSEMaxCurrent=%d\n",resultPowerDiscovery.EVSEMaxCurrent.Value);*/
		printf("\tEVSEMaxPhases=%d\n",resultPowerDiscovery.EVSEMaxPhases);

		/*printf("\tEnergyProvider=%d\n",resultPowerDiscovery.EnergyProvider.data[0]);*/

	}




	/*********************************
	 * Setup data for lineLock *
	 *********************************/

	lineLock.PEVStatus.ChargerStandby = 1;
	lineLock.PEVStatus.ConnectorLocked = 1;
	lineLock.PEVStatus.ReadyToCharge = 1;
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
		printEVSEStatus(&resultLineLock.EVSEStatus);

	}



	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	powerDelivery.PEVStatus = lineLock.PEVStatus; /* PEV status, taken from lineLock */
	/*powerDelivery.isused.Tariff = 0;
	powerDelivery.Tariff = Green_charge_tariffIDType;*/

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
	}






	/********************
	 * Call meterStatus *
	 ********************/

	printf("\nPEV: call EVSE meterStatus\n");

	if(call_meteringStatus(&service,&v2gHeader,&resultMeteringStatus))
	{
		printErrorMessage(&service);
	}
	else
	{

		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printEVSEStatus(&resultPowerDiscovery.EVSEStatus);
		printf("\tEVSEID=%d\n",resultMeteringStatus.EVSEID.data[0]);
		printf("\tEVSEMaxPower=%d\n",resultMeteringStatus.EVSEMaxPower.Value);
		printf("\tisused.MeterInfo=%d\n",		resultMeteringStatus.isused.MeterInfo);
		printf("\t\tMeterInfo.MeterID=%d\n",		resultMeteringStatus.MeterInfo.MeterID.data[0]);
		printf("\t\tMeterInfo.MeterReading.Value=%d\n",		resultMeteringStatus.MeterInfo.MeterReading.Value);
		printf("\t\tMeterInfo.MeterStatus=%d\n",		resultMeteringStatus.MeterInfo.MeterStatus);
	/*	printf("\t\tMeterInfo.TMeter=%d\n",		resultMeteringStatus.MeterInfo.TMeter);*/
	/*	printf("\t\tisused.PCurrent=%d\n",		resultMeteringStatus.isused.PCurrent);
		printf("\t\tPCurrent=%d\n",		resultMeteringStatus.PCurrent.Value);*/

	}




	/*********************************
	 * Setup data for meteringReceipt *
	 *********************************/

	meteringReceipt.PEVID.arraylen.data=1;
	meteringReceipt.PEVID.data[0]=10;
	meteringReceipt.isused.PEVID=1;

	meteringReceipt.PEVStatus = powerDelivery.PEVStatus; /* PEV status, taken from sessionSetup */

	meteringReceipt.TCurrent = 12345;
	meteringReceipt.isused.TCurrent = 1;
	meteringReceipt.Tariff = Green_charge_tariffIDType;
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


	/* service data structure */
	struct EXIService service;
	struct HeaderType v2gHeader;
	struct SessionSetupReqType sessionSetup;
	struct SessionSetupResType resultSessionSetup;
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




	struct FloatingValueType float_type; /* test float type*/


	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	/* setup offset for DoIP header (otherwise set
	 * transportHeaderOffset=0 if no transfer protocol is used)*/
	transportHeaderOffset = DOIP_HEADER_LENGTH;


	/*******************
	 * Init V2G Client *
	 *******************/

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, transportHeaderOffset);

	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionInformation.SessionID.arraylen.data = 0; /* no session id in the initial message -> array length = 0*/
	v2gHeader.SessionInformation.ProtocolVersion.data[0]='1'; /* assign protocol version number*/
	v2gHeader.SessionInformation.ProtocolVersion.arraylen.data=1; /* array string length =1 of protocol version */
	v2gHeader.SessionInformation.isused.ProtocolVersion = 1; /* important: optional elements have to be set used (=1) or not used (=0) */
	v2gHeader.SessionInformation.isused.ServiceSessionID = 0; /* service session is not used */
	v2gHeader.isused.Notification=0; /* no notification */

	/* setup sessionSetup parameter */
	sessionSetup.isused.PEVID=1; /* no PEVID is transported */
	sessionSetup.PEVID.arraylen.data=1;
	sessionSetup.PEVID.data[0]=10;
	sessionSetup.PEVStatus.ChargerStandby=0; /* charger standby = true */
	sessionSetup.PEVStatus.ConnectorLocked=0; /* connector locked = false */



	printf("PEV: call EVSE sessionSetup\n");

	/*********************
	 * Call sessionSetup *
	 *********************/
	if(call_sessionSetup(&service,&v2gHeader,&sessionSetup,&resultSessionSetup))
	{
		printErrorMessage(&service);
	}
	else
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printEVSEStatus(&resultSessionSetup.EVSEStatus);
		printf("\tTCurrent=%d\n",resultSessionSetup.TCurrent);
	}


	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	powerDiscovery.PEVStatus = sessionSetup.PEVStatus; /* PEV status, taken from sessionSetup */
	powerDiscovery.EoC = 4321;
	powerDiscovery.ChargingMode = DC_charging_chargingModeType;

	float_type.Multiplier = 2;
	float_type.Unit = A_unitSymbolType;
	float_type.Value = 700;

	float_type.Multiplier = 0;
	float_type.Unit = J_unitSymbolType;
	float_type.Value = 100;

	powerDiscovery.EAmount = float_type;
	powerDiscovery.PEVMaxPhases = 3;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 600;
	powerDiscovery.PEVMaxPower = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 1000;
	powerDiscovery.PEVMaxVoltage = float_type;
	float_type.Value = 200;
	powerDiscovery.PEVMinVoltage = float_type;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 800;
	powerDiscovery.PEVMaxCurrent = float_type;
	float_type.Value = 150;
	powerDiscovery.PEVMinCurrent = float_type;


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
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printEVSEStatus(&resultPowerDiscovery.EVSEStatus);
		printf("\tEVSEMaxVoltage=%d\n",resultPowerDiscovery.EVSEMaxVoltage.Value);
		printf("\tEVSEMaxCurrent=%d\n",resultPowerDiscovery.EVSEMaxCurrent.Value);
		printf("\tEVSEMinCurrent=%d\n",resultPowerDiscovery.EVSEMinCurrent.Value);
		printf("\tEVSEMaxPhases=%d\n",resultPowerDiscovery.EVSEMaxPhases);

		/*printf("\tEnergyProvider=%d\n",resultPowerDiscovery.EnergyProvider.data[0]);*/

	}

	/***********************
	 * Call cableCheck     *
	 ***********************/
	printf("\nPEV: call EVSE cableCheck\n");

	cableCheck.PEVStatus.ChargerStandby = 1;
	cableCheck.PEVStatus.ConnectorLocked = 1;
	cableCheck.PEVStatus.ReadyToCharge = 1;


	if(call_cableCheck(&service,&v2gHeader,&cableCheck,&resultCableCheck))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultCableCheck.ResponseCode);
		printEVSEStatus(&resultCableCheck.EVSEStatus);
	}


	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	powerDelivery.PEVStatus = cableCheck.PEVStatus; /* PEV status, taken from sessionSetup */
	powerDelivery.isused.Tariff = 0;
	/*powerDelivery.Tariff = Green_charge_tariffIDType;*/

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
		printEVSEStatus(&resultPowerDelivery.EVSEStatus);
	}


	/***********************
	 * Call preCharge      *
	 ***********************/
	printf("\nPEV: call EVSE preCharge\n");

	preCharge.PEVStatus = cableCheck.PEVStatus;
	float_type.Unit = A_unitSymbolType;
	float_type.Value = 400;
	preCharge.PEVDemandCurrent = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 700;
	preCharge.PEVTargetVoltage = float_type;
	float_type.Value = 300;
	preCharge.VoltageDifferential = float_type;

	if(call_preCharge(&service,&v2gHeader,&preCharge,&resultPreCharge))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPreCharge.ResponseCode);
		printEVSEStatus(&resultPreCharge.EVSEStatus);
		printf("\tEVSEPresentVoltage=%d\n",resultPreCharge.EVSEPresentVoltage.Value);
	}

	/***********************
	 * Call currentDemand      *
	 ***********************/
	printf("\nPEV: call EVSE currentDemand\n");

	currentDemand.PEVStatus = powerDelivery.PEVStatus;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 44;
	currentDemand.CurrentDifferential = float_type;

	float_type.Value = 40;
	currentDemand.PEVDemandCurrent = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 300;
	currentDemand.VoltageDifferential = float_type;

	float_type.Value = 700;
	preCharge.PEVTargetVoltage = float_type;
	currentDemand.PEVTargetVoltage = float_type;

	if(call_currentDemand(&service,&v2gHeader,&currentDemand,&resultCurrentDemand))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
		printEVSEStatus(&resultCurrentDemand.EVSEStatus);
		printf("\tEVSEPresentVoltage.Value=%d\n",resultCurrentDemand.EVSEPresentVoltage.Value);
		printf("\tEVSEPresentCurrent.Value=%d\n",resultCurrentDemand.EVSEPresentCurrent.Value);

	}



	/***********************
	 * Call weldingDetection     *
	 ***********************/
	printf("\nPEV: call EVSE weldingDetection\n");
	weldingDetection.PEVStatus = powerDelivery.PEVStatus;

	if(call_weldingDetection(&service,&v2gHeader,&weldingDetection,&resultWeldingDetection))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultWeldingDetection.ResponseCode);
		printEVSEStatus(&resultWeldingDetection.EVSEStatus);
		printf("\tEVSEPresentVoltage=%d\n",resultWeldingDetection.EVSEPresentVoltage.Value);
	}

	/*************************
	 * Call terminateCharging*
	 *************************/
	printf("\nPEV: call EVSE terminateCharging\n");
	terminateCharging.PEVStatus = sessionSetup.PEVStatus;

	if(call_terminateCharging(&service,&v2gHeader,&terminateCharging,&resultTerminateCharging))
	{
		printErrorMessage(&service);
	}
	else
	{

		/* show result of the answer message of EVSE powerDiscovery*/
		printf("PEV: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultTerminateCharging.ResponseCode);
		printEVSEStatus(&resultWeldingDetection.EVSEStatus);
		printf("\tEVSEPresentVoltage.Value=%d\n",resultTerminateCharging.EVSEPresentVoltage.Value);
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

static void printEVSEStatus(struct EVSEStatusType* status)
{
	printf("\tEVSEStatus:\n\t\tConnectorLocked=%d\n",status->ConnectorLocked);
	printf("\t\tEVSEStandby=%d\n",status->EVSEStandby);
	printf("\t\tFatalError=%d\n",status->FatalError);
	printf("\t\tPowerSwitchClosed=%d\n",status->PowerSwitchClosed);
	printf("\t\tRCD=%d\n",status->RCD);
	printf("\t\tChargerStandby=%d\n",status->ChargerStandby);
	printf("\t\tEVSEMalfunction=%d\n",status->EVSEMalfunction);
	printf("\t\tShutDownTime=%d\n",status->ShutDownTime);
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

