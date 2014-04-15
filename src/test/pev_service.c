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
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

/* includes for the application handshake protocol */
#include "appHand_service.h"
#include "appHand_dataTypes.h"


/* includes V2GTP */
#include "v2gtp.h"

/* includes for example data transmitter */
#include "v2g_serviceClientDataTransmitter.h"

/* includes of the 15118 messaging */
#include "v2g_service.h"
#include "v2g_dataTypes.h"
#include "v2g_dataTypes.c"
#include "v2g_serviceClientStubs.h"
#include "EXITypes.h"
/*#include "appHandQNameDefines.h" */

#include <stdio.h>

#define MAX_BYTE_SIZE 128
#define MAX_STRING_SIZE 256
#define MAX_STREAM_SIZE 256


static void printErrorMessage(struct EXIService* service);
static void printDCEVSEStatus(struct DC_EVSEStatusType* status);
static void printACEVSEStatus(struct AC_EVSEStatusType* status);
static void printASCIIString(uint32_t* string, uint32_t len);
static void printBinaryArray(uint8_t* byte, uint32_t len);
static int writeStringToEXIString(char* string, uint32_t* exiString);




static int appHandshake()
{
	static uint8_t byte_array[MAX_BYTE_SIZE]; /* define MAX_BYTE_SIZE before*/
	static uint32_t string_array[MAX_STRING_SIZE]; /* define MAX_STRING_SIZE before*/

	/* define in and out byte stream */
	uint8_t inStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */
	uint8_t outStream[MAX_STREAM_SIZE]; /* define MAX_STREAM_SIZE before */

	/* BINARY memory setup */
	exi_bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	exi_string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

	struct EXIDatabinder appHandService;
	struct EXIDocumentType_appHand exiDoc;
	struct SupportedAppProtocolReq handshake;
	struct SupportedAppProtocolRes resultHandshake;
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

	length = writeStringToEXIString("urn:din:70121:2012:MsgDef", handshake.AppProtocol[1].ProtocolNamespace.data);
	handshake.AppProtocol[1].ProtocolNamespace.arraylen.data = length; /* length of the string */
	handshake.AppProtocol[1].SchemaID=2;
	handshake.AppProtocol[1].VersionNumberMajor=1;
	handshake.AppProtocol[1].VersionNumberMinor=0;
	handshake.AppProtocol[1].Priority=2;


	handshake.arraylen.AppProtocol=2; /* we have only one protocol implemented */

	/* assign handshake request structure to the exiDoc and signal it */
	exiDoc.isused.supportedAppProtocolReq=1;
	exiDoc.supportedAppProtocolReq = &handshake;

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

	serviceDataTransmitter(outStream, payloadLength, inStream);

	/* Init deserializer
	 * Provide here also the offset of the transport protocol */
	init_appHandDeserializer(&appHandService,bytes,string,V2GTP_HEADER_LENGTH);


	/* setup the */
 	init_EXIDocumentType_appHand(&exiDoc);
	exiDoc.isused.supportedAppProtocolRes=1;

 	exiDoc.supportedAppProtocolRes = &resultHandshake;

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
	struct ServiceDetailReqType serviceDetail;
	struct ServiceDetailResType resultServiceDetail;
	struct PaymentServiceSelectionReqType servicePayment;
	struct PaymentServiceSelectionResType resultServicePayment;
	struct PaymentDetailsReqType paymentDetails;
	struct PaymentDetailsResType resultPaymentDetails;
	struct AuthorizationReqType contractAuthentication;
	struct AuthorizationResType resultContractAuthentication;
	struct ChargeParameterDiscoveryReqType powerDiscovery;
	struct ChargeParameterDiscoveryResType resultPowerDiscovery;
	struct PowerDeliveryReqType powerDelivery;
	struct PowerDeliveryResType resultPowerDelivery;
	struct ChargingStatusResType resultChargingStatus;
	struct MeteringReceiptReqType meteringReceipt;
	struct MeteringReceiptResType resultMeteringReceipt;
	struct SessionStopReqType sessionStop;
	struct SessionStopResType resultSessionStop;

	struct AC_EVChargeParameterType EVChargeParameter;
	struct AC_EVSEChargeParameterType evseChargeParameter;
	struct SalesTariffType sales;
	struct SAScheduleListType schedule;

	struct AC_EVSEStatusType evseStatus;




	struct PhysicalValueType float_type;

	enum responseMessages resMsg;

	uint32_t outPayloadLength;

	size_t i,j;


	/* BINARY memory setup */
	exi_bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	exi_string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

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

	if(prepare_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup))
	{

		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE sessionSetup");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream */
	if(	determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
		return 0;
	}




	/* check, if this is the sessionSetup response message */
	if(resMsg==SESSIONSETUPRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\tResponseCode=%d\n",resultSessionSetup.ResponseCode);
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[1]);
		printf("\tEVSETimeStamp=%d\n",resultSessionSetup.EVSETimeStamp);

	}



	/*******************************************
	 * Setup data for serviceDiscovery *
	 *******************************************/

	serviceDiscovery.isused.ServiceCategory=1;
	serviceDiscovery.ServiceCategory = 	Internet_serviceCategoryType;
	serviceDiscovery.isused.ServiceScope=0;


	printf("\n\nEV side: prepare EVSE serviceDiscovery\n");

	/****************************
	 * Prepare serviceDiscovery *
	 ****************************/

	prepare_serviceDiscovery(&service,&v2gHeader, &serviceDiscovery,&resultServiceDiscovery);

	printf("EV side: call EVSE serviceDiscovery ");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
		return 0;
	}

	/* check, if this is the serviceDiscovery response message */
	if(resMsg==SERVICEDISCOVERYRES)
	{
		/* show result of the answer message of EVSE serviceDiscovery */
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServiceDiscovery.ResponseCode);
		printf("\t ServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceID);
		printf("\t ServiceName=");
		printASCIIString(resultServiceDiscovery.ChargeService.ServiceName.data,(uint32_t)resultServiceDiscovery.ChargeService.ServiceName.arraylen.data );

		if(	resultServiceDiscovery.PaymentOptionList.PaymentOption[1]==Contract_paymentOptionType)
			printf("\t PaymentOption=Contract_paymentOptionType\n");

		if(	resultServiceDiscovery.ChargeService.FreeService==1)
			printf("\t ChargeService.FreeService=True\n");

		if(resultServiceDiscovery.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode[0]==DC_combo_core_EnergyTransferModeType)
			printf("\t EnergyTransferMode=AC_single_DC_core\n");

		if(resultServiceDiscovery.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode[1]==AC_single_phase_core_EnergyTransferModeType)
			printf("\t EnergyTransferMode=AC_single_phase_core_EnergyTransferModeType\n");

		printf("\t Value added service list:\n");
		for(i=0;i<resultServiceDiscovery.ServiceList.arraylen.Service;i++)
		{
			printf("\n\t\t ServiceID=%d\n",	resultServiceDiscovery.ServiceList.Service[i].ServiceID);
			printf("\t\t ServiceName=");
			printASCIIString(resultServiceDiscovery.ServiceList.Service[i].ServiceName.data,(uint32_t)resultServiceDiscovery.ServiceList.Service[i].ServiceName.arraylen.data );
			if(resultServiceDiscovery.ServiceList.Service[i].ServiceCategory==Internet_serviceCategoryType)
				printf("\t\t ServiceCategory=Internet\n");
			if(resultServiceDiscovery.ServiceList.Service[i].FreeService==1)
				printf("\t\t FreeService=True\n");
		}



	}

	/*********************************
	 * Setup data for ServiceDetails *
	 *********************************/

	serviceDetail.ServiceID=22; /* Value Added Server ID */


	printf("\n\nEV side: prepare EVSE serviceDetail\n");

	/*************************
	 * Prepare ServiceDetail *
	 *************************/

	if(prepare_serviceDetail(&service,&v2gHeader, &serviceDetail, &resultServiceDetail)){
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE ServiceDetail \n");

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	if(determineResponseMessage(&service, &resMsg)){
		printErrorMessage(&service);
		return 0;
	}

	if(resMsg==SERVICEDETAILRES){
		printf("EV side: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\tResponseCode=%d\n",   resultServiceDetail.ResponseCode);
		printf("\tServiceID=%d\n",   resultServiceDetail.ServiceID);

		printf("\t\tLength=%d\n",resultServiceDetail.ServiceParameterList.arraylen.ParameterSet);/*TEST*/

		for(i=0; i<resultServiceDetail.ServiceParameterList.arraylen.ParameterSet; i++)
		{
			printf("\t\tServiceSetID=%d\n",   resultServiceDetail.ServiceParameterList.ParameterSet[i].ParameterSetID);
			printf("\t\tParameters=%d\n",   resultServiceDetail.ServiceParameterList.ParameterSet[i].arraylen.Parameter);

			for(j=0; j<resultServiceDetail.ServiceParameterList.ParameterSet[i].arraylen.Parameter; j++)
			{
				printf("\t\t\t %d: ParameterName=", j+1);
				printASCIIString(resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].attr_Name.data,resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].attr_Name.arraylen.data );

				if(resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].isused.stringValue==1)
				{
					printf("\t\t\t %d: StringValue=", j+1);
					printASCIIString(resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].stringValue.data,resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].stringValue.arraylen.data );
				}
				else if(resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].isused.intValue==1)
				{
					printf("\t\t\t %d: IntValue=%d\n", j+1,  resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].intValue);
				} else if(resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].isused.physicalValue==1)
				{
					printf("\t\t\t %d: PhysicalValue=%d (%d %d)\n",  j+1, resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].physicalValue.Value, resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].physicalValue.Unit, resultServiceDetail.ServiceParameterList.ParameterSet[i].Parameter[j].physicalValue.Multiplier);
				}
			}
		}

	}




	/*******************************************
	 * Setup data for ServicePaymentSelection *
	 *******************************************/

	servicePayment.SelectedPaymentOption = ExternalPayment_paymentOptionType;
	servicePayment.SelectedServiceList.SelectedService[0].ServiceID=resultServiceDiscovery.ChargeService.ServiceID; /* charge server ID */
	servicePayment.SelectedServiceList.SelectedService[0].isused.ParameterSetID=0; /* is not used */
	servicePayment.SelectedServiceList.SelectedService[1].ServiceID = resultServiceDiscovery.ServiceList.Service[0].ServiceID;
	servicePayment.SelectedServiceList.SelectedService[1].ParameterSetID=resultServiceDetail.ServiceParameterList.ParameterSet[0].ParameterSetID;
	servicePayment.SelectedServiceList.SelectedService[1].isused.ParameterSetID=1;
	servicePayment.SelectedServiceList.arraylen.SelectedService=2; /* only one service was selected */

	printf("\n\nEV side: prepare EVSE servicePaymentSelection\n");

	/**************************************
	 * Prepare ServicePaymentSelection *
	 **************************************/

	if(prepare_paymentServiceSelection(&service,&v2gHeader, &servicePayment,&resultServicePayment))
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==PAYMENTSERVICESELECTIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServicePayment.ResponseCode);
	}






	/**********************************
	 * Setup data for Payment Details *
	 **********************************/

	paymentDetails.eMAID.data[0]=1;
	paymentDetails.eMAID.data[1]=123;
	paymentDetails.eMAID.arraylen.data=2;

	paymentDetails.ContractSignatureCertChain.Certificate.data[0]='C';
	paymentDetails.ContractSignatureCertChain.Certificate.data[1]='e';
	paymentDetails.ContractSignatureCertChain.Certificate.arraylen.data=2;
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[0].data[0]='S';
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[0].data[1]='u';
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[0].arraylen.data=2;
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[1].data[0]='S';
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[1].data[1]='u';
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[1].data[2]='2';
	paymentDetails.ContractSignatureCertChain.SubCertificates.Certificate[1].arraylen.data=3;
	paymentDetails.ContractSignatureCertChain.SubCertificates.arraylen.Certificate=2;
	paymentDetails.ContractSignatureCertChain.attr_Id.data[0]='I';
	paymentDetails.ContractSignatureCertChain.attr_Id.data[1]='d';
	paymentDetails.ContractSignatureCertChain.attr_Id.arraylen.data=2;
	paymentDetails.ContractSignatureCertChain.isused.SubCertificates=1;
	paymentDetails.ContractSignatureCertChain.isused.attr_Id=1;


	printf("\n\nEV side: prepare EVSE paymentDetails\n");

	/***************************
	 * Prepare Payment Details *
	 ***************************/

	if(prepare_paymentDetails(&service,&v2gHeader, &paymentDetails, &resultPaymentDetails)){
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE ServiceDetail \n");

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	if(determineResponseMessage(&service, &resMsg)){
		printErrorMessage(&service);
		return 0;
	}



	if(resMsg==PAYMENTDETAILSRES){
		printf("EV side: received response message from EVSE\n");
				printf("\tHeader SessionID=");
				printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
				printf("\tResponseCode=%d\n",   resultPaymentDetails.ResponseCode);
				printf("\tEVSETimeStamp=%d\n",   resultPaymentDetails.EVSETimeStamp);
				printf("\tGenChallenge=%d\n",   resultPaymentDetails.GenChallenge.data[0]);
	}





	/*******************************************
	 * Setup data for ContractAuthentification *
	 *******************************************/

	contractAuthentication.GenChallenge = resultPaymentDetails.GenChallenge;
	contractAuthentication.attr_Id.data[0]='I';
	contractAuthentication.attr_Id.data[1]='d';
	contractAuthentication.attr_Id.data[2]='2';
	contractAuthentication.attr_Id.arraylen.data=3;

	contractAuthentication.isused.GenChallenge=1; /* no challenge needed here*/
	contractAuthentication.isused.attr_Id=1; /* no signature needed here */


	printf("\n\nEV side: prepare EVSE contractAuthentification\n");

	/**************************************
	 * Prepare ContractAuthentification   *
	 **************************************/

	if(prepare_authorization(&service,&v2gHeader, &contractAuthentication,&resultContractAuthentication))
	{
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE  Authentification \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==AUTHORIZATIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultContractAuthentication.ResponseCode);
		if(resultContractAuthentication.EVSEProcessing==Finished_EVSEProcessingType)
			printf("\t EVSEProcessing=Finished\n");


	}



	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/
	printf("\n\nEV side: prepare EVSE chargeParameterDiscovery\n");

	powerDiscovery.RequestedEnergyTransferMode = AC_single_phase_core_EnergyTransferModeType;
	powerDiscovery.MaxEntriesSAScheduleTuple=1234;

	EVChargeParameter.DepartureTime = 12345;
	EVChargeParameter.isused.DepartureTime=1;

	float_type.Multiplier = 0;
	float_type.Unit = W_unitSymbolType;
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
	powerDiscovery.isused.AC_EVChargeParameter = 1; /* we use here AC based charging parameters */
	powerDiscovery.isused.DC_EVChargeParameter = 0;

	resultPowerDiscovery.AC_EVSEChargeParameter = &evseChargeParameter; /* we expect AC-based parameters from the evse*/


	/* we expect 1 sale tariff schedule */
	resultPowerDiscovery.SAScheduleList = &schedule;
	resultPowerDiscovery.SAScheduleList->SAScheduleTuple[0].SalesTariff = &sales;

	init_SalesTariffType(&sales); /* init sales structure */
	init_SAScheduleListType(&schedule);

	prepare_chargeParameterDiscovery(&service,&v2gHeader,&powerDiscovery,&resultPowerDiscovery);


	printf("EV side: call EVSE chargeParameterDiscovery");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMessage(&service, &resMsg))
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
		printf("\t EVSEProcessing=%d\n",resultPowerDiscovery.EVSEProcessing);
		printf("\t EVSEMaxCurrent=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSEMaxCurrent.Value);
		printf("\t EVSENominalVoltage=%d\n",resultPowerDiscovery.AC_EVSEChargeParameter->EVSENominalVoltage.Value);
	}



	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	printf("\n\nEV side: prepare EVSE powerDelivery\n");


	powerDelivery.isused.ChargingProfile= 0;
	powerDelivery.isused.DC_EVPowerDeliveryParameter=0; /* only used for DC charging */

	powerDelivery.ChargeProgress=Start_chargeProgressType;
	powerDelivery.SAScheduleTupleID=resultPowerDiscovery.SAScheduleList->SAScheduleTuple[0].SAScheduleTupleID;

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
	if(determineResponseMessage(&service, &resMsg))
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the chargingStatus response message */
	if(resMsg==CHARGINGSTATUSRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultChargingStatus.ResponseCode);
		printACEVSEStatus(&resultChargingStatus.AC_EVSEStatus);
		printf("\tReceiptRequired=%d\n",resultChargingStatus.ReceiptRequired);
		printf("\tEVSEID=%d\n",resultChargingStatus.EVSEID.data[0]);
		printf("\tSAScheduleTupleID=%d\n",resultChargingStatus.SAScheduleTupleID);
		printf("\tEVSEMaxCurrent=%d (%d %d)\n",resultChargingStatus.EVSEMaxCurrent.Value, resultChargingStatus.EVSEMaxCurrent.Unit, resultChargingStatus.EVSEMaxCurrent.Multiplier);
		printf("\tisused.MeterInfo=%d\n",		resultChargingStatus.isused.MeterInfo);
		printf("\t\tMeterInfo.MeterID=%d\n",		resultChargingStatus.MeterInfo.MeterID.data[0]);
		printf("\t\tMeterInfo.MeterReading.Value=%d\n",		resultChargingStatus.MeterInfo.MeterReading);
		printf("\t\tMeterInfo.MeterStatus=%d\n",		resultChargingStatus.MeterInfo.MeterStatus);
		printf("\t\tMeterInfo.TMeter=%d\n",		resultChargingStatus.MeterInfo.TMeter);
		printf("\t\tMeterInfo.SigMeterReading.data=%d\n",		resultChargingStatus.MeterInfo.SigMeterReading.data[0]);
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


	meteringReceipt.MeterInfo.MeterReading = 100;
	meteringReceipt.MeterInfo.isused.MeterReading = 1;
	meteringReceipt.MeterInfo.isused.SigMeterReading = 0;

	meteringReceipt.MeterInfo.TMeter =123456789;
	meteringReceipt.MeterInfo.isused.TMeter = 1;

	meteringReceipt.attr_Id.data[0]='I';
	meteringReceipt.attr_Id.data[1]='d';
	meteringReceipt.attr_Id.data[2]='3';
	meteringReceipt.attr_Id.arraylen.data=3;
	meteringReceipt.isused.attr_Id=1; /* message is signed */

	resultMeteringReceipt.AC_EVSEStatus = &evseStatus; /* we expect EVSE status */

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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the meteringReceipt response message */
	if(resMsg==METERINGRECEIPTRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultMeteringReceipt.ResponseCode);
		printACEVSEStatus(&evseStatus);
	}



	/***********************************
	 * Setup data for stopSession *
	 ***********************************/

	printf("\n\nEV side: prepare EVSE stopSession\n");

	/************************
	 * Prepare stopSession  *
	 ************************/

	sessionStop.ChargingSession = 1;

	if(prepare_sessionStop(&service,&v2gHeader,&sessionStop, &resultSessionStop))
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
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
	struct PaymentServiceSelectionReqType servicePayment;
	struct PaymentServiceSelectionResType resultServicePayment;
	struct AuthorizationReqType contractAuthentication;
	struct AuthorizationResType resultContractAuthentication;
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
	struct SessionStopReqType sessionStop;
	struct SessionStopResType resultSessionStop;

	struct DC_EVStatusType EVStatus;
	struct DC_EVSEStatusType evseStatus;
	struct DC_EVChargeParameterType EVChargeParameter;
	struct DC_EVSEChargeParameterType evseChargeParameter;
	struct DC_EVPowerDeliveryParameterType EVPowerDelivery;
	struct SAScheduleListType SAScheduleList;

	enum responseMessages resMsg;

	struct PhysicalValueType float_type;

	uint32_t outPayloadLength;


	size_t i, j;

	/* BINARY memory setup */
	exi_bytes_t bytes = { MAX_BYTE_SIZE, byte_array, 0 };

	/* STRING memory setup */
	exi_string_ucs_t string = { MAX_STRING_SIZE, string_array, 0 };

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
	sessionSetup.EVCCID.data[0]=20;
	sessionSetup.EVCCID.arraylen.data=1;

	printf("EV side: prepare EVSE sessionSetup\n");

	/************************
	 * Prepare sessionSetup *
	 ************************/

	if(prepare_sessionSetup(&service,&v2gHeader, &sessionSetup,&resultSessionSetup))
	{
		printf("Error!\n");
	}

	printf("EV side: call EVSE sessionSetup\n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream */
	if(determineResponseMessage(&service, &resMsg))
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
		printf("\tEVSEID=%d\n",	resultSessionSetup.EVSEID.data[1]);
		printf("\tDateTimeNow=%d\n",resultSessionSetup.EVSETimeStamp);
	}



	/* else if(resMsg==NOTIFICATION) {

		printf("Received a notification: %d", v2gHeader.Notification.FaultCode );

	}

*/
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
	if(determineResponseMessage(&service, &resMsg))
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
		printf("\t ChargeServiceID=%d\n",	resultServiceDiscovery.ChargeService.ServiceID);
		printf("\t ServiceName=");
		printASCIIString(resultServiceDiscovery.ChargeService.ServiceName.data,(uint32_t)resultServiceDiscovery.ChargeService.ServiceName.arraylen.data );
		printf("\t PaymentOption=%d\n",	resultServiceDiscovery.PaymentOptionList.PaymentOption[1]);
		printf("\t EnergyTransferType=%d\n",	resultServiceDiscovery.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode[1]);
		printf("\t FreeService=%d\n",	resultServiceDiscovery.ChargeService.FreeService);
		printf("\t ServiceCategory=%d\n",	resultServiceDiscovery.ChargeService.ServiceCategory);
		printf("\t ServiceScope=%d\n",	resultServiceDiscovery.ChargeService.ServiceScope.data[0]);
	}




	/*******************************************
	 * Setup data for ServicePaymentSelection *
	 *******************************************/

	servicePayment.SelectedPaymentOption = ExternalPayment_paymentOptionType;
	servicePayment.SelectedServiceList.SelectedService[0].ServiceID=resultServiceDiscovery.ChargeService.ServiceID; /* charge server ID */
	servicePayment.SelectedServiceList.SelectedService[0].isused.ParameterSetID=0; /* is not used */
	servicePayment.SelectedServiceList.arraylen.SelectedService=1; /* only one service was selected */

	printf("\n\nEV side: prepare EVSE servicePaymentSelection\n");

	/**************************************
	 * Prepare ServicePaymentSelection *
	 **************************************/

	if(prepare_paymentServiceSelection(&service,&v2gHeader, &servicePayment,&resultServicePayment))
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==PAYMENTSERVICESELECTIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultServicePayment.ResponseCode);
	}





	/*******************************************
	 * Setup data for ContractAuthentification *
	 *******************************************/

	contractAuthentication.isused.GenChallenge=0; /* no challenge needed here*/
	contractAuthentication.isused.attr_Id=0; /* no signature needed here */


	printf("\n\nEV side: prepare EVSE contractAuthentification\n");

	/**************************************
	 * Prepare ContractAuthentification   *
	 **************************************/

	if(prepare_authorization(&service,&v2gHeader, &contractAuthentication,&resultContractAuthentication))
	{
		printErrorMessage(&service);
		return 0;
	}

	printf("EV side: call EVSE  Authentification \n");

	/* Use here your sending / receiving mechanism to / from the EVSE. The following serviceDataTransmitter method
	 * is only an exemplary implementation which also shows how to add the V2GTP header information to
	 * the output stream.
	 * */

	serviceDataTransmitter(outStream, outPayloadLength, inStream);

	/* this methods deserialize the response EXI stream and determines the kind of
	 * the response message */
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the servicePaymentSelection response message */
	if(resMsg==AUTHORIZATIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup */
		printf("EV: received response message from EVSE\n");
		printf("\tHeader SessionID=");
		printBinaryArray(v2gHeader.SessionID.data,v2gHeader.SessionID.arraylen.data );
		printf("\t ResponseCode=%d\n",resultContractAuthentication.ResponseCode);
		if(resultContractAuthentication.EVSEProcessing==Finished_EVSEProcessingType)
			printf("\t EVSEProcessing=Finished\n");


	}


	/*******************************************
	 * Setup data for chargeParameterDiscovery *
	 *******************************************/

	/* setup EVStatus */

	EVStatus.EVRESSSOC = 89;
	EVStatus.EVReady = 1;

	EVStatus.EVErrorCode = NO_ERROR_DC_EVErrorCodeType;

	EVChargeParameter.DC_EVStatus = EVStatus;

	EVChargeParameter.DepartureTime=123456789;
	EVChargeParameter.isused.DepartureTime=1;

	powerDiscovery.MaxEntriesSAScheduleTuple = 10;
	powerDiscovery.isused.MaxEntriesSAScheduleTuple=1;

	float_type.Multiplier = 0;
	float_type.Unit = A_unitSymbolType;
	float_type.Value = 60;

	EVChargeParameter.EVMaximumCurrentLimit = float_type;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 20000;

	EVChargeParameter.EVMaximumPowerLimit = float_type;
	EVChargeParameter.isused.EVMaximumPowerLimit = 1;

	float_type.Unit = V_unitSymbolType;
	float_type.Value = 420;

	EVChargeParameter.EVMaximumVoltageLimit= float_type;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 15000;

	EVChargeParameter.EVEnergyCapacity= float_type;
	EVChargeParameter.isused.EVEnergyCapacity = 1;

	float_type.Unit = W_unitSymbolType;
	float_type.Value = 5000;

	EVChargeParameter.EVEnergyRequest= float_type;
	EVChargeParameter.isused.EVEnergyRequest = 1;

	EVChargeParameter.FullSOC=99;
	EVChargeParameter.isused.FullSOC = 1;

	EVChargeParameter.BulkSOC=80;
	EVChargeParameter.isused.BulkSOC = 1;

	powerDiscovery.RequestedEnergyTransferMode = DC_combo_core_EnergyTransferModeType;

	powerDiscovery.DC_EVChargeParameter = &EVChargeParameter;
	powerDiscovery.isused.DC_EVChargeParameter = 1; /* we use here DC based charging parameters */
	powerDiscovery.isused.AC_EVChargeParameter = 0;

	resultPowerDiscovery.DC_EVSEChargeParameter = &evseChargeParameter; /* we expect DC-based parameters from the evse*/

	if(powerDiscovery.MaxEntriesSAScheduleTuple>0)
	{
		init_SAScheduleListType(&SAScheduleList);
		resultPowerDiscovery.SAScheduleList = &SAScheduleList;
	}

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
	if(determineResponseMessage(&service, &resMsg))
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
		if(resultPowerDiscovery.EVSEProcessing==Finished_EVSEProcessingType)
			printf("\tEVSEProcessing=Finished\n");
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
			printf("\tSAScheduleList: \n");

			for(i=0; i< resultPowerDiscovery.SAScheduleList->arraylen.SAScheduleTuple;i++)
			{
				printf("\t\t Tuple#%d: \n",(i+1));
				printf("\t\t SAScheduleTupleID=%d: \n", resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].SAScheduleTupleID);

				for(j=0; j< resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.arraylen.PMaxScheduleEntry;j++)
				{
					printf("\t\t\t Entry#%d: \n",(j+1));
					printf("\t\t\t\t PMax=%d (%d %d) \n",resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].PMax.Value, resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].PMax.Unit, resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].PMax.Multiplier);
					printf("\t\t\t\t Start=%d \n",resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.start);
					if(resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.isused.duration)
						printf("\t\t\t\t Duration=%d \n",resultPowerDiscovery.SAScheduleList->SAScheduleTuple[i].PMaxSchedule.PMaxScheduleEntry[j].RelativeTimeInterval.duration);
				}
		}
	}



	/*****************************
	 * Setup data for cableCheck *
	 *****************************/

	/* setup EVStatus */
	EVStatus.EVRESSSOC = 12;
	EVStatus.EVReady = 1;
	EVStatus.EVErrorCode = 1;
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
	if(determineResponseMessage(&service, &resMsg))
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
		if(resultCableCheck.EVSEProcessing==Finished_EVSEProcessingType)
			printf("\tEVSEProcessing=Finished\n");
		printDCEVSEStatus(&(resultCableCheck.DC_EVSEStatus));
	}






	/*****************************
	 * Setup data for preCharge  *
	 *****************************/

	/* setup EVStatus */
	preCharge.DC_EVStatus =EVStatus;

	float_type.Unit = A_unitSymbolType;
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
	if(determineResponseMessage(&service, &resMsg))
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
		printf("\tEVSEPresentVoltage=%d (%d %d)\n",resultPreCharge.EVSEPresentVoltage.Value, resultPreCharge.EVSEPresentVoltage.Unit, resultPreCharge.EVSEPresentVoltage.Multiplier);
	}



	/*********************************
	 * Setup data for powerDelivery *
	 *********************************/

	powerDelivery.ChargeProgress = 1;

	EVPowerDelivery.DC_EVStatus = EVStatus;
	EVPowerDelivery.BulkChargingComplete = 0;
	EVPowerDelivery.isused.BulkChargingComplete = 1;
	EVPowerDelivery.ChargingComplete = 1;

	powerDelivery.DC_EVPowerDeliveryParameter = &EVPowerDelivery;
	powerDelivery.isused.DC_EVPowerDeliveryParameter = 1; /* DC parameters are send */

	powerDelivery.ChargeProgress = Start_chargeProgressType;



	/* we are using a charging profile */
	powerDelivery.isused.ChargingProfile=1;

	powerDelivery.SAScheduleTupleID  = resultPowerDiscovery.SAScheduleList->SAScheduleTuple[0].SAScheduleTupleID;

	/* set up 3 entries */
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryMaxPower.Value=0;
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryMaxPower.Unit=W_unitSymbolType;
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryMaxPower.Multiplier=2;
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryStart=0;
	powerDelivery.ChargingProfile.ProfileEntry[0].ChargingProfileEntryMaxNumberOfPhasesInUse=1;
	powerDelivery.ChargingProfile.ProfileEntry[0].isused.ChargingProfileEntryMaxNumberOfPhasesInUse=1;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryMaxPower.Value=20000;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryMaxPower.Unit = W_unitSymbolType;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryMaxPower.Multiplier = 1;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryMaxNumberOfPhasesInUse=3;
	powerDelivery.ChargingProfile.ProfileEntry[1].isused.ChargingProfileEntryMaxNumberOfPhasesInUse=1;
	powerDelivery.ChargingProfile.ProfileEntry[1].ChargingProfileEntryStart=300; /* 5min */
	powerDelivery.ChargingProfile.ProfileEntry[2].ChargingProfileEntryMaxPower.Value=0;
	powerDelivery.ChargingProfile.ProfileEntry[2].ChargingProfileEntryStart=1200; /* 20min */
	powerDelivery.ChargingProfile.ProfileEntry[2].ChargingProfileEntryMaxNumberOfPhasesInUse=3;
	powerDelivery.ChargingProfile.ProfileEntry[2].isused.ChargingProfileEntryMaxNumberOfPhasesInUse=1;
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the powerDelivery response message */
	if(resMsg==POWERDELIVERYRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("\nEV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultPowerDelivery.ResponseCode);
		printDCEVSEStatus(resultPowerDelivery.DC_EVSEStatus);
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

	currentDemand.ChargingComplete = 1;

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
	if(determineResponseMessage(&service, &resMsg))
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
		printf("\t EVSEMaximumCurrentLimit=%d (%d %d) \n",resultCurrentDemand.EVSEMaximumCurrentLimit.Value, resultCurrentDemand.EVSEMaximumCurrentLimit.Unit, resultCurrentDemand.EVSEMaximumCurrentLimit.Multiplier);
		printf("\t EVSEMaximumPowerLimit=%d\n",resultCurrentDemand.EVSEMaximumPowerLimit.Value);

		printf("\tReceiptRequired=%d\n",resultCurrentDemand.ReceiptRequired);
		printf("\tEVSEID=%d\n",resultCurrentDemand.EVSEID.data[0]);
		printf("\tisused.MeterInfo=%d\n",		resultCurrentDemand.isused.MeterInfo);
		printf("\t\tMeterInfo.MeterID=%d\n",		resultCurrentDemand.MeterInfo.MeterID.data[0]);
		printf("\t\tMeterInfo.MeterReading.Value=%d\n",		resultCurrentDemand.MeterInfo.MeterReading);
		printf("\t\tMeterInfo.MeterStatus=%d\n",		resultCurrentDemand.MeterInfo.MeterStatus);
		printf("\t\tMeterInfo.TMeter=%d\n",		resultCurrentDemand.MeterInfo.TMeter);
	}





	/***********************************
	 * Setup data for weldingDetection *
	 ***********************************/

	EVStatus.EVRESSSOC=100;
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==WELDINGDETECTIONRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultWeldingDetection.ResponseCode);
		printDCEVSEStatus(&resultWeldingDetection.DC_EVSEStatus);
		printf("\tEVSEPresentVoltage=%d (%d %d)\n",resultWeldingDetection.EVSEPresentVoltage.Value,resultWeldingDetection.EVSEPresentVoltage.Unit ,resultWeldingDetection.EVSEPresentVoltage.Multiplier);
	}






	/***********************************
	 * Setup data for stopSession *
	 ***********************************/

	printf("\n\nEV side: prepare EVSE stopSession\n");

	/************************
	 * Prepare stopSession  *
	 ************************/

	sessionStop.ChargingSession = 0;

	if(prepare_sessionStop(&service,&v2gHeader,&sessionStop, &resultSessionStop))
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
	if(determineResponseMessage(&service, &resMsg))
	{
		printErrorMessage(&service);
	}

	/* check, if this is the sessionSetup response message */
	if(resMsg==SESSIONSTOPRES)
	{
		/* show result of the answer message of EVSE sessionSetup*/
		printf("EV side: received response message from EVSE\n");
		/* show result of the answer message of EVSE powerDiscovery*/
		printf("\tResponseCode=%d\n",resultSessionStop.ResponseCode);
	}


	return 0;
}



int main_service(argc, argv)
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
	printf("\t\tRCD=%d\n",status->RCD);
	printf("\t\tEVSENotification=%d\n",status->EVSENotification);
	printf("\t\tNotificationMaxDelay=%d\n",status->NotificationMaxDelay);
}

static void printDCEVSEStatus(struct DC_EVSEStatusType* status)
{
	if(status->isused.EVSEIsolationStatus)
		printf("\tEVSEStatus:\n\t\tEVSEIsolationStatus=%d\n",status->EVSEIsolationStatus);

	printf("\t\tEVSEStatusCode=%d\n",status->EVSEStatusCode);

	if(status->EVSENotification==None_EVSENotificationType)
		printf("\t\tEVSENotification=None_EVSENotificationType\n");

	printf("\t\tNotificationMaxDelay=%d\n",status->NotificationMaxDelay);

}

static void printErrorMessage(struct EXIService* service)
{

	if(service->errorCode==EXI_NON_VALID_MESSAGE)
	{
		printf("EV did not send a valid V2G message!\n");
	}
	else if(service->errorCode==EXI_SERIALIZATION_FAILED)
	{
		printf("Error: Could not serialize the response message\n");
	}
	else if(service->errorCode==EXI_DESERIALIZATION_FAILED)
	{
		printf("Error: Could not deserialize the response message\n");
	}
	else if(service->errorCode==EXI_VALUE_RANGE_FAILED)
	{
		printf("Error: Could not deserialize the response message because of VALUE_RANGE\n");
	}
	else if(service->errorCode==EXI_UNKNOWN_ERROR)
	{
		printf("Error: Could not deserialize the response message because of VALUE_RANGE\n");
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

