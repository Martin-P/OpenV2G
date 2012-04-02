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
 * @version 0.6
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

/* includes of the 15118 messaging */
#include "v2g_service.h"
#include "v2g_serviceDataTypes.h"
#include "v2g_serviceClientStubs.h"
#include "EXITypes.h"

/* includes for the application handshake protocol */
#include "appHand_service.h"
#include "appHand_dataTypes.h"



/* includes V2GTP */
#include "v2gtp.h"

/* includes for example data transmitter */
#include "v2g_serviceClientDataTransmitter.h"


#include <stdio.h>

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 100


static void printErrorMessage(struct EXIService* service);
static void printDCEVSEStatus(struct DC_EVSEStatusType* status);
static void printACEVSEStatus(struct AC_EVSEStatusType* status);
static void printASCIIString(uint32_t* string, uint32_t len);
static void printBinaryArray(uint8_t* byte, uint32_t len);
static int writeStringToEXIString(char* string, uint32_t* exiString);

/** Example implementation of the handshake protocol (EV side) */
static int appHandshake()
{
	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */

	/* BINARY memory setup */
	bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	struct EXIDatabinder appHandService;
	struct EXIDocumentType_appHand exiDoc;
	struct AnonType_supportedAppProtocolReq handshake;
	struct AnonType_supportedAppProtocolRes resultHandshake;
	uint16_t length, payloadLength;

	/* init the app handshake serializer.
	 * Important: also provide the offset of the V2GTP header length */
	init_appHandSerializer(&appHandService,bytes,string,MAX_STREAM_SIZE, V2GTP_HEADER_LENGTH);

	init_EXIDocumentType_appHand(&exiDoc);

	printf("EV side: setup data for the supported application handshake request message\n");

	/* set up ISO/IEC 15118 Version 1.0 information */
	length = writeStringToEXIString("urn:iso:15118:2:2010:MsgDef", handshake.AppProtocol[0].ProtocolNamespace.data);
	handshake.AppProtocol[0].ProtocolNamespace.arraylen.data = length; /* length of the string */
	handshake.AppProtocol[0].SchemaID=1;
	handshake.AppProtocol[0].VersionNumberMajor=1;
	handshake.AppProtocol[0].VersionNumberMinor=0;
	handshake.AppProtocol[0].Priority=1;

	handshake.arraylen.AppProtocol=1; /* we have only one protocol implemented */

	/* assign handshake request structure to the exiDoc and signal it */
	exiDoc.supportedAppProtocolReq = &handshake;
	exiDoc.isused.supportedAppProtocolReq=1;

	payloadLength=0;
	if(serialize_appHand(&appHandService, outStream,&payloadLength, &exiDoc))
	{

		/* an error occured */
		return -1;
	}

	printf("EV side: send message to the EVSE\n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, payloadLength+V2GTP_HEADER_LENGTH, inStream);

	/* Init deserializer
	 * Provide here also the offset of the transport protocol */
	init_appHandDeserializer(&appHandService,bytes,string,V2GTP_HEADER_LENGTH);

	/* setup the */
	init_EXIDocumentType_appHand(&exiDoc);
	exiDoc.supportedAppProtocolRes=&resultHandshake;
	exiDoc.isused.supportedAppProtocolRes=1;

	if(deserialize_appHand(&appHandService,inStream,100,&exiDoc))
	{
		/* an error occurred */
		return -1;
	}

	printf("EV side: Response of the EVSE \n");
	if(resultHandshake.ResponseCode==OK_SuccessfulNegotiation_responseCodeType)
	{
		printf("\t\tResponseCode=OK_SuccessfulNegotiation\n");
		printf("\t\tSchemaID=%d\n",resultHandshake.SchemaID );
	}

	return 0;

}

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
	struct ServicePaymentSelectionReqType servicePayment;
	struct ServicePaymentSelectionResType resultServicePayment;
	struct ChargeParameterDiscoveryReqType powerDiscovery;
	struct ChargeParameterDiscoveryResType resultPowerDiscovery;
	struct PowerDeliveryReqType powerDelivery;
	struct PowerDeliveryResType resultPowerDelivery;
	struct ChargingStatusResType resultChargingStatus;
	struct MeteringReceiptReqType meteringReceipt;
	struct MeteringReceiptResType resultMeteringReceipt;
	struct SessionStopResType resultSessionStop;

	struct AC_EVSEStatusType evseStatus;
	struct AC_EVChargeParameterType EVChargeParameter;
	struct AC_EVSEChargeParameterType evseChargeParameter;

	struct SAScheduleListType scheduleInfo;
	struct SalesTariffType sales;

	struct PhysicalValueType float_type;

	enum responseMessages resMsg;

	uint32_t outPayloadLength;


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

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, &outPayloadLength, transportHeaderOffset);


	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionID.data[0] = 0; /* sessionID is always '0' at the beginning (the response contains the valid sessionID)*/
	v2gHeader.SessionID.data[1] = 0;
	v2gHeader.SessionID.data[2] = 0;
	v2gHeader.SessionID.data[3] = 0;
	v2gHeader.SessionID.data[4] = 0;
	v2gHeader.SessionID.data[5] = 0;
	v2gHeader.SessionID.data[6] = 0;
	v2gHeader.SessionID.data[7] = 0;
	v2gHeader.SessionID.arraylen.data = 8; /* length of the byte session array is always 8*/

	v2gHeader.isused.Notification=0; /* no notification */
	v2gHeader.isused.Signature=0; /* no security */

	/* setup sessionSetup parameter */
	sessionSetup.EVCCID.data[0]=10;
	sessionSetup.EVCCID.arraylen.data=1;


	printf("EV side: prepare EVSE sessionSetup\n");

	/************************
	 * Prepare sessionSetup *
	 ************************/

	prepare_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup);

	printf("EV side: call EVSE sessionSetup\n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream */
	if(	determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==SESSIONSETUPRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printf("\tDateTimeNow=%d\n",resultSessionSetup.DateTimeNow);
	}

	/*******************************************
	 * Setup data for serviceDiscovery *
	 *******************************************/

	serviceDiscovery.isused.ServiceCategory=1;
	serviceDiscovery.ServiceCategory = 	EVCharging_serviceCategoryType;
	serviceDiscovery.isused.ServiceScope=0;


	printf("\n\nEV side: prepare EVSE serviceDiscovery\n");

	/****************************
	 * Prepare serviceDiscovery *
	 ****************************/

	prepare_serviceDiscovery(&service,&v2gHeader, &serviceDiscovery,&resultServiceDiscovery);

	printf("EV side: call EVSE serviceDiscovery\n ");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the serviceDiscovery response message */
	if(resMsg==SERVICEDISCOVERYRES)
	{
		/* show result of the answer message of EVSE serviceDiscovery */
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServiceDiscovery.ResponseCode);
		printf("\t ServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceTag.ServiceID);
		printf("\t ServiceName=");
		printASCIIString(resultServiceDiscovery.ChargeService.ServiceTag.ServiceName.data,(uint32_t)resultServiceDiscovery.ChargeService.ServiceTag.ServiceName.arraylen.data );
		if(	resultServiceDiscovery.PaymentOptions.PaymentOption[0]==ExternalPayment_paymentOptionType)
		printf("\t PaymentOption=ExternalPayment\n");
		if(resultServiceDiscovery.ChargeService.EnergyTransferType==AC_single_DC_core_EVSESupportedEnergyTransferType)
		printf("\t EnergyTransferType=AC_single_DC_core\n");
		printf("\t Value added service list:\n");
		printf("\t\t ServiceID=%d\n",	resultServiceDiscovery.ServiceList.Service[0].ServiceTag.ServiceID);
		printf("\t\t ServiceName=");
		printASCIIString(resultServiceDiscovery.ServiceList.Service[0].ServiceTag.ServiceName.data,(uint32_t)resultServiceDiscovery.ServiceList.Service[0].ServiceTag.ServiceName.arraylen.data );
		if(resultServiceDiscovery.ServiceList.Service[0].ServiceTag.ServiceCategory==Internet_serviceCategoryType)
		printf("\t\t ServiceCategory=Internet\n");

	}


	/*******************************************
	 * Setup data for ServicePaymentSelection *
	 *******************************************/

	servicePayment.SelectedPaymentOption = ExternalPayment_paymentOptionType;
	servicePayment.SelectedServiceList.SelectedService[0].ServiceID=1; /* charge server ID */
	servicePayment.SelectedServiceList.SelectedService[0].isused.ParameterSetID=0; /* is not used */
	servicePayment.SelectedServiceList.arraylen.SelectedService=1; /* only one service was selected */

	printf("\n\nEV side: prepare EVSE servicePaymentSelection\n");

	/***********************************
	 * Prepare ServicePaymentSelection *
	 ***********************************/

	if(prepare_servicePaymentSelection(&service,&v2gHeader, &servicePayment,&resultServicePayment))
	{
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE ServicePaymentSelection \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==SERVICEPAYMENTSELECTIONRES)
	{
		/* show result of the answer message of EVSE servicePaymentSelection */
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServicePayment.ResponseCode);
	}







	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/
	printf("\n\nEV side: prepare EVSE chargeParameterDiscovery\n");

	powerDiscovery.EVRequestedEnergyTransferType = AC_three_phase_core_EVRequestedEnergyTransferType;

	EVChargeParameter.DepartureTime = 12345;

	float_type.Multiplier = 0;
	float_type.Unit = W_unitSymbolType;
	float_type.isused.Unit=1;
	float_type.Value = 100;

	EVChargeParameter.EAmount = float_type;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 200;

	EVChargeParameter.EVMaxCurrent= float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 400;

	EVChargeParameter.EVMaxVoltage=float_type;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 500;

	EVChargeParameter.EVMinCurrent=float_type;

	powerDiscovery.AC_EVChargeParameter = &EVChargeParameter;
	powerDiscovery.isused.AC_EVChargeParameter = 1; /* we use here DC based charging parameters */
	powerDiscovery.isused.DC_EVChargeParameter = 0;

	resultPowerDiscovery.AC_EVSEChargeParameter = &evseChargeParameter; /* we expect AC-based parameters from the evse*/
	resultPowerDiscovery.SAScheduleList = &scheduleInfo; /* EVSE may send a schedule for us; should be always assigned here! */
	resultPowerDiscovery.SAScheduleList->SAScheduleTuple[0].SalesTariff = &sales;

	prepare_chargeParameterDiscovery(&service,&v2gHeader,&powerDiscovery,&resultPowerDiscovery);


	printf("EV side: call EVSE chargeParameterDiscovery\n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the chargeParameterDiscovery response message */
	if(resMsg==CHARGEPARAMETERDISCOVERYRES)

	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\tResponseCode=%d\n",resultPowerDiscovery.ResponseCode);
		printACEVSEStatus(&(resultPowerDiscovery.AC_EVSEChargeParameter->AC_EVSEStatus));

		printf("\t EVSEMaxCurrent=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxCurrent.Value);
		printf("\t EVSEMaxVoltage=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxVoltage.Value);
		printf("\t EVSEMinimumCurrentLimit=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMinCurrent.Value);
	}


	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	printf("\n\nEV side: prepare EVSE powerDelivery\n");

	powerDelivery.ReadyToChargeState = 1;
	powerDelivery.isused.ChargingProfile= 0;
	powerDelivery.isused.DC_EVPowerDeliveryParameter=0; /* only used for DC charging */
	resultPowerDelivery.AC_EVSEStatus = &evseStatus; /* we expect an evse status */

	prepare_powerDelivery(&service,&v2gHeader,&powerDelivery,&resultPowerDelivery);

	printf("EV side: call EVSE powerDelivery \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the powerDelivery response message */
	if(resMsg==POWERDELIVERYRES)
	{

		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		printf("\tResponseCode=%d\n",resultPowerDelivery.ResponseCode);
		printACEVSEStatus(&evseStatus);
	}


	/*********************************
	 * Setup data for chargingStatus *
	 *********************************/

	printf("\n\nEV side: prepare EVSE chargingStatus\n");

	/***************************
	 * Prepare chargingStatus  *
	 ***************************/

	if(prepare_chargingStatus(&service,&v2gHeader,&resultChargingStatus))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE chargingStatus \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the chargingStatus response message */
	if(resMsg==CHARGINGSTATUSRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultSessionStop.ResponseCode);
		printACEVSEStatus(&evseStatus);
		printf("\tReceiptRequired=%d\n",resultChargingStatus.ReceiptRequired);
		printf("\tSAScheduleTupleID=%d\n",resultChargingStatus.SAScheduleTupleID);
		printf("\tEVSEID=%d\n",resultChargingStatus.EVSEID.data[0]);
		printf("\tEVSEMaxCurrent=%d\n",resultChargingStatus.EVSEMaxCurrent.Value);
		printf("\tisused.MeterInfo=%d\n",		resultChargingStatus.isused.MeterInfo);
		printf("\t\tMeterInfo.MeterID=%d\n",		resultChargingStatus.MeterInfo.MeterID.data[0]);
		printf("\t\tMeterInfo.MeterReading.Value=%d\n",		resultChargingStatus.MeterInfo.MeterReading.Value);
		printf("\t\tMeterInfo.MeterStatus=%d\n",		resultChargingStatus.MeterInfo.MeterStatus);
		printf("\t\tMeterInfo.TMeter=%d\n",		resultChargingStatus.MeterInfo.TMeter);
	}






	/***********************************
	 * Setup data for meteringReceipt *
	 ***********************************/


	meteringReceipt.SessionID = v2gHeader.SessionID;
	meteringReceipt.SAScheduleTupleID = 12;
	meteringReceipt.isused.SAScheduleTupleID=1;
	meteringReceipt.MeterInfo.MeterStatus = 2;
	meteringReceipt.MeterInfo.isused.MeterStatus = 1;
	meteringReceipt.MeterInfo.MeterID.arraylen.data=1;
	meteringReceipt.MeterInfo.MeterID.data[0]=3;

	meteringReceipt.MeterInfo.MeterReading.Multiplier = 0;
	meteringReceipt.MeterInfo.MeterReading.Unit = A_unitSymbolType;
	meteringReceipt.MeterInfo.MeterReading.Value = 100;
	meteringReceipt.MeterInfo.isused.MeterReading = 1;
	meteringReceipt.MeterInfo.isused.SigMeterReading = 0;

	meteringReceipt.MeterInfo.TMeter =123456789;
	meteringReceipt.MeterInfo.isused.TMeter = 1;

	meteringReceipt.isused.attr_Id=0; /* message is not signed */

	printf("\n\nEV side: prepare EVSE meteringReceipt\n");

	/****************************
	 * Prepare meteringReceipt  *
	 ****************************/

	if(prepare_meteringReceipt(&service,&v2gHeader,&meteringReceipt,&resultMeteringReceipt))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE meteringReceipt \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the meteringReceipt response message */
	if(resMsg==METERINGRECEIPTRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultSessionStop.ResponseCode);
		printACEVSEStatus(&evseStatus);
	}


	/***********************************
	 * Setup data for stopSession *
	 ***********************************/

	printf("\n\nEV side: prepare EVSE stopSession\n");

	/************************
	 * Prepare stopSession  *
	 ************************/

	if(prepare_sessionStop(&service,&v2gHeader,&resultSessionStop))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE stopSession \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the stopSession response message */
	if(resMsg==SESSIONSTOPRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultSessionStop.ResponseCode);
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
	struct ServicePaymentSelectionReqType servicePayment;
	struct ServicePaymentSelectionResType resultServicePayment;
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
	struct SessionStopResType resultSessionStop;

	struct DC_EVStatusType EVStatus;
	struct DC_EVSEStatusType evseStatus;
	struct DC_EVChargeParameterType EVChargeParameter;
	struct DC_EVSEChargeParameterType evseChargeParameter;
	struct DC_EVPowerDeliveryParameterType EVPowerDelivery;

	struct SAScheduleListType pmaxScheduleList;

	enum responseMessages resMsg;

	struct PhysicalValueType float_type;

	uint32_t outPayloadLength;


	size_t i, j;

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

	init_v2gServiceClient(&service,bytes,string,inStream,MAX_STREAM_SIZE, outStream, MAX_STREAM_SIZE, &outPayloadLength, transportHeaderOffset);


	/*******************************
	 * Setup data for sessionSetup *
	 *******************************/

	/* setup header information */
	v2gHeader.SessionID.data[0] = 0; /* sessionID is always '0' at the beginning (the response message contains the valid sessionID)*/
	v2gHeader.SessionID.data[1] = 0;
	v2gHeader.SessionID.data[2] = 0;
	v2gHeader.SessionID.data[3] = 0;
	v2gHeader.SessionID.data[4] = 0;
	v2gHeader.SessionID.data[5] = 0;
	v2gHeader.SessionID.data[6] = 0;
	v2gHeader.SessionID.data[7] = 0;
	v2gHeader.SessionID.arraylen.data = 8; /* length of the byte session array is always 8*/

	v2gHeader.isused.Notification=0; /* no notification */
	v2gHeader.isused.Signature=0; /* no security */

	/* setup sessionSetup parameter */
	sessionSetup.EVCCID.data[0]=10;
	sessionSetup.EVCCID.arraylen.data=1;

	printf("EV side: prepare EVSE sessionSetup\n");

	/************************
	 * Prepare sessionSetup *
	 ************************/

	prepare_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup);

	printf("EV side: call EVSE sessionSetup\n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==SESSIONSETUPRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[0]);
		printf("\tDateTimeNow=%d\n",resultSessionSetup.DateTimeNow);
	}

	/*******************************************
	 * Setup data for serviceDiscovery *
	 *******************************************/

	serviceDiscovery.isused.ServiceCategory=1;
	serviceDiscovery.ServiceCategory = 	EVCharging_serviceCategoryType;
	serviceDiscovery.isused.ServiceScope=0;


	printf("\n\nEV side: prepare EVSE serviceDiscovery\n");

	/****************************
	 * Prepare serviceDiscovery *
	 ****************************/

	prepare_serviceDiscovery(&service,&v2gHeader, &serviceDiscovery,&resultServiceDiscovery);

	printf("EV side: call EVSE serviceDiscovery \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the serviceDiscovery response message */
	if(resMsg==SERVICEDISCOVERYRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("\nEV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServiceDiscovery.ResponseCode);
		printf("\t ServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceTag.ServiceID);
		printf("\t ServiceName=");
		printASCIIString(resultServiceDiscovery.ChargeService.ServiceTag.ServiceName.data,(uint32_t)resultServiceDiscovery.ChargeService.ServiceTag.ServiceName.arraylen.data );
		if(	resultServiceDiscovery.PaymentOptions.PaymentOption[0]==ExternalPayment_paymentOptionType)
		printf("\t PaymentOption=ExternalPayment\n");
		if(resultServiceDiscovery.ChargeService.EnergyTransferType==AC_single_DC_core_EVSESupportedEnergyTransferType)
		printf("\t EnergyTransferType=AC_single_DC_core\n");
	}


	/*******************************************
	 * Setup data for ServicePaymentSelection *
	 *******************************************/

	servicePayment.SelectedPaymentOption = ExternalPayment_paymentOptionType;
	servicePayment.SelectedServiceList.SelectedService[0].ServiceID=1; /* charge server ID */
	servicePayment.SelectedServiceList.SelectedService[0].isused.ParameterSetID=0; /* is not used */
	servicePayment.SelectedServiceList.arraylen.SelectedService=1; /* only one service was selected */

	printf("\n\nEV side: prepare EVSE servicePaymentSelection\n");

	/**************************************
	 * Prepare ServicePaymentSelection *
	 **************************************/

	if(prepare_servicePaymentSelection(&service,&v2gHeader, &servicePayment,&resultServicePayment))
	{
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE ServicePaymentSelection \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==SERVICEPAYMENTSELECTIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServicePayment.ResponseCode);
	}



	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	/* setup EVStatus */

	EVStatus.EVRESSSOC = 89;
	EVStatus.EVReady = 1;
	EVStatus.EVCabinConditioning = 1;
	EVStatus.EVRESSConditioning = 1;
	EVStatus.isused.EVCabinConditioning=1;
	EVStatus.isused.EVRESSConditioning=1;
	EVStatus.EVErrorCode = NO_ERROR_DC_EVErrorCodeType;

	EVChargeParameter.DC_EVStatus = EVStatus;


	float_type.Multiplier = 0;
	float_type.Unit = A_unitSymbolType;
	float_type.isused.Unit=1;
	float_type.Value = 60;

	EVChargeParameter.EVMaximumCurrentLimit = float_type;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 20000;

	EVChargeParameter.EVMaximumPowerLimit = float_type;
	EVChargeParameter.isused.EVMaximumPowerLimit = 1;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 420;

	EVChargeParameter.EVMaximumVoltageLimit= float_type;

	float_type.Unit = W_s_unitSymbolType;
	float_type.Value = 15000;

	EVChargeParameter.EVEnergyCapacity= float_type;
	EVChargeParameter.isused.EVEnergyCapacity = 1;

	float_type.Unit = W_s_unitSymbolType;
	float_type.Value = 5000;

	EVChargeParameter.EVEnergyRequest= float_type;
	EVChargeParameter.isused.EVEnergyRequest = 1;

	EVChargeParameter.FullSOC=99;
	EVChargeParameter.isused.FullSOC = 1;

	EVChargeParameter.BulkSOC=80;
	EVChargeParameter.isused.BulkSOC = 1;

	powerDiscovery.EVRequestedEnergyTransferType = DC_combo_core_EVRequestedEnergyTransferType;

	powerDiscovery.DC_EVChargeParameter = &EVChargeParameter;
	powerDiscovery.isused.DC_EVChargeParameter = 1; /* we use here DC based charging parameters */
	powerDiscovery.isused.AC_EVChargeParameter = 0;

	resultPowerDiscovery.DC_EVSEChargeParameter = &evseChargeParameter; /* we expect DC-based parameters from the evse*/

	resultPowerDiscovery.SAScheduleList = &pmaxScheduleList; /* the EVSE can provide some PMax information; should be always assign here! */


	printf("\n\nEV side: prepare EVSE chargeParameterDiscovery\n");

	/************************************
	 * Prepare chargeParameterDiscovery *
	 ************************************/

	if(prepare_chargeParameterDiscovery(&service,&v2gHeader, &powerDiscovery,&resultPowerDiscovery))
	{
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE chargeParameterDiscovery \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the chargeParameterDiscovery response message */
	if(resMsg==CHARGEPARAMETERDISCOVERYRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("\nEV side: received response message from EVSE\n");
		printf("\t\t Header SessionID=%d\n",v2gHeader.SessionID.data[0]);
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

		/* show PMax schedule, if there one provided  */
		if(resultPowerDiscovery.isused.SAScheduleList)
		{
			printf("\tSAScheduleList: \n");

			for(i=0; i< pmaxScheduleList.arraylen.SAScheduleTuple;i++)
			{
				printf("\t\t Tuple#%d: \n",(i+1));
				printf("\t\t SAScheduleTupleID=%d: \n", pmaxScheduleList.SAScheduleTuple[i].SAScheduleTupleID);
				printf("\t\t PMaxScheduleID=%d: \n",pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.PMaxScheduleID);

				for(j=0; j< pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.arraylen.PMaxScheduleEntry;j++)
				{
					printf("\t\t\t Entry#%d: \n",(j+1));
					printf("\t\t\t\t PMax=%d \n",pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].PMax);
					printf("\t\t\t\t Start=%d \n",pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.start);
					if(pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.isused.duration)
						printf("\t\t\t\t Duration=%d \n",pmaxScheduleList.SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.duration);
				}
			}
		}
	}




	/*****************************
	 * Setup data for cableCheck *
	 *****************************/

	/* setup EVStatus */
	cableCheck.DC_EVStatus =EVStatus;


	printf("\n\nEV side: prepare EVSE cableCheck\n");

	/**********************
	 * Prepare cableCheck *
	 **********************/

	if(prepare_cableCheck(&service,&v2gHeader,&cableCheck,&resultCableCheck))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE cableCheck \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the cableCheck response message */
	if(resMsg==CABLECHECKRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		printf("\t\t Header SessionID=%d\n",v2gHeader.SessionID.data[0]);
		printf("\tResponseCode=%d\n",resultCableCheck.ResponseCode);
		printDCEVSEStatus(&(resultCableCheck.DC_EVSEStatus));
	}


	/*****************************
	 * Setup data for preCharge  *
	 *****************************/

	/* setup EVStatus */
	preCharge.DC_EVStatus =EVStatus;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 100;
	preCharge.EVTargetCurrent = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 200;
	preCharge.EVTargetVoltage = float_type;

	printf("\n\nEV side: prepare EVSE preCharge\n");

	/**********************
	 * Prepare preCharge  *
	 **********************/

	if(prepare_preCharge(&service,&v2gHeader,&preCharge,&resultPreCharge))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE preCharge \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the preCharge response message */
	if(resMsg==PRECHARGERES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultPreCharge.ResponseCode);
		printDCEVSEStatus(&resultPreCharge.DC_EVSEStatus);
		printf("\tEVSEPresentVoltage=%d\n",resultPreCharge.EVSEPresentVoltage.Value);
	}



	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	powerDelivery.ReadyToChargeState = 1;

	EVPowerDelivery.DC_EVStatus = EVStatus;
	EVPowerDelivery.BulkChargingComplete = 1;
	EVPowerDelivery.isused.BulkChargingComplete = 1;
	EVPowerDelivery.ChargingComplete = 0;

	powerDelivery.DC_EVPowerDeliveryParameter = &EVPowerDelivery;
	powerDelivery.isused.DC_EVPowerDeliveryParameter = 1; /* DC parameters are send */


	/* we are using a charging profile */
	powerDelivery.isused.ChargingProfile=1;
	powerDelivery.ChargingProfile.SAScheduleTupleID = pmaxScheduleList.SAScheduleTuple[0].SAScheduleTupleID;

	/* set up 3 entries */
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryMaxPower=0;
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryStart=0;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryMaxPower=20000;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryStart=300; /* 5min */
	powerDelivery.ChargingProfile.ProfileEntry[2].ChargingProfileEntryMaxPower=0;
	powerDelivery.ChargingProfile.ProfileEntry[2].ChargingProfileEntryStart=1200; /* 20min */
	powerDelivery.ChargingProfile.arraylen.ProfileEntry=3;



	resultPowerDelivery.DC_EVSEStatus = &evseStatus; /* we expect the DC-based EVSE status */

	printf("\n\nEV side: prepare EVSE powerDelivery\n");


	/**************************
	 * Prepare powerDelivery  *
	 **************************/

	if(prepare_powerDelivery(&service,&v2gHeader,&powerDelivery,&resultPowerDelivery))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE powerDelivery \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the powerDelivery response message */
	if(resMsg==POWERDELIVERYRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("\nEV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultPreCharge.ResponseCode);
		printDCEVSEStatus(&resultPreCharge.DC_EVSEStatus);
	}





	/*********************************
	 * Setup data for currentDemand *
	 *********************************/

	currentDemand.DC_EVStatus = EVStatus;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 100;

	currentDemand.EVTargetCurrent = float_type;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 420;

	currentDemand.EVMaximumVoltageLimit = float_type;
	currentDemand.isused.EVMaximumVoltageLimit = 1;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 20000;

	currentDemand.EVMaximumPowerLimit = float_type;
	currentDemand.isused.EVMaximumPowerLimit = 1;

	float_type.Unit = A_unitSymbolType;
	float_type.Value = 60;

	currentDemand.EVMaximumCurrentLimit = float_type;
	currentDemand.isused.EVMaximumCurrentLimit = 1;

	currentDemand.BulkChargingComplete = 0;
	currentDemand.isused.BulkChargingComplete = 1;

	currentDemand.ChargingComplete = 0;

	float_type.Unit = s_unitSymbolType;
	float_type.Value = 300; /* 5 min*/

	currentDemand.RemainingTimeToFullSoC = float_type;
	currentDemand.isused.RemainingTimeToFullSoC = 1;

	float_type.Unit = s_unitSymbolType;
	float_type.Value = 120; /* 3 min */

	currentDemand.RemainingTimeToBulkSoC = float_type;
	currentDemand.isused.RemainingTimeToBulkSoC = 1;


	float_type.Unit = V_unitSymbolType;
	float_type.Value = 400;

	currentDemand.EVTargetVoltage = float_type;


	printf("\n\nEV side: prepare EVSE currentDemand\n");

	/**************************
	 * Prepare currentDemand  *
	 **************************/

	if(prepare_currentDemand(&service,&v2gHeader,&currentDemand,&resultCurrentDemand))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE currentDemand \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==CURRENTDEMANDRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("\nEV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
		printDCEVSEStatus(&resultCurrentDemand.DC_EVSEStatus);
		printf("\t EVSEPresentVoltage=%d\n",resultCurrentDemand.EVSEPresentVoltage.Value);
		printf("\t EVSEPresentCurrent=%d\n",resultCurrentDemand.EVSEPresentCurrent.Value);
		printf("\t EVSECurrentLimitAchieved=%d\n",resultCurrentDemand.EVSECurrentLimitAchieved);
		printf("\t EVSEVoltageLimitAchieved=%d\n",resultCurrentDemand.EVSEVoltageLimitAchieved);

		printf("\t EVSEPowerLimitAchieved=%d\n",resultCurrentDemand.EVSEPowerLimitAchieved);
		printf("\t EVSEMaximumVoltageLimit=%d\n",resultCurrentDemand.EVSEMaximumVoltageLimit.Value);
		printf("\t EVSEMaximumCurrentLimit=%d\n",resultCurrentDemand.EVSEMaximumCurrentLimit.Value);
		printf("\t EVSEMaximumPowerLimit=%d\n",resultCurrentDemand.EVSEMaximumPowerLimit.Value);
	}






	/***********************************
	 * Setup data for weldingDetection *
	 ***********************************/

	weldingDetection.DC_EVStatus =EVStatus;



	printf("\n\nEV side: prepare EVSE weldingDetection\n");

	/**************************
	 * Prepare weldingDetection  *
	 **************************/

	if(prepare_weldingDetection(&service,&v2gHeader,&weldingDetection,&resultWeldingDetection))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE weldingDetection \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==WELDINGDETECTIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
		printDCEVSEStatus(&resultCurrentDemand.DC_EVSEStatus);
		printf("\tEVSEPresentVoltage=%d\n",resultWeldingDetection.EVSEPresentVoltage.Value);
	}





	/***********************************
	 * Setup data for stopSession *
	 ***********************************/

	printf("\n\nEV side: prepare EVSE stopSession\n");

	/************************
	 * Prepare stopSession  *
	 ************************/

	if(prepare_sessionStop(&service,&v2gHeader,&resultSessionStop))
	{
		printErrorMessage(&service);
		return 0; /* stop here */
	}

	printf("EV side: call EVSE stopSession \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMesssage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==SESSIONSTOPRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultCurrentDemand.ResponseCode);
	}


	return 0;
}



int main()
{
	printf("+++ Start application handshake protocol example +++\n\n");

	appHandshake();

	printf("+++ Terminate application handshake protocol example +++\n\n");

	printf("\n\nPlease press enter for AC charging!\n");
	fflush(stdout);
	 getchar();
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
	printf("\tEVSEStatus:\n");
	printf("\t\tPowerSwitchClosed=%d\n",status->PowerSwitchClosed);
	printf("\t\tRCD=%d\n",status->RCD);
	printf("\t\tShutDownTime=%d\n",status->ShutDownTime);
	printf("\t\tStopCharging=%d\n",status->StopCharging);
}

static void printDCEVSEStatus(struct DC_EVSEStatusType* status)
{
	if(status->isused.EVSEIsolationStatus)
		printf("\tEVSEStatus:\n\t\tEVSEIsolationStatus=%d\n",status->EVSEIsolationStatus);

	printf("\t\tEVSEStatusCode=%d\n",status->EVSEStatusCode);

}

static void printErrorMessage(struct EXIService* service)
{
	if(service->errorCode==EXI_NON_VALID_MESSAGE)
	{
		printf("EV did not send a valid V2G message!\n");
	}
	else if(service->errorCode==EXI_SERIALIZATION_FAILED)
	{
		printf("EVSE error: Could not serialize the response message\n");
	} 	else if(service->errorCode==EXI_SERIALIZATION_FAILED)
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

static void printBinaryArray(uint8_t* byte, uint32_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}

static int writeStringToEXIString(char* string, uint32_t* exiString)
{

	int pos=0;
	while(string[pos]!='\0')
	{
		exiString[pos] = string[pos];
		pos++;
	}

	return pos;
}

